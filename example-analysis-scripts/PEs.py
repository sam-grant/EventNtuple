# Samuel Grant 2024
# Read and plot crvcoincs.PEs, crvcoincs.PEsPerLayer, and crvcoincs.sidePEsPerLayer 

# Setup the Mu2e Python environment first: 
# mu2einit
# source /cvmfs/mu2e.opensciencegrid.org/env/ana/current/bin/activate

# External libraries
import uproot
import awkward as ak
import numpy as np

# Internal classes
from utils import Plotter, Printer  # Plotting and printing methods

def run(filename):
    # Helpers
    plotter = Plotter()
    printer = Printer()

    # EventNtuple branch names
    branch_names_ = [
        'event',
        'crvcoincs.PEs', 
        'crvcoincs.PEsPerLayer[4]', 
        'crvcoincs.sidePEsPerLayer[8]'
    ]

    # Load tree into awkward array
    with uproot.open(filename + ':EventNtuple/ntuple') as tree:
        data_ = tree.arrays(branch_names_) 

    # Print information on the first 5 events
    printer.print_n_events(data_, n_events=5)

    # Plot PEs 
    PEs_ = ak.flatten(data_['crvcoincs.PEs'], axis=None)
    plotter.plot_1D(PEs_, nbins=int(np.max(PEs_)-1), xmin=1, xmax=int(np.max(PEs_)-1), 
                     xlabel='PEs', ylabel='Coincidences', fout='h1_PEs.png', 
                     log_y=True, log_x=True)
    
    # Plot PEsPerLayer 
    PEsPerLayer_ = data_['crvcoincs.PEsPerLayer[4]']
    PEsPerLayer0_ = ak.flatten(PEsPerLayer_[:,:,0], axis=None) # Helpful for setting the range
    plotter.plot_1D_overlay( {'Layer 0' : ak.flatten(PEsPerLayer_[:,:,0], axis=None), 
                              'Layer 1' : ak.flatten(PEsPerLayer_[:,:,1], axis=None), 
                              'Layer 2' : ak.flatten(PEsPerLayer_[:,:,2], axis=None), 
                              'Layer 3' : ak.flatten(PEsPerLayer_[:,:,3], axis=None)}, 
                              nbins=int(np.max(PEsPerLayer0_)-1), xmin=1, xmax=np.max(PEsPerLayer0_), 
                              xlabel='PEs per layer', ylabel='Coincidences', fout='h1_PEsPerLayer.png', 
                              log_x=True, log_y=True)
    
    # Plot sidePEsPerLayer 
    sidePEsPerLayer_ = data_['crvcoincs.sidePEsPerLayer[8]']
    sidePEsPerLayer00_ = ak.flatten(sidePEsPerLayer_[:,:,0::2][:,:,0], axis=None) # Helpful for setting the range
    # Negative sides have even indices (0::2), positive sides have odd indices (1::2)
    plotter.plot_1D_overlay({'Layer 0, side 0' : ak.flatten(sidePEsPerLayer_[:,:,0::2][:,:,0], axis=None), 
                             'Layer 1, side 0' : ak.flatten(sidePEsPerLayer_[:,:,0::2][:,:,1], axis=None),
                             'Layer 2, side 0' : ak.flatten(sidePEsPerLayer_[:,:,0::2][:,:,2], axis=None),
                             'Layer 3, side 0' : ak.flatten(sidePEsPerLayer_[:,:,0::2][:,:,3], axis=None),
                             'Layer 0, side 1' : ak.flatten(sidePEsPerLayer_[:,:,1::2][:,:,0], axis=None), 
                             'Layer 1, side 1' : ak.flatten(sidePEsPerLayer_[:,:,1::2][:,:,1], axis=None),
                             'Layer 2, side 1' : ak.flatten(sidePEsPerLayer_[:,:,1::2][:,:,2], axis=None),
                             'Layer 3, side 1' : ak.flatten(sidePEsPerLayer_[:,:,1::2][:,:,3], axis=None)}, 
                             nbins=int(np.max(sidePEsPerLayer00_-1)), xmin=1, xmax=np.max(sidePEsPerLayer00_-1), 
                             xlabel='PEs per layer per side', ylabel='Coincidences', fout='h1_sidePEsPerLayer.png', 
                             log_x=True, log_y=True)
    
    return

# Entry point
def main(): 
    run('nts.owner.trkana-reco.version.sequencer.root')
    return

if __name__ == '__main__':
    main()