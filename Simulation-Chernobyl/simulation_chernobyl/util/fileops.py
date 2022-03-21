# loads settings from file
def load_settings():
    setfile = open("data/settings.txt")   # open settings file
    setmatrix = setfile.readlines()   # read settings
    setfile.close()   # close file
    setmatrix = setmatrix[0].replace("\n", "")   # read first line
    setmatrix = setmatrix.split()   # convert string to list
    antial = eval(setmatrix[0])   # set antial
    sound_volume = int(setmatrix[1])   # set sound volume
    simstep = int(setmatrix[2])   # set simstep
    lang = setmatrix[3]   # set simulation language
    return antial, sound_volume, simstep, lang
