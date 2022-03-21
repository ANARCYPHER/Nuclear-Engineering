import numpy as np

# Calculates center coordinates of boxes edge coordinates given in file
# and saves them in new file with edge coordinates of box

moverbox = np.loadtxt("input_coords.txt", dtype='int', delimiter=',')   # load file to main array
centerx = ((moverbox[:,2]-moverbox[:,0])/2 + moverbox[:,0]).astype(int)   # calculate center x coords
centery = ((moverbox[:,3]-moverbox[:,1])/2 + moverbox[:,1]).astype(int)   # calculate center y coords
emptyarr = np.zeros([len(moverbox), 2])   # create empty array
emptyarr[:,0] = centerx   # add center x coords to empty array
emptyarr[:,1] = centery   # add center x coords to empty array
emptyarr = emptyarr.astype(int)   # convert it to int
moverbox = np.append(moverbox, emptyarr, axis=1)    # append it to main array
np.savetxt('coords.txt', moverbox, fmt='%d', delimiter=', ')   # output main array to file

moverbox = np.loadtxt("input_rods_coords.txt", dtype='int', delimiter=',')   # load file to main array
centerx = ((moverbox[:,2]-moverbox[:,0])/2 + moverbox[:,0]).astype(int)   # calculate center x coords
centery = ((moverbox[:,3]-moverbox[:,1])/2 + moverbox[:,1]).astype(int)   # calculate center y coords
emptyarr = np.zeros([len(moverbox), 2])   # create empty array
emptyarr[:,0] = centerx   # add center x coords to empty array
emptyarr[:,1] = centery   # add center x coords to empty array
emptyarr = emptyarr.astype(int)   # convert it to int
moverbox = np.append(moverbox, emptyarr, axis=1)    # append it to main array
np.savetxt('rods_coords.txt', moverbox, fmt='%d', delimiter=', ')   # output main array to file
