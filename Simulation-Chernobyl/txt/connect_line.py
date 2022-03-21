import numpy as np

# Creates 2 sorted arrays for left and right side for help_all screen
# containing coordinates of center of element and its name to be displayed on screen
# Arrays are sorted so there are no line intersections
# Filter can be used to excluede unwanted lines in output file

# inputs
separator = 630   # border on x axis sparating graph in left and right region
filters = np.array([7, 14, 15, 16, 17, 18, 24, 28, 46, 59])   # unwanted lines

# open files
objects = np.loadtxt("../data/coords.txt", dtype='int', delimiter=',')   # load coords from file to matrix
names_file = open("expl.txt")   # open file containing explanations
names = names_file.readlines()   # store them in list
names_file.close()   # close file

# remove everithing in explanations after ///
names_out = names   # names list
for name_num, name in enumerate(names):   # for line in explanations matrix:
    name = name.split(' ')   # convert string to list of words
    name_out = ""   # reset output string
    for word in name:   # for word in list of words:
        if word != "///": name_out += word + " "   # if word is not separator mark: add it to otput string
        else: break   # if word is separator mark: break loop
    names_out[name_num] = name_out.rstrip()   # add string to new line in names list, without whitespace on end

# sort and split coordinates with names, by x position
i_r = 0   # right group itterator
i_l = 0   # left group itterator
line_coords_r = np.zeros([len(objects), 7], dtype = object)   # right group empty matrix with int and string
line_coords_l = np.zeros([len(objects), 7], dtype = object)   # left group empty matrix with int and string
for line_num, line in enumerate(objects):   # for all lines in coords matrix:
    if np.all(line_num + 1 != filters):   # if line is not one of unwanted:
        if line [4] >= separator:   # if object center is past separator:
            line_coords_r[i_r, 0:6] = line   # write that line to right matrix
            line_coords_r[i_r, 6] = names_out[line_num]   # write corresponding name
            i_r += 1   # next column on output
        else:   # if object center is not past separator:
            line_coords_l[i_l, 0:6] = line   # write that line to left matrix
            line_coords_l[i_l, 6] = names_out[line_num]   # write corresponding name
            i_l += 1   # next column on output

# delete all zero rows
empty_idx_r = np.argwhere(np.all(line_coords_r[..., :] == 0, axis=1))   # find all zero rows
line_coords_r = np.delete(line_coords_r, empty_idx_r, axis=0)   # delete all zero rows
empty_idx_l = np.argwhere(np.all(line_coords_l[..., :] == 0, axis=1))   # find all zero rows
line_coords_l = np.delete(line_coords_l, empty_idx_l, axis=0)   # delete all zero rows
    
# sort text according to rules
line_coords_r = line_coords_r[np.argsort(line_coords_r[:, 5])]   # sort by center y coordinate
line_coords_l = line_coords_l[np.argsort(line_coords_l[:, 5])]   # sort by center y coordinate

# save files
np.savetxt('graph_coords_r.txt', line_coords_r, fmt='%s', delimiter=', ')   # output left coords array
np.savetxt('graph_coords_l.txt', line_coords_l, fmt='%s', delimiter=', ')   # output left coords array
