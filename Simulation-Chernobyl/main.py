import pygame
import numpy as np
import math
import time
import datetime
import webbrowser
import os
import csv

from simulation_chernobyl.util import fileops
from simulation_chernobyl.graphics import graphics
from simulation_chernobyl.graphics import grapher
from simulation_chernobyl.graphics import logger
from simulation_chernobyl.graphics import screens
from simulation_chernobyl.graphics import rgb

logger = logger.Logger()
grapher = grapher.Grapher()
screens = screens.Screens()



# --Todo-- #
###### record select zoom, focus, help
##### zoom graph and record x
##### graph line height multiplyer in picker
### auto scale graph 

######### engine
######## main interface
##### save, load, save on quit
### logging
## icon

version = "Pre-alpha 0.2.2"
date = "(30.1.2022)" 



###### --Initial variables-- ######
update = 30   # screen update frequency
windowx, windowy = 1280, 720   # window width, window height

simspeed = 1.0   # simulation speed multiplyer
sound_volume = 5   # initial sound volume
zoom = 1   # graph zoom
counter_step = 0.1   # simulation step size
counter = 0   # simulation time

antial = False   # anti aliasing
sound = True   # sound on/off
pause = True   # program paused
record = False   # recording values
rec_show = False   # show recorded values
rec_img = False   # save image of record graph
settings = False   # settings open
graph_picker = False   # graph picker open
whelp = False   # help window open
whelp_all = False   # full diagram show
wabout = False   # about window open
welcome = False   # print welcome text
sel_record = 0   # selected recort to show
mouse_wheel = 0   # mouse wheel rotation state

lang = "eng"   # simulation language
lang_num = 1   # index of language in use

textout_color = rgb.black   # initial text color
grapher.graph_dim(1, 538, 361, 718, counter_step)   # grapher dimensions



###### --Load database-- ######

###### --Load encoder-- ######

###### --Initial values for grapher-- ######
vals = np.zeros(6)   # empty array to store all values
val_names = ["val1", "val2", "val3", "val4", "val5", "val6"]   # names of these values
will_rec = np.array([True, False, True, True, False, False])   # will these values be recorded?
will_graph = np.array([True, True, True, False, False, False])   # will these values be graphed?
val_colors = np.array([rgb.red, rgb.lime, rgb.blue, rgb.black, rgb.purple, rgb.cyan])   # colors for these values

graph_line_num = 3   # initial number of lines on graph
vals_graph = np.zeros(graph_line_num)   # empty array to store values that are graphed
colors_graph = np.array([rgb.red, rgb.lime, rgb.blue], dtype=object)   # initial colors for graphed values

rec_num = 3   # initial number of values to be recorded
names_rec = np.array(["val1", "val3", "val4"])   # initial values names to be recorded
colors_rec = np.array(["(255, 0, 0)", "(0, 0, 255)", "(0, 0, 0)"], dtype=object)   # initial colors for recorded values
vals_rec = np.zeros(rec_num)   # empty list of vals to be recorded

grapher.set_line_color(graph_line_num, colors_graph)   # update line colors



###### --Load settings-- ######
try:
    antial, sound_volume, zoom, lang = fileops.load_settings()   # try to load settings from file
except:
    setfile = open("data/settings.txt","w+")   # create settings file
    setfile.write(str(antial)+' '+str(sound_volume)+' '+str(zoom)+' '+lang+' ')   # write to settings file
    setfile.close()   # close file
    whelp = True   # Show help
    welcome = True   # print welcome text



###### --Load texts-- ######
languages = np.loadtxt("txt/languages.txt", dtype='str')   # languages list
with open("txt/"+lang+"/texts.txt") as texts: texts_arr = texts.readlines()   # texts
with  open("txt/"+lang+"/about.txt") as fabout_txt: about_txt = fabout_txt.readlines()   # about text
about_txt[0] = about_txt[0].rstrip() + " " + version
about_txt[1] = date



