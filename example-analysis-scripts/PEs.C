// Samuel Grant 2024
// Read and plot crvcoincs.PEs, crvcoincs.PEsPerLayer, and crvcoincs.sidePEsPerLayer 
// Run this inside an EventNtuple muse environment

#include <iostream>
#include "EventNtuple/inc/CrvHitInfoReco.hh"

void DrawTH1(TH1F *hist, TString title, TString fname, bool logX = true, bool logY = true) {
    // Setup canvas
	TCanvas *c = new TCanvas("c","c",800,600);
    // Set title
	hist->SetTitle(title);
    // Set stats
	gStyle->SetOptStat(2210);
    // Format axes
	hist->GetXaxis()->SetTitleSize(.04);
	hist->GetYaxis()->SetTitleSize(.04);
	hist->GetXaxis()->SetTitleOffset(1.1);
	hist->GetYaxis()->SetTitleOffset(1.1);
	hist->GetXaxis()->CenterTitle(1);
	hist->GetYaxis()->CenterTitle(1);
	hist->GetYaxis()->SetMaxDigits(4);
    // Format line style
	hist->SetLineWidth(1);
	hist->SetLineColor(1);
    // Apply log scales if desired
    if (logX) { c->SetLogx(); }
    if (logY) { c->SetLogy(); }
    // Draw 
	hist->Draw("HIST");
    // Save canvas
	c->SaveAs(fname);
    // Clean up
	delete c;
    // End
	return;
}

void DrawTH1Overlay(std::map<TString, TH1F*> hist_map, TString title, TString fname, bool logX = true, bool logY = true) {
    // Setup canvas 
    TCanvas *c = new TCanvas("c", "c", 800, 600);
    gStyle->SetOptStat(0);
    // Set title once
    auto it = hist_map.begin();
    it->second->SetTitle(title);
    // Book legend
    TLegend *legend = new TLegend(0.69, 0.69, 0.89, 0.89);
    legend->SetBorderSize(0);
    legend->SetTextSize(0.03);
    // Loop thro' hist map
    size_t i = 0; // Initialise hist index
    for (auto &[label, hist] : hist_map) { 
        // Format axes
        hist->GetXaxis()->SetTitleSize(.04);
        hist->GetYaxis()->SetTitleSize(.04);
        hist->GetXaxis()->SetTitleOffset(1.1);
        hist->GetYaxis()->SetTitleOffset(1.1);
        hist->GetXaxis()->CenterTitle(1);
        hist->GetYaxis()->CenterTitle(1);
        hist->GetYaxis()->SetMaxDigits(4);
        // Format line style 
        hist->SetLineColor(i + 1); 
        hist->SetLineWidth(1);
        // Draw the histogram, using "same" for all but the first
        hist->Draw(i == 0 ? "HIST" : "HIST SAME");
        // Add label
        legend->AddEntry(hist, label, "l");
        ++i; // Increment hist index
    }
    // Draw the legend
    legend->Draw();
    // Apply log scales if desired
    if (logX) { c->SetLogx(); }
    if (logY) { c->SetLogy(); }
    // Save the canvas
    c->SaveAs(fname);
    // Clean up
    delete legend;
    delete c;
}

void Run(TString finName) { 
    // Open file 
    TFile *fin = TFile::Open(finName); 
    // Get tree
    TTree *tree = (TTree*)fin->Get("EventNtuple/ntuple");
    // Get branches
    Int_t event;
    std::vector<mu2e::CrvHitInfoReco>* crvcoincs = nullptr;
    tree->SetBranchAddress("event", &event);
    tree->SetBranchAddress("crvcoincs", &crvcoincs);
    // Book PE histogram
    TH1F *h1_PEs = new TH1F("h1_PEs", "", 1e5-1, 1, 1e5);
    // Book PEsPerLayer and sidePEsPerLayer histograms 
    // I'm using maps to hold them, with the legend label as a key (slightly awkward)
    std::map<TString, TH1F*> h1_PEsPerLayerMap; 
    std::map<TString, TH1F*> h1_sidePEsPerLayerMap; 
    for (int i_layer = 0; i_layer < mu2e::CRVId::nLayers; i_layer++) {
        TH1F *h1_PEsPerLayer = new TH1F(("h1_PEsPerLayer"+to_string(i_layer)).c_str(), "", 1e4-1, 1, 1e4); 
        h1_PEsPerLayerMap[("Layer " +to_string(i_layer)).c_str()] = h1_PEsPerLayer;
        for (int i_side = 0; i_side < mu2e::CRVId::nSidesPerBar; i_side++) { 
            TH1F *h1_sidePEsPerLayer = new TH1F(("h1_sidePEsPerLayer"+to_string(i_layer)+to_string(i_side)).c_str(), "", 1e4-1, 1, 1e4);
            h1_sidePEsPerLayerMap[("Layer " +to_string(i_layer)+", side "+to_string(i_side)).c_str()] = h1_sidePEsPerLayer; 
        }
    }
    // Loop thro' the tree
    Long64_t nEntries = tree->GetEntries();
    for (Long64_t i_event = 0; i_event < nEntries; ++i_event) {
        // Get event
        tree->GetEntry(i_event);
        // Skip empty events
        if (crvcoincs->size() == 0) { continue; }
        // Loop thro' coincidences in the current event
        for (auto& crvcoinc : *crvcoincs) {
            // Get total PEs
            float PEs = crvcoinc.PEs;
            // Fill PEs histogram
            h1_PEs->Fill(PEs);
            // Loop thro' layers
            for (int i_layer = 0; i_layer < mu2e::CRVId::nLayers; i_layer++) {
                // Get PEsPerLayer
                float PEsPerLayer = crvcoinc.PEsPerLayer[i_layer];
                // Fill PEsPerLayer
                h1_PEsPerLayerMap[("Layer " +to_string(i_layer)).c_str()]->Fill(PEsPerLayer);
                // Loop thro' sides
                for (int i_side = 0; i_side < mu2e::CRVId::nSidesPerBar; i_side++) { 
                    // Calculate layer/side index
                    int layerSideIndex = i_layer * mu2e::CRVId::nSidesPerBar + i_side;
                    // Get sidePEsPerLayer
                    float sidePEsPerLayer = crvcoinc.sidePEsPerLayer[layerSideIndex];
                    // Fill sidePEsPerLayer
                    h1_sidePEsPerLayerMap[("Layer " +to_string(i_layer)+", side "+to_string(i_side)).c_str()]->Fill(sidePEsPerLayer);
                }
            }
        }
        // Calculate percentage completion
        float percentage = (static_cast<float>(i_event) / nEntries) * 100;
        // Print the percentage 
        if (i_event % (nEntries / 100) == 0) {
            printf("Processing: %.1f%%\n", percentage);
        }
    }
    // Draw
    DrawTH1(h1_PEs, "; PEs; Coincidences", "h1_PEs.png");
    DrawTH1Overlay(h1_PEsPerLayerMap, "; PEs per layer; Coincidences", "h1_PEsPerLayer.png");
    DrawTH1Overlay(h1_sidePEsPerLayerMap, "; PEs per layer per side; Coincidences", "h1_sidePEsPerLayer.png");
    // Close file
    fin->Close();
    std::cout << "Processing completed successfully.\n";
    // End
    return;
}
// Entry point
void PEs() { 
    Run("nts.owner.trkana-reco.version.sequencer.root");
    return;

}
