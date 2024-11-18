# Samuel Grant 2024
# Helper functions for plotting and debugging 

import math
import numpy as np
from scipy import stats

# FIXME: matplotlib workaround, currently see the error:
# qt.qpa.plugin: Could not find the Qt platform plugin "xcb" in ""
# when running matplotlib on the VMS
import matplotlib
matplotlib.use('Agg') # Use the Agg backend (no Qt needed)
import matplotlib.pyplot as plt 

class Plotter:
    # Initialise
    def __init__(self):
        pass  
    
    # Colour map
    colours = [
        (0., 0., 0.),                                                   # Black
        (0.8392156862745098, 0.15294117647058825, 0.1568627450980392),  # Red
        (0.12156862745098039, 0.4666666666666667, 0.7058823529411765),  # Blue
        (0.17254901960784313, 0.6274509803921569, 0.17254901960784313), # Green
        (1.0, 0.4980392156862745, 0.054901960784313725),                # Orange
        (0.5803921568627451, 0.403921568627451, 0.7411764705882353),    # Purple
        (0.09019607843137255, 0.7450980392156863, 0.8117647058823529),  # Cyan
        (0.8901960784313725, 0.4666666666666667, 0.7607843137254902),   # Pink
        (0.5490196078431373, 0.33725490196078434, 0.29411764705882354), # Brown
        (0.4980392156862745, 0.4980392156862745, 0.4980392156862745),   # Gray 
        (0.7372549019607844, 0.7411764705882353, 0.13333333333333333)   # Yellow
    ]

    # Rounding
    def round(self, value, sf):
        if value == 0.:
            return '0'
        elif math.isnan(value):
            return 'NaN'
        else:
            # Determine the order of magnitude
            magnitude = math.floor(math.log10(abs(value))) + 1
            # Calculate the scale factor
            scale_factor = sf - magnitude
            # Truncate the float to the desired number of significant figures
            truncated_val = math.trunc(value * 10 ** scale_factor) / 10 ** scale_factor
            # Convert the truncated value to a string and return it
            truncated_str = str(truncated_val).rstrip('0').rstrip('.')
            return truncated_str 

    # Stats for histograms (assumes a normal distribution, ROOT does the same thing with TH1)
    def get_stats(self, data, xmin, xmax):
        # data = data[(data >= xmin) & (data <= xmax)] # Filter data within range
        n = len(data) 
        mean = np.mean(data)  
        mean_err = stats.sem(data) # Mean error (standard error of the mean from scipy)
        std_dev = np.std(data) # Standard deviation
        std_dev_err = np.sqrt(std_dev**2 / (2*n)) # Standard deviation error assuming normal distribution
        underflows = len(data[data < xmin]) # Number of underflows
        overflows = len(data[data > xmax]) # Number of overflows
        return n, mean, mean_err, std_dev, std_dev_err, underflows, overflows
    
    # Plot 1D histogram
    def plot_1D(self, data, nbins=100, xmin=-1.0, xmax=1.0, title=None, xlabel=None, ylabel=None, fout='hist.png', leg_pos='best', log_x=False, log_y=False, stats=True, under_over=False, errors=False, NDPI=300):
        # Convert to numpy 
        data = np.array(data)
        # Create figure and axes
        fig, ax = plt.subplots()
        # Plot the histogram with outline
        counts, bin_edges, _ = ax.hist(data, bins=nbins, range=(xmin, xmax), histtype='step', edgecolor='black', linewidth=1.0, fill=False, density=False)
        # Set x-axis limits
        ax.set_xlim(xmin, xmax)
        # Log scale 
        if log_x: ax.set_xscale('log')
        if log_y: ax.set_yscale('log')
        # Calculate statistics
        N, mean, mean_err, std_dev, std_dev_err, underflows, overflows = self.get_stats(data, xmin, xmax)
        # Create legend text
        leg_txt = f'Entries: {N}\nMean: {self.round(mean, 3)}\nStd Dev: {self.round(std_dev, 3)}'
        if errors: leg_txt = f'Entries: {N}\nMean: {self.round(mean, 3)}' + rf'$\pm$' + f'{self.round(mean_err, 1)}\nStd Dev: {self.round(std_dev, 3)}' rf'$\pm$' + f'{self.round(std_dev_err, 1)}'
        if under_over: leg_txt += f'\nUnderflows: {underflows}\nOverflows: {overflows}'
        # Add legend to the plot
        if stats: ax.legend([leg_txt], loc=leg_pos, frameon=False, fontsize=13)
        # Formatting 
        ax.set_title(title, fontsize=15, pad=10)
        ax.set_xlabel(xlabel, fontsize=13, labelpad=10) 
        ax.set_ylabel(ylabel, fontsize=13, labelpad=10) 
        # Set font size of tick labels on x and y axes
        ax.tick_params(axis='x', labelsize=13)  # Set x-axis tick label font size
        ax.tick_params(axis='y', labelsize=13)  # Set y-axis tick label font size
        # Draw
        plt.tight_layout()
        plt.savefig(fout, dpi=NDPI, bbox_inches='tight')
        # plt.show() 
        # Save the figure
        print('\n---> Written:\n\t', fout)
        # Clear memory
        plt.close()
        return
    
    # Overlay many 1D histograms
    def plot_1D_overlay(self, hists_, nbins=100, xmin=-1.0, xmax=1.0, title=None, xlabel=None, ylabel=None, fout='hist.png', leg_pos='best', log_x=False, log_y=False, NDPI=300, include_black=False):
        # Create figure and axes
        fig, ax = plt.subplots()
        # Iterate over the hists and plot each one
        for i, (label, hist) in enumerate(hists_.items()):
            colour = self.colours[i]
            if not include_black: colour = self.colours[i+1]
            counts, bin_edges, _ = ax.hist(hist, bins=nbins, range=(xmin, xmax), histtype='step', edgecolor=colour, linewidth=1.0, fill=False, density=False, color=colour, label=label)
        # Log scale 
        if log_x: ax.set_xscale('log')
        if log_y: ax.set_yscale('log') 
        # Set x-axis limits
        ax.set_xlim(xmin, xmax)
        ax.set_title(title, fontsize=16, pad=10)
        ax.set_xlabel(xlabel, fontsize=14, labelpad=10) 
        ax.set_ylabel(ylabel, fontsize=14, labelpad=10) 
        # Set font size of tick labels on x and y axes
        ax.tick_params(axis='x', labelsize=14)  # Set x-axis tick label font size
        ax.tick_params(axis='y', labelsize=14)  # Set y-axis tick label font size
        # Scientific notation
        # self.ScientificNotation(ax)
        # Add legend to the plot
        ax.legend(loc=leg_pos, frameon=False, fontsize=12)
        # Draw
        plt.tight_layout()
        # Save
        plt.savefig(fout, dpi=NDPI, bbox_inches='tight')
        # plt.show()
        # Clear memory
        plt.close()
        print('\n---> Written:\n\t', fout)
        return
    