###### --initialize GUI-- ######
pygame.init()   # initialize pygame
pygame.display.set_icon(pygame.image.load('img/icon.png'))   # set game icon
screen = pygame.display.set_mode((windowx, windowy))   # set window size
gui = pygame.image.load("img/gui.png")
menu = pygame.image.load("img/menu.png")
fontlg = pygame.font.Font("txt/fonts/LiberationSans-Regular.ttf", 18)   # large text font
fontmd = pygame.font.Font("txt/fonts/LiberationSans-Regular.ttf", 16)   # medium text font
fontsm = pygame.font.Font("txt/fonts/LiberationSans-Regular.ttf", 15)   # small text font
fontxl = pygame.font.Font("txt/fonts/LiberationSans-Regular.ttf", 20)   # extra large text font
fontsb = pygame.font.Font("txt/fonts/LiberationSans-Bold.ttf", 14)   # small bold text font
clock = pygame.time.Clock()   # start clock
# how many times calculations event is repeated in one iterration of main loop
pygame.time.set_timer(pygame.USEREVENT, int(100/simspeed))



###### --Classes settings-- ######
screens.config(screen, windowx, windowy, lang)
logger.gui_max_width(60)   # max text width



###### --Main loop-- ######
run = True
while run:
    for e in pygame.event.get():
        if e.type == pygame.KEYDOWN:   # if any key is pressed:
            # --Key setup-- #
            if e.key == pygame.K_ESCAPE: run = False  # if "escape" key is pressed, close program
            if e.key == pygame.K_p:   # if "P" key is pressed:
                if pause is False: pause = True   # if it is not paused, pause it 
                else: pause = False  # if it is paused, unpause it
        
        
        
        ###### -- Button engine-- ######
        mouse = pygame.mouse.get_pos()   # get mouse position
        if e.type == pygame.MOUSEBUTTONDOWN:   # if mouse clicked:
            
            # main menu
            if settings is False and whelp is False and wabout is False and graph_picker is False and rec_show is False:
                if 177 < mouse[0] < 207 and 1 < mouse[1] < 31:   # start / stop
                    if pause is False: 
                        pause = True    # pause
                        logger.log_add("Paused", rgb.red)   # GUI logger example
                    else: 
                        pause = False   # unpause
                        logger.log_add("Unpaused", rgb.lime)   # GUI logger example
                if 177 < mouse[0] < 207 and 32 < mouse[1] < 62:   # record
                    if record is False: 
                        record = True    # start
                        grapher.record_start(names_rec, colors_rec)   # start recording
                        logger.log_add("Recording started") 
                    else: 
                        record = False   # stop
                        grapher.record_stop()   # stop recording
                        logger.log_add("Recording stopped. Saved in records directory.")
                if 208 < mouse[0] < 238 and 1 < mouse[1] < 31:   # sound
                    if sound is False: sound = True    # unmute
                    else: sound = False   # mute
                if 208 < mouse[0] < 238 and 32 < mouse[1] < 62: rec_show = pause = True   # show recorded
                if 239 < mouse[0] < 269 and 32 < mouse[1] < 62:   # simulation speed minus
                    if simspeed >= 0.15:   # if simulation speed is over minimal:
                        if simspeed <= 1.2: simspeed -= 0.1   # if simspeed is bellow 1.2 decrease by 0.1
                        if simspeed > 1.2: simspeed -= 0.2   #if simspeed is above 1.2 decrease by 0.2
                        pygame.time.set_timer(pygame.USEREVENT, int(100/simspeed))   # update simspeed
                if 332 < mouse[0] < 362 and 32 < mouse[1] < 62:   # simulation speed plus
                    if simspeed <= 9.9:
                        if simspeed < 1.2: simspeed += 0.1
                        if simspeed >= 1.2: simspeed += 0.2
                        pygame.time.set_timer(pygame.USEREVENT, int(100/simspeed))
                if 425 < mouse[0] < 455 and 1 < mouse[1] < 31: settings = pause = True  # switch to settings
                if 363 < mouse[0] < 393 and 1 < mouse[1] < 31: graph_picker = pause = True   # switch to graph picker
                if 425 < mouse[0] < 455 and 32 < mouse[1] < 62: whelp = pause = True   # switch to help
                if 456 < mouse[0] < 486 and 32 < mouse[1] < 62: wabout = pause = True   # switch to about
                if 456 < mouse[0] < 486 and 1 < mouse[1] < 31: run = False   # quit
            
            # graph picker
            if graph_picker is True:
                for num, val_name in enumerate(val_names):   # for every value:
                    if 1 < mouse[0] < 40 and 62 + num * 30 < mouse[1] < 62 + num * 30 + 29:   # recorder
                        will_rec[num] = not will_rec[num]   # invert: False <-> True
                    if 41 < mouse[0] < 80 and 62 + num * 30 < mouse[1] < 62 + num * 30 + 29:   # grapher
                        will_graph[num] = not will_graph[num]   # invert: False <-> True
                    if 81 < mouse[0] < 130 and 62 + num * 30 < mouse[1] < 62 + num * 30 + 29:   # colors
                        cur_color = 0   # current color
                        for row_num, row in enumerate(rgb.all_main):   # for all colors in array:
                            if np.array_equal(val_colors[num], row):   # if current color is same as color in array
                                cur_color = row_num   # output index of it
                                break   # break loop
                        if cur_color == len(rgb.all_main) - 1:   # if this is last color in list:
                            cur_color = -1   # rotate to start (-1 becouse later it will be returned to 0)
                        val_colors[num] = rgb.all_main[cur_color + 1]   # move to next color in array
                graph_line_num = len(np.delete(will_graph, np.where(will_graph == False)))   # new number of graph lines
                vals_graph = np.zeros(graph_line_num)   # empty list of vals to be on graph
                colors_graph = np.zeros(graph_line_num, dtype=object)   # resize output color list
                rec_num = len(np.delete(will_rec, np.where(will_rec == False)))   # new number of vals to be recorded
                vals_rec = np.zeros(rec_num)   # empty list of vals to be recorded
                names_rec = np.zeros(rec_num, dtype=object)   # empty list of val names to be recorded
                colors_rec = np.zeros(rec_num, dtype=object)   # resize record color list
                if 0 < mouse[0] < 31 and 1 < mouse[1] < 31:   # back
                    graph_picker = False   # back
                    num_out = 0   # iterable value for output list
                    for num, check in enumerate(will_rec):   # iterate over all variables
                        if check == True:   # if this value is marked to be recorded:
                            colors_rec[num_out] = tuple(val_colors[num])   # add its color to output list
                            names_rec[num_out] = val_names[num]   # add its name to output list
                            num_out += 1   # iterate output list
                    num_out = 0   # iterable value for output list
                    for num, check in enumerate(will_graph):   # iterate over all variables
                        if check == True:   # if this value is marked to be plotted:
                            colors_graph[num_out] = val_colors[num]   # add its color to output list
                            num_out += 1   # iterate output list
                    grapher.set_line_color(graph_line_num, colors_graph)   # update grapher colors
                if record is True:   # if recording is active:
                    record = False   # stop recording
                    grapher.record_stop()   # stop recording
                    logger.log_add("Recording stopped. Saved in records directory.")
                    
            # settings
            if settings is True:
                if 456 < mouse[0] < 486 and 1 < mouse[1] < 31:   # cancle settings changes:
                    settings = False   # exit settings
                    antial, sound_volume, zoom, lang = fileops.load_settings()   # reload settings from file
                if 456 < mouse[0] < 486 and 32 < mouse[1] < 62:   # save settings
                    settings = False   # exit settings
                    setfile = open("data/settings.txt","w+")   # open settings file
                    setfile.write(str(antial)+' '+str(sound_volume)+' '+str(zoom)+' '+lang+' ')   # write to settings file
                    setfile.close()   # close file
                if 177 < mouse[0] < 207 and 1 < mouse[1] < 31:    # turn on antialias
                    if antial is False: antial = True
                    else: antial = False   # turn off antial
                if 208 < mouse[0] < 238 and 1 < mouse[1] < 31 and sound_volume > 1: sound_volume -= 1  # sound volume minus
                if 301 < mouse[0] < 331 and 1 < mouse[1] < 31 and sound_volume < 10: sound_volume += 1  # sound volume plus
                if 208 < mouse[0] < 238 and 32 < mouse[1] < 62 and zoom > 1: zoom -= 1   # zoom minus
                if 301 < mouse[0] < 331 and 32 < mouse[1] < 62 and zoom < 5: zoom += 1   # zoom plus
                if 177 < mouse[0] < 207 and 32 < mouse[1] < 62:    # change language
                    lang = languages[lang_num]   # load language
                    lang_num +=1   # iterate over languages
                    if lang_num >= len(languages): lang_num = 0   # rotate lang num
                    logger.log_add(str((texts_arr[5]).rstrip()), rgb.black)   # print that simulation must restart
                    
            # help window
            if whelp is True:
                if whelp_all is False:   # if help all is closed:
                    if 177 < mouse[0] < 207 and 1 < mouse[1] < 31: whelp = False   # back
                    if 208 < mouse[0] < 238 and 1 < mouse[1] < 31: whelp_all = True  # help all
                if whelp_all is True: # if help all is open:
                    if 177 < mouse[0] < 207 and 1 < mouse[1] < 31: whelp_all = False   # back
                    
            # about window
            if wabout is True:
                if 625 < mouse[0] < 656 and 16 < mouse[1] < 47: wabout = False   # back
                if 680 < mouse[0] < 711 and 222 < mouse[1] < 253:   # open github link
                    webbrowser.open(r"https://github.com/mzivic7/Simulation-Chernobyl")
                # if 680 < mouse[0] < 711 and 255 < mouse[1] < 286:   # open wiki link
                    # webbrowser.open(r"")   # ###
                if 680 < mouse[0] < 711 and 289 < mouse[1] < 320:   # open report bug link
                    webbrowser.open(r"https://github.com/mzivic7/Simulation-Chernobyl/issues")
            
            # show records
            if rec_show is True:
                if 0 < mouse[0] < 31 and 1 < mouse[1] < 31: rec_show = False   # back
                if os.path.isdir("records") is False: os.mkdir("records")   # if there is no records dir: create it
                records = os.listdir("records")   # get list of all records
                if not records:   # if there are no files
                    rec_show = False   # dont show records menu
                    logger.log_add("There are no saved records.")
                else:
                    for num in range(len(records)):   # for every file position:
                        if 0 < mouse[0] < 200 and 31 + num * 31 < mouse[1] < 62 + num * 31: 
                            sel_record = num   # select record
                    with open("records/" + records[sel_record]) as file: 
                        file_lines = file.readlines()   # read all lines in array
                        header_record = file_lines[0].replace("\n", "").replace("time,", "").split(",")   # read csv val names
                        color_record = file_lines[1]   # read csv val colors
                    read_record = np.genfromtxt("records/" + records[sel_record], delimiter=',', skip_header = 2)   # read csv vals
                    if len(read_record) == 0:   # if there are no data
                        read_record = np.zeros([2,len(header_record) + 1])   # add zeros to prevent graph errors
                        color_record = '"(255, 255, 255),"' * len(header_record)   # color all lines white to hide them
                if 31 < mouse[0] < 62 and 0 < mouse[1] < 31:   # save graph image
                    sub = screen.subsurface(pygame.Rect(201, 1, 1079, 719))
                    now_time = datetime.datetime.now()   # get current date and time
                    now_time_short = (now_time.strftime("%Y-%m-%d %H-%M-%S"))   # remove milliseconds
                    if os.path.isdir("screenshots") is False: os.mkdir("screenshots")   # if there is no screenshots dir, create it
                    pygame.image.save(sub, "screenshots/Screenshot from " + now_time_short + ".png")   # save screenshot
                if record is True:   # if recording is active:
                    record = False   # stop recording
                    grapher.record_stop()   # stop recording
                    logger.log_add("Recording stopped. Saved in records directory.")
                
                        
        # mouse wheel
        if e.type == pygame.MOUSEWHEEL:   # if event is mouse whell
            mouse_wheel = e.y   # store its movement in variable as -1 and 1
                
                
        
        ###### --Calculations-- ######
        if e.type == pygame.USEREVENT:   # event for calculations
            if pause is False:   # if it is not paused:
                
                ###### --Engine-- ######
                
                vals[0] = 88 + (math.sin(counter/2))*50   # test values
                vals[1] = 88 + (math.sin((counter/2)+(2*math.pi/3)))*50
                vals[2] = 88 + (math.sin((counter/2)+(4*math.pi/3)))*50
                vals[3] = 88
                vals[4] = 44
                vals[5] = 132
                
                num_out = 0   # iterable value for output list
                for num, check in enumerate(will_graph):
                    if check == True:   # if this value is marked to be plotted:
                        vals_graph[num_out] = vals[num]   # add it to output list
                        num_out += 1   # iterate output list
                grapher.add_val(counter, vals_graph)   # add values to graph
                
                num_out = 0   # iterable value for output list
                if record is True:
                    for num, check in enumerate(will_rec):
                        if check == True:   # if this value is marked to be plotted:
                            vals_rec[num_out] = vals[num]   # add it to output list
                            num_out += 1   # iterate output list
                    grapher.rec_val(counter, vals_rec)   # record values to file
                    
                counter += counter_step   # iterate counter
                counter = round(counter, 2)   # round counter to one decimal
        
        if e.type == pygame.QUIT: run = False   # if exited, break loop
    
    
    
    ###### --Graphics-- ######
    screen.fill((255, 255, 255))   # color screen white
    screen.blit(gui, (0, 0))   # show gui image
    screen.blit(menu, (176, 0))   # show main menu image
    grapher.draw_graph(screen, antial)   # draw graph
    
    # main screen texts
    screen.blit(fontlg.render(str(datetime.timedelta(seconds=round(counter))), True, rgb.black), (270, 5))   # counter time
    screen.blit(fontlg.render(str(round(simspeed, 2)), True, rgb.black), (288, 36))   # simulation speed
    logger.gui_logger(screen, fontsm)   # gui logger
    if welcome is True:   # if this is first time running: print welcome text in logger
        logger.log_add(str((texts_arr[0]).rstrip()), textout_color)
        logger.log_add(str((texts_arr[1]).rstrip()), textout_color)
        logger.log_add(str((texts_arr[2]).rstrip()), textout_color)
        welcome = False

    if settings is False and whelp is False and wabout is False and graph_picker is False:
        screens.main(mouse, pause, sound, record)   # main menu
    if settings is True:
        screens.settings(mouse, antial, sound_volume, zoom, lang)   # settings
    if graph_picker is True:
        screens.picker(mouse, vals, val_names, val_colors, will_rec, will_graph)   # graph value picker
    if whelp is True:
        screens.help(mouse, whelp_all, lang, texts_arr)   # help
    if wabout is True:
        screens.about(mouse, about_txt)   # about
    if rec_show is True:   # show recorded values
        screens.rec_show(mouse, mouse_wheel, records, sel_record, read_record, header_record, color_record, antial)   # show records
        mouse_wheel = 0   # reset mouse whell state
    
    screen.blit(fontlg.render(str(mouse), True, rgb.black), (5, 695))   # show mouse coordinates
    
    pygame.display.flip()   # update screen
    clock.tick(update)   # screen update frequency

pygame.quit()
