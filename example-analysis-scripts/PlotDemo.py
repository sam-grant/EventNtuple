'''
Samuel Grant 2024
Demo for mu2epyutils Plot() class

Run this inside the Mu2e Python environment: 
source /cvmfs/mu2e.opensciencegrid.org/env/ana/current/bin/activate

'''

# External libraries
import numpy as np
import sys
import os

# Internal classes
sys.path.append(os.path.abspath('../utils/pyutils'))

from mu2epyutil import Plot

def Run():
    # Get class
    pl = Plot()

    # Global bool to toggle plt.show()
    show = False

    # Make a Gaussian to plot
    N = 10000
    mu = 0     
    sigma = 1
    data1_ = np.random.normal(loc=mu, scale=sigma, size=N)

    """ Demo for Plot().Plot1D() """

    # Plot a 1D histogram with a basic stats box
    pl.Plot1D(
        data1_, nbins=100, xmin=-5, xmax=5,
        title='Basic 1D histogram', xlabel='x', ylabel='Counts', fout='h1_basic.png',
        show=show, # Toggle plt.show()
    )

    # Change the colour 
    pl.Plot1D(
        data1_, nbins=100, xmin=-5, xmax=5, 
        title='Change the colour', xlabel='x', ylabel='Counts', fout='h1_red.png', 
        show=show,  
        col=pl.col_[1] # line colour
    )

    # Make stats box more verbose 
    pl.Plot1D(
        data1_, nbins=100, xmin=-4, xmax=6, 
        title='Verbose stats box ', xlabel='x', ylabel='Counts', fout='h1_verbose_stats.png',
        show=show,
        stat_errors=True, under_over=True # Stat box errors and under/overflows
    )

    # Move the stats box 
    pl.Plot1D(
        data1_, nbins=100, xmin=-5, xmax=5, 
        title='Reposition the stats box', xlabel='x', ylabel='Counts', fout='h1_move_stats.png',
        show=show, 
        leg_pos='upper left' # Move the stat box
    )

    # Remove the stats box 
    pl.Plot1D(
        data1_, nbins=100, xmin=-5, xmax=5, 
        title='Remove the stats box', xlabel='x', ylabel='Counts', fout='h1_no_stats.png',
        show=show, 
        stats=False # Remove the stat box
    )

    # Add error bars
    pl.Plot1D(
        data1_, nbins=100, xmin=-5, xmax=5, 
        title='Add error bars', xlabel='x', ylabel='Counts', fout='h1_error_bars.png',
        show=show,
        error_bars=True # Add Poisson error bars 
    )

    # Reweight your data
    pl.Plot1D(
        data1_, nbins=100, xmin=-6, xmax=6, 
        title='Reweight', xlabel='x', ylabel='Counts', fout='h1_gaus_errors.png',
        show=show,
        weights_=abs(data1_) # Reweight the bins 
    )

    # Use a log scale 
    pl.Plot1D(
        data1_, nbins=100, xmin=-5, xmax=5, 
        title='Add a log scale', xlabel='x', ylabel='Counts', fout='h1_log_y.png',
        show=show,
        log_y=True # Log scale on y 
    )
    
    """ Demo for Plot().Plot1DOverlay() """

    # Two more Gaussians
    data2_ = np.random.normal(loc=mu+2, scale=sigma, size=N)
    data3_ = np.random.normal(loc=mu-2, scale=sigma, size=N)

    # Overlay many 1D histograms
    pl.Plot1DOverlay(
        {  
            "Left" : data3_,
            "Middle" : data1_,
            "Right" : data2_,
             
        },
        nbins=100, xmin=-6, xmax=6, 
        title="Overlay many 1D histograms", xlabel='x', ylabel='Counts', fout='h1_overlay.png',
        show=show
    )

    # """ Demo for Plot().Plot2D() """

    # Make a spiral
    t_ = np.linspace(0, 10 * np.pi, 500) 
    a = 0.1  
    x_ = a * t_ * np.cos(t_)  
    y_ = a * t_ * np.sin(t_)  
    r_ = np.sqrt(x_**2 + y_**2)
    
    # Plot a 2D histogram
    pl.Plot2D(
        x_=x_, y_=y_, nbins_x=50, xmin=np.min(x_), xmax=np.max(x_), nbins_y=50, ymin=np.min(y_), ymax=np.max(y_), 
        title="Basic 2D histogram", xlabel='x', ylabel='y', fout='h2_basic.png',
        show=show
    )

    # Change the colour scheme
    pl.Plot2D(
        x_=x_, y_=y_, nbins_x=50, xmin=np.min(x_), xmax=np.max(x_), nbins_y=50, ymin=np.min(y_), ymax=np.max(y_), 
        title='Change the colour scheme', xlabel='x', ylabel='y', fout='h2_viridis.png',
        show=show,
        cmap='viridis'
    )

    # Remove the colour bar 
    pl.Plot2D(
        x_=x_, y_=y_, nbins_x=50, xmin=np.min(x_), xmax=np.max(x_), nbins_y=50, ymin=np.min(y_), ymax=np.max(y_), 
        title='Remove the colour bar', xlabel='x', ylabel='y', fout='h2_no_cbar.png',
        show=show,
        cb=False 
    )
    
    # Use a log colour scheme
    pl.Plot2D(
        x_=x_, y_=y_, nbins_x=50, xmin=np.min(x_), xmax=np.max(x_), nbins_y=50, ymin=np.min(y_), ymax=np.max(y_), 
        title='Use a log colour scale', xlabel='x', ylabel='y', fout='h2_logz.png',
        show=show, 
        log_z=True
    )

    # Reweight 
    pl.Plot2D(
        x_=x_, y_=y_, nbins_x=50, xmin=np.min(x_), xmax=np.max(x_), nbins_y=50, ymin=np.min(y_), ymax=np.max(y_), 
        title='Reweight', xlabel='x', ylabel='y', fout='h2_reweight.png',
        show=show,
        weights_=r_**2, zlabel=r"$r^{2}$"
    )

    """ Demo for Plot().PlotGraph() """

    # Basic graph
    pl.PlotGraph(
        x_=x_, y_=y_,
        title="Basic scatter plot", xlabel='x', ylabel='y', fout='gr_basic.png',
        show=show
    )

    # Change the colour 
    pl.PlotGraph(
        x_=x_, y_=y_,
        title="Change the colour", xlabel='x', ylabel='y', fout='gr_red.png',
        show=show,
        col=pl.col_[1]
    )

   # Add a line
    pl.PlotGraph(
        x_=x_, y_=y_,
        title="Add a connecting line", xlabel='x', ylabel='y', fout='gr_line.png',
        show=show,
        linestyle='-'
    )

    # Change the range
    pl.PlotGraph(
        x_=x_, y_=y_,
        title="Change the range", xlabel='x', ylabel='y', fout='gr_range.png',
        show=show,
        xmin=-1, xmax=1, ymin=-1, ymax=1
    )

    # Add yerror bars
    pl.PlotGraph(
        x_=x_, y_=y_,
        title="Add yerror bars", xlabel='x', ylabel='y', fout='gr_yerrors.png',
        show=show,
        yerr_=5e-4*len(y_) 
    )

    # Add xerror bars
    pl.PlotGraph(
        x_=x_, y_=y_,
        title="Add xerror bars", xlabel='x', ylabel='y', fout='gr_xerrors.png',
        show=show,
        xerr_=5e-4*len(x_) 
    )

    # Add a log scale
    pl.PlotGraph(
        x_=x_, y_=y_,
        title="Add yerror bars", xlabel='x', ylabel='y', fout='gr_log_y.png',
        show=show,
        log_y=True 
    )

    """ Demo for Plot().PlotGraphOverlay() """

    # Three oscillating functions with phase shifts
    t_ = np.linspace(0, 10, 50)
    lam = 0.2 # decay constant
    f1_ = np.exp(-lam * t_) * np.sin(t_)  # sin(t)
    f2_ = np.exp(-lam * t_) * np.sin(t_ + 2 * np.pi / 3)  # sin(t + 2pi/3)
    f3_ = np.exp(-lam * t_) *  np.sin(t_ - 2 * np.pi / 3)  # sin(t - 2pi/3)

    # Setup graphs_ dict
    graphs_ = { 
        r"$\phi=0$" : [ t_, f1_, None, None],
        r"$\phi=2\pi/3$" : [ t_, f2_, None, None],
        r"$\phi=-2\pi/3$" : [ t_, f3_, None, None]
    } 

    # Plot overlay
    pl.PlotGraphOverlay(
        graphs_=graphs_,
        title="Overlay many graphs", xlabel='t', ylabel='f(t)', fout='gr_overlay.png',
        show=show, include_black=True
    )

    return

def main(): 
    Run()
    return

if __name__ == '__main__':
    main()