'''
Samuel Grant 2024
Demo for mu2epyutils Print() class
'''

# External libraries
import uproot

# Internal classes
import sys
import os
sys.path.append(os.path.abspath('../utils/pyutils'))

from mu2epyutil import Print

def Run(filename):
	# Utilities classes
	pr = Print()

	# Branch names 
	branch_names_ = [ 
		# Events
		'run',
		'subrun',
		'event',
		# CRV coincidences
		'crvcoincs.sectorType', 
		'crvcoincs.pos.fCoordinates.fX',
		'crvcoincs.pos.fCoordinates.fY',
		'crvcoincs.pos.fCoordinates.fZ',
		'crvcoincs.time', 
		'crvcoincs.timeStart',
		'crvcoincs.PEs',
		'crvcoincs.PEsPerLayer[4]',
		'crvcoincs.sidePEsPerLayer[8]',
		'crvcoincs.nHits',
		'crvcoincs.nLayers', 
		'crvcoincs.angle',
		# Tracks
		'trk.status',
		'trk.nactive',
		'trk.nhits',
		'trk.nplanes',
		'trk.nnullambig',
		'trk.ndof',
		'trk.fitcon',
		# Track segments
		'trksegs'
	] 

	# Load tree into Awkward array
	with uproot.open(filename + ':EventNtuple/ntuple') as tree:
		# print(tree.fields)
		data_ = tree.arrays(branch_names_)

	# Print raw array
	print('\n\nRaw array:\n\n', data_)

	# Print one event in readable form 
	print('\n\nHuman readable:\n')
	pr.PrintNEvents(data_, n=1)

	return

def main(): 
	Run(filename='nts.owner.trkana-reco.version.sequencer.root')
	return

if __name__ == '__main__':
	main()	