#! /usr/bin/env python
import os
import awkward as ak
import matplotlib.pyplot as plt
import math
import numpy as np
from scipy import stats
from matplotlib.ticker import ScalarFormatter
import matplotlib.colors as colors

class Plot:
  """ 
  This class provides methods for creating various types of plots. It includes
  features for statistical analysis, automatic formatting, and scientific notation handling.
  
  Attributes:
    style_path (str): Path to the matplotlib style file.
      
  Methods:
    Plot1D: Create a 1D histogram.
    Plot2D: Create a 2D histogram.
    PlotGraph: Create a scatter plot.
    Plot1DOverlay: Overlay many 1D histograms.
    PlotGraphOverlay: Overlay many scatter plots.
  """

  def __init__(self, style_path=None):
    """
    Initialise the Plot class.
    
    Args:
      style_path (str, optional): Path to custom matplotlib style file.
        If None, uses default Mu2e style.
    """
    if style_path is None:
      style_path = os.path.join(os.path.dirname(__file__), 'mu2e.mplstyle')
    plt.style.use(style_path)
  
  def RoundToSigFig(self, val, sf): 
    """
    Round a value to a specified number of significant figures.
    
    Args:
      val (float): Value to round
      sf (int): Number of significant figures
        
    Returns:
      float: Rounded value
        
    Note:
      Returns original value for 0 or NaN inputs
    """
    if val == 0 or math.isnan(val): # Edge cases
      return val
    
    # Determine the order of magnitude
    mag = math.floor(math.log10(abs(val))) 
    # Calculate the scale factor
    scale = 10 ** (sf - mag - 1)
    # Round to the nearest number of significant figures
    return round(val * scale) / scale

  def GetStats(self, array, xmin, xmax): 
    """
    Calculate 'stat box' statistics from a 1D array.
    
    Args:
      array (np.ndarray): Input array
      xmin (float): Minimum x-axis value
      xmax (float): Maximum x-axis value
        
    Returns:
      tuple: (n_entries, mean, mean_err, std_dev, std_dev_err, underflows, overflows)
    """
    array = ak.to_numpy(array) # Ensure numpy array
    n_entries = len(array) # Number of entries
    mean = np.mean(array) # Mean
    mean_err = stats.sem(array) # Mean error (standard error on the mean from scipy)
    std_dev = np.std(array) # Standard deviation
    std_dev_err = np.sqrt(std_dev**2 / (2*n_entries)) # Standard deviation error assuming normal distribution
    underflows = len(array[array < xmin]) # Number of underflows
    overflows = len(array[array > xmax]) # Number of overflows
    return n_entries, mean, mean_err, std_dev, std_dev_err, underflows, overflows

  def _ScientificNotation(self, ax, lower_limit=1e-3, upper_limit=1e3, cbar=None): 
    """
    Set scientific notation on axes when appropriate.
    
    Args:
      ax (plt.Axes): Matplotlib axes object
      cbar (plt.colorbar.Colorbar, optional): Colorbar object
        
    Note:
      Scientific notation is applied when values are ≥ 10^4 or ≤ 10^-4
    """
    # Access the max values of the axes
    xmax, ymax = ax.get_xlim()[1], ax.get_ylim()[1]

    # Configure x-axis
    if ax.get_xscale() != 'log': 
      ax.xaxis.set_major_formatter(ScalarFormatter(useMathText=True)) # Use math formatting 
      ax.ticklabel_format(style='sci', axis='x', scilimits=(-4, 4)) # Set scientific notation
      # FIXME: x exponent overlaps with the axis title with right-aligned labels

    # Configure y-axis
    if ax.get_yscale() != 'log': 
      ax.yaxis.set_major_formatter(ScalarFormatter(useMathText=True))
      ax.ticklabel_format(style='sci', axis='y', scilimits=(-4, 4))

    # Configure colourbar
    if cbar is not None: 
        # Access the max value of the cbar range
        cmax = cbar.norm.vmax
        if abs(cmax) >= upper_limit or abs(cmax) <= lower_limit:
          cbar.ax.yaxis.set_major_formatter(ScalarFormatter(useMathText=True))  # Use math formatting
          cbar.ax.ticklabel_format(style='sci', axis='y', scilimits=(-4, 4))  # Set scientific notation

  def Plot1D(        
    self,
    array,
    nbins = 100,
    xmin = -1.0,
    xmax = 1.0,
    weights = None,
    title = None,
    xlabel = None,
    ylabel = None,
    col = 'black',
    leg_pos = 'best',
    out_path = None,
    dpi = 300,
    log_x = False,
    log_y = False,
    under_over = False,
    stat_box = True,
    stat_box_errors = False,
    error_bars = False,
    ax = None,
    show = True
  ):
    """
    Create a 1D histogram from an array of values.
    
    Args:
      array (np.ndarray): Input data array
      weights (np.ndarray, optional): Weights for each value
      nbins (int, optional): Number of bins. Defaults to 100
      xmin (float, optional): Minimum x-axis value. Defaults to -1.0
      xmax (float, optional): Maximum x-axis value. Defaults to 1.0
      title (str, optional): Plot title
      xlabel (str, optional): X-axis label
      ylabel (str, optional): Y-axis label
      col (str, optional): Histogram color. Defaults to 'black'
      leg_pos (str, optional): Legend position. Defaults to 'best'
      out_path (str, optional): Path to save the plot
      dpi (int, optional): DPI for saved plot. Defaults to 300
      log_x (bool, optional): Use log scale for x-axis. Defaults to False
      log_y (bool, optional): Use log scale for y-axis. Defaults to False
      under_over (bool, optional): Show overflow/underflow stats. Defaults to False
      stat_box (bool, optional): Show statistics box. Defaults to True
      stat_box_errors (bool, optional): Show errors in stats box. Defaults to False
      error_bars (bool, optional): Show error bars on bins. Defaults to False
      ax (plt.Axes, optional): External custom axes 
      show (bool, optional): Display the plot, defaults to True
        
    Raises:
      ValueError: If array is empty or None
    """
    # Input validation
    if array is None or len(array) == 0:
      raise ValueError("Empty or None array passed to Plot1D")
        
    # Create or use provided axes
    new_fig = False
    if ax is None:
      # Create figure and axes
      fig, ax = plt.subplots()
      new_fig = True
    
    # Create the histogram 
    counts, bin_edges, _ = ax.hist(array, bins=int(nbins), range=(xmin, xmax), histtype='step', edgecolor=col,  fill=False, density=False, weights=weights)
    bin_centres = (bin_edges[:-1] + bin_edges[1:]) / 2
    bin_errors = 0 * len(bin_centres)
    
    # Calculate errors
    if weights is None:
      bin_errors = np.sqrt(counts)  # Poisson errors for unweighted data
    else:
      # Weighted errors: sqrt(sum(weights^2)) for each bin
      weights_squared, _ = np.histogram(array, bins=int(nbins), range=(xmin, xmax), weights=np.square(weights))
      bin_errors = np.sqrt(weights_squared)
        
    # Plot the histogram 
    if error_bars:
      ax.errorbar(bin_centres, counts, yerr=bin_errors, ecolor=col, fmt='.', color=col, capsize=2, elinewidth=1)
    else:
      ax.hist(array, bins=int(nbins), range=(xmin, xmax), histtype='step', edgecolor=col, fill=False, density=False, weights=weights)
        
    # Set x-axis limits
    ax.set_xlim(xmin, xmax)
    
    # Log scale 
    if log_x: 
      ax.set_xscale('log')
    if log_y: 
      ax.set_yscale('log')
      
    # Statistics
    N, mean, mean_err, std_dev, std_dev_err, underflows, overflows = self.GetStats(array, xmin, xmax)
    
    # Create legend text (imitating the ROOT statbox)
    leg_txt = f'Entries: {N}\nMean: {self.RoundToSigFig(mean, 3)}\nStd Dev: {self.RoundToSigFig(std_dev, 3)}'
    
    # Stats box
    if stat_box_errors: 
      leg_txt = f'Entries: {N}\nMean: {self.RoundToSigFig(mean, 3)}' + rf'$\pm$' + f'{self.RoundToSigFig(mean_err, 1)}\nStd Dev: {self.RoundToSigFig(std_dev, 3)}' rf'$\pm$' + f'{self.RoundToSigFig(std_dev_err, 1)}'
    if under_over: 
      leg_txt += f'\nUnderflows: {underflows}\nOverflows: {overflows}'
    
    # Add legend to the plot
    if stat_box: 
      ax.legend([leg_txt], loc=leg_pos)
    
    # Formatting 
    ax.set_title(title)
    ax.set_xlabel(xlabel) 
    ax.set_ylabel(ylabel) 

    # Scientific notation 
    self._ScientificNotation(ax)

    # If no axis is provided, draw the figure
    if new_fig:
      # Draw
      plt.tight_layout()
      # Save
      if out_path:
        plt.savefig(out_path, dpi=dpi, bbox_inches='tight')
        print('\n---> Wrote:\n\t', out_path)
      # Show 
      if show: 
        plt.show()
      # Clear memory
      plt.close() 

  def Plot1DOverlay(
    self,
    hists_dict, 
    weights, 
    nbins = 100,
    xmin = -1.0,
    xmax = 1.0,
    title = None,
    xlabel = None,
    ylabel = None,
    out_path = None,
    dpi = 300,
    leg_pos = 'best',
    log_x = False,
    log_y = False,
    ax = None,
    show = True
  ):
    """
    Overlay multiple 1D histograms from a dictionary of arrays.
    
    Args:
        hists_dict (Dict[str, np.ndarray]): Dictionary mapping labels to arrays
        weights (List[np.ndarray], optional): List of weight arrays for each histogram
        nbins (int, optional): Number of bins. Defaults to 100
        xmin (float, optional): Minimum x-axis value. Defaults to -1.0
        xmax (float, optional): Maximum x-axis value. Defaults to 1.0
        title (str, optional): Plot title
        xlabel (str, optional): X-axis label
        ylabel (str, optional): Y-axis label
        out_path (str, optional): Path to save the plot
        dpi (int, optional): DPI for saved plot. Defaults to 300
        leg_pos (str, optional): Legend position. Defaults to 'best'
        log_x (bool, optional): Use log scale for x-axis. Defaults to False
        log_y (bool, optional): Use log scale for y-axis. Defaults to False
        ax (plt.Axes, optional): External custom axes.
        show (bool, optional): Display the plot. Defaults to True
        
    Raises:
        ValueError: If hists_dict is empty or None
        ValueError: If weights length doesn't match number of histograms
    """
    # Input validation
    if not hists_dict:
      raise ValueError("Empty or None histogram dictionary provided")
    if weights is not None and len(weights) != len(hists_dict):
      raise ValueError("Number of weight arrays does not match the number of histograms")

    # Create or use provided axes
    new_fig = False
    if ax is None:
      fig, ax = plt.subplots()
      new_fig = True
    
    # Iterate over the histograms and plot each one
    for i, (label, hist) in enumerate(hists_dict.items()):
      weight = None if weights is None else weights[i]
      ax.hist(
        hist,
        bins=nbins,
        range=(xmin, xmax),
        histtype='step',
        fill=False,
        density=False,
        label=label,
        weights=weight
      )

    # Configure axes scales
    if log_x:
      ax.set_xscale('log')
    if log_y:
      ax.set_yscale('log')
      
    # Set plot limits
    ax.set_xlim(xmin, xmax)

    # Format titles
    ax.set_title(title)
    ax.set_xlabel(xlabel)
    ax.set_ylabel(ylabel)

    # Set legend
    ax.legend(loc=leg_pos)
    
    # Configure scientific notation and legend
    self._ScientificNotation(ax)
    
    # Handle figure if not using external axes
    if new_fig:
      plt.tight_layout()
      # Save if output path provided
      if out_path:
        plt.savefig(out_path, dpi=dpi, bbox_inches="tight")
        print(f"\n---> Wrote:\n\t{out_path}")
      # Show 
      if show:
        plt.show()
      # Clear memory
      plt.close()
  
  def Plot2D(
    self,
    x,
    y,
    weights=None,
    nbins_x=100,
    xmin=-1.0,
    xmax=1.0,
    nbins_y=100,
    ymin=-1.0,
    ymax=1.0,
    title=None,
    xlabel=None,
    ylabel=None,
    zlabel=None,
    out_path=None,
    cmap='inferno',
    dpi=300,
    log_x=False,
    log_y=False,
    log_z=False,
    colorbar=True,
    ax=None,
    show=True
  ):
    
    """
    Plot a 2D histogram from two arrays of the same length.

    Args:
      x (np.ndarray): Array of x-values
      y (np.ndarray): Array of y-values 
      weights (np.ndarray, optional): Optional weights for each point
      nbins_x (int): Number of bins in x. Defaults to 100
      xmin (float): Minimum x value. Defaults to -1.0
      xmax (float): Maximum x value. Defaults to 1.0
      nbins_y (int): Number of bins in y. Defaults to 100
      ymin (float): Minimum y value. Defaults to -1.0
      ymax (float): Maximum y value. Defaults to 1.0
      title (str, optional): Plot title
      xlabel (str, optional): X-axis label
      ylabel (str, optional): Y-axis label
      zlabel (str, optional): Colorbar label
      out_path (str, optional): Path to save the plot
      cmap (str): Matplotlib colormap name. Defaults to 'inferno'
      dpi (int): DPI for saved plot. Defaults to 300
      log_x (bool): Use log scale for x-axis
      log_y (bool): Use log scale for y-axis
      log_z (bool): Use log scale for color values
      cbar (bool): Whether to show colorbar. Defaults to True
      ax (plt.Axes, optional): External custom axes.
      show (bool): show (bool, optional): Display the plot. Defaults to True
        
    Raises:
      ValueError: If input arrays are empty or different lengths
    """
    # Ensure numpy arrays
    x = ak.to_numpy(x)
    y = ak.to_numpy(y)

    # Filter out empty entries
    valid_indices = [i for i in range(len(x)) if np.any(x[i]) and np.any(y[i])]
    x = [x[i] for i in valid_indices]
    y = [y[i] for i in valid_indices]
    
    if weights is not None:
      weights = [weights[i] for i in valid_indices]

    # Validate inputs
    if len(x) == 0 or len(y) == 0:
      raise ValueError("Input arrays are empty")
    if len(x) != len(y):
      raise ValueError("Input arrays have different lengths")
        
    # Create or use provided axes
    new_fig = False
    if ax is None:
      fig, ax = plt.subplots()
      new_fig = True
        
    # Create 2D histogram
    hist, _, _ = np.histogram2d(
      x, y,
      bins=[nbins_x, nbins_y],
      range=[[xmin, xmax], [ymin, ymax]],
      weights=weights
    )
    
    # Set up normalisation
    if log_z:
      norm = colors.LogNorm(vmin=1, vmax=np.max(hist))
    else:
      norm = colors.Normalize(vmin=np.min(hist), vmax=np.max(hist))
        
    # Plot the 2D histogram
    im = ax.imshow(
      hist.T,
      cmap=cmap,
      extent=[xmin, xmax, ymin, ymax],
      aspect='auto',
      origin='lower',
      norm=norm
    )
    
    # Configure axes scales
    if log_x:
      ax.set_xscale('log')
    if log_y:
      ax.set_yscale('log')
        
    # Add colorbar
    cbar = None
    if colorbar:
      cbar = plt.colorbar(im, ax=ax)
      cbar.set_label(zlabel)
    
    # Set labels
    ax.set_title(title)
    ax.set_xlabel(xlabel)
    ax.set_ylabel(ylabel)
    
    # Scientific notation
    self._ScientificNotation(ax, cbar)
    
    if new_fig:
      # Draw
      plt.tight_layout()

      # Save if path provided
      if out_path:
        plt.savefig(out_path, dpi=dpi, bbox_inches='tight')
        print(f"\n---> Wrote:\n\t{out_path}")

      # Show if requested
      if show:
        plt.show()
          
      # Clear memory
      plt.close()
    
  def PlotGraph(
    self,
    x,
    y,
    xerr=None,
    yerr=None,
    title=None,
    xlabel=None,
    ylabel=None,
    xmin=None,
    xmax=None,
    ymin=None,
    ymax=None,
    col='black',
    linestyle='None',
    out_path=None,
    dpi=300,
    log_x=False,
    log_y=False,
    ax=None,
    show=True
  ):
    """
    Plot a scatter graph with optional error bars.

    Args:
      x (np.ndarray): Array of x-values
      y (np.ndarray): Array of y-values
      xerr (np.ndarray, optional): X error bars
      yerr (np.ndarray, optional): Y error bars
      title (str, optional): Plot title
      xlabel (str, optional): X-axis label
      ylabel (str, optional): Y-axis label
      xmin (float, optional): Minimum x value
      xmax (float, optional): Maximum x value
      ymin (float, optional): Minimum y value
      ymax (float, optional): Maximum y value
      color (str): Marker and error bar color, defaults to 'black'
      linestyle (str): Style for connecting lines, defaults to 'None'
      out_path (str, optional): Path to save the plot
      dpi (int): DPI for saved plot. Defaults to 300
      log_x (bool): Use log scale for x-axis, defaults to False
      log_y (bool): Use log scale for y-axis, defaults to False
      ax (plt.Axes, optional): Optional matplotlib axes to plot on
      show (bool): Whether to display plot, defaults to True

    Raises:
      ValueError: If input arrays have different lengths
    """
    # Input validation
    if len(x) != len(y):
      raise ValueError("x and y arrays must have the same length")
    
    # Create or use provided axes
    new_fig = False
    if ax is None:
      fig, ax = plt.subplots()
      new_fig = True

    # Create graph with error bars
    ax.errorbar(
      x, y,
      xerr=xerr,
      yerr=yerr,
      fmt='o',
      color=col,
      markersize=4,
      ecolor=col,
      capsize=2,
      elinewidth=1,
      linestyle=linestyle,
      linewidth=1
    )

    # Set axis limits if provided
    if xmin is not None or xmax is not None:
      ax.set_xlim(left=xmin, right=xmax)
    if ymin is not None or ymax is not None:
      ax.set_ylim(bottom=ymin, top=ymax)

    # Configure log scales
    if log_x:
      ax.set_xscale('log')
    if log_y:
      ax.set_yscale('log')
      
    # Set labels
    ax.set_title(title)
    ax.set_xlabel(xlabel)
    ax.set_ylabel(ylabel)
    
    # Scientific notation
    self._ScientificNotation(ax)
    
    if new_fig:
      # Draw
      plt.tight_layout()

      # Save if path provided
      if out_path:
        plt.savefig(out_path, dpi=dpi, bbox_inches='tight')
        print(f"\n---> Wrote:\n\t{out_path}")

      # Show if requested
      if show:
        plt.show()
      
      # Clear memory
      plt.close()
  
  def PlotGraphOverlay(
    self,
    graphs,
    title=None,
    xlabel=None,
    ylabel=None,
    xmin=None,
    xmax=None,
    ymin=None,
    ymax=None,
    legend_position='best',
    linestyle='None',
    out_path=None,
    log_x=False,
    log_y=False,
    dpi=300,
    ax=None,
    show=True
  ):
    """
    Overlay multiple scatter graphs with optional error bars.
    
    Args:
      graphs (dict): Dictionary of graphs to plot, where each graph is a dictionary:
        {
          'label1': {
            'x': x_array,
            'y': y_array,
            'xerr': xerr_array,  # optional
            'yerr': yerr_array   # optional
          },
          'label2': {...}
        }
      title (str, optional): Plot title
      xlabel (str, optional): X-axis label
      ylabel (str, optional): Y-axis label
      xmin (float, optional): Minimum x value
      xmax (float, optional): Maximum x value
      ymin (float, optional): Minimum y value
      ymax (float, optional): Maximum y value
      leg_pos (str): Position of legend. Defaults to 'best'
      linestyle (str): Style for connecting lines. Defaults to 'None'
      out_path (str, optional): Path to save plot
      log_x (bool): Use log scale for x-axis, defaults to False
      log_y (bool): Use log scale for y-axis, defaults to False
      dpi (int): DPI for saved plot, defaults to 300
      ax (plt.Axes, optional): Optional matplotlib axes to plot on
      show (bool): Whether to display plot. Defaults to True
        
    Raises:
        ValueError: If any graph data is malformed or arrays have different lengths
    """
    # Create or use provided axes
    new_fig = False
    if ax is None:
      fig, ax = plt.subplots()
      new_fig = True
    
    # Loop through graphs and plot
    for label, graph_data in graphs.items():
      # Validate graph data
      if not isinstance(graph_data, dict):
        raise ValueError(f"Graph data for {label} must be a dictionary")
      if 'x' not in graph_data or 'y' not in graph_data:
        raise ValueError(f"Graph data for {label} must contain 'x' and 'y' arrays")
      if len(graph_data['x']) != len(graph_data['y']):
        raise ValueError(f"X and Y arrays for {label} must have same length")
          
      # Get data
      x = graph_data['x']
      y = graph_data['y']
      xerr = graph_data.get('xerr', None)  # Use .get() to handle missing error bars
      yerr = graph_data.get('yerr', None)
        
      # Create this graph
      ax.errorbar(
        x, y,
        yerr=yerr,
        xerr=xerr,
        fmt='o',
        label=label,
        markersize=4,
        capsize=2,
        elinewidth=1,
        linestyle=linestyle,
        linewidth=1
      )

    # Set axis limits if provided
    if xmin is not None or xmax is not None:
      ax.set_xlim(left=xmin, right=xmax)
    if ymin is not None or ymax is not None:
      ax.set_ylim(bottom=ymin, top=ymax)

    # Configure log scales
    if log_x:
      ax.set_xscale('log')
    if log_y:
      ax.set_yscale('log')
      
    # Set labels
    ax.set_title(title)
    ax.set_xlabel(xlabel)
    ax.set_ylabel(ylabel)
    
    # Scientific notation
    self._ScientificNotation(ax)
    
    # Add legend
    ax.legend(loc=legend_position)
    
    if new_fig:
      # Draw
      plt.tight_layout()

      # Save if path provided
      if out_path:
        plt.savefig(out_path, dpi=dpi, bbox_inches='tight')
        print(f"\n---> Wrote:\n\t{out_path}")

      # Show 
      if show:
        plt.show()
          
      # Clear memory
      plt.close()