class Printer: 
    # Initialise
    def __init__(self):
        pass  

    # Event string in human readable form 
    def get_event_str(self, event):
        
        event_str = (
            f'-------------------------------------------------------------------------------------\n'
            # f'***** evt *****\n'
            f'event: {event['event']}\n'
            # f'***** crv *****\n'
            f'crvcoincs.PEs: {(event['crvcoincs.PEs'])}\n'
            f'crvcoincs.PEsPerLayer: {(event['crvcoincs.PEsPerLayer[4]'])}\n'
            f'crvcoincs.sidePEsPerLayer: {(event['crvcoincs.sidePEsPerLayer[8]'])}\n'
            # Add 'to_list' for verbose printouts
            # f'crvcoincs.PEs: {ak.to_list(event['crvcoincs.PEs'])}\n'
            # f'crvcoincs.PEsPerLayer: {ak.to_list(event['crvcoincs.PEsPerLayer[4]'])}\n'
            # f'crvcoincs.sidePEsPerLayer: {ak.to_list(event['crvcoincs.sidePEsPerLayer[8]'])}\n'
            f'-------------------------------------------------------------------------------------\n'
        )

        return event_str

    def print_n_events(self, data_, n_events=10):
        # Iterate event-by-event
        for i, event in enumerate(data_, start=1):
            print(self.get_event_str(event))
            if i >= n_events: 
                return