import pygame
import numpy as np
from ..graphics import graphics as gr
from ..graphics import rgb

class Screens():
    def __init__(self):
        self.windowx, self.windowy = 1280, 720
        self.surface = pygame.display.set_mode((self.windowx, self.windowy))
    
    # load everything needed
    def config(self, surface, windowx, windowy, lang):
        self.surface, self.windowx, self.windowy = surface, windowx, windowy
        self.gui = pygame.image.load("img/gui.png")   # load images
        self.menu = pygame.image.load("img/menu.png")
        self.setmenu = pygame.image.load("img/settings.png")
        self.runbt = pygame.image.load("img/run.png")
        self.stopbt = pygame.image.load("img/stop.png")
        self.soundon = pygame.image.load("img/sound.png")
        self.soundoff = pygame.image.load("img/mute.png")
        self.help_gui = pygame.image.load("img/help_gui.png")
        self.back = pygame.image.load("img/back.png")
        self.help_graph_all = pygame.image.load("img/help_all.png")
        self.rods_help = pygame.image.load("img/rods.png")
        self.link = pygame.image.load("img/link.png")
        self.accept = pygame.image.load("img/accept.png")
        self.cancle = pygame.image.load("img/cancle.png")
        self.camera = pygame.image.load("img/camera.png")
        self.fontlg = pygame.font.Font("txt/fonts/LiberationSans-Regular.ttf", 18)   # large text font
        self.fontmd = pygame.font.Font("txt/fonts/LiberationSans-Regular.ttf", 16)   # medium text font
        self.fontsm = pygame.font.Font("txt/fonts/LiberationSans-Regular.ttf", 15)   # small text font
        self.fontxl = pygame.font.Font("txt/fonts/LiberationSans-Regular.ttf", 20)   # extra large text font
        self.fontsb = pygame.font.Font("txt/fonts/LiberationSans-Bold.ttf", 14)   # small bold text font
        # load matrices containing names, mouseover and center coords for help surface
        self.moverbox = np.loadtxt("data/coords.txt", dtype='int', delimiter=',')
        self.rods_moverbox = np.loadtxt("data/rods_coords.txt", dtype='int', delimiter=',')
        self.graph_names_l = np.loadtxt("txt/"+lang+"/graph_coords_l.txt", dtype=object, delimiter=',')
        self.graph_names_r = np.loadtxt("txt/"+lang+"/graph_coords_r.txt", dtype=object, delimiter=',')
        self.graph_names_rods = np.loadtxt("txt/"+lang+"/graph_coords_rods.txt", dtype=object, delimiter=',')
        with open("txt/"+lang+"/expl.txt") as expl: self.explarr = expl.readlines()   # explanations
        with open("txt/"+lang+"/gui_expl.txt") as gui_expl: self.gui_explarr = gui_expl.readlines()   # gui explanations
        with open("txt/"+lang+"/rods_expl.txt") as rods_expl: self.rods_explarr = rods_expl.readlines()   # rods explanations
        with open("txt/"+lang+"/texts.txt") as texts: self.texts_arr = texts.readlines()   # texts
        self.graph_index = 0
        
    # main menu, without main screen
    def main(self, mouse, pause, sound, record):
        if pause is True: pygame.draw.rect(self.surface, rgb.green1, (177,1,30,30)) # if simulation is paused: color it
        if record is True: pygame.draw.rect(self.surface, rgb.red1, (177,32,30,30)) # if recording: color it
        gr.mouseover_group(self.surface, mouse)   # draw rectangles if mouse is over button
        gr.mouseover(self.surface, 2, 1, rgb.gray1, mouse)   # simulation speed minus
        gr.mouseover(self.surface, 9, 1, rgb.gray1, mouse)   # about
        if pause is True: self.surface.blit(self.runbt, (177, 1))   # if simulation is paused: show image
        else: self.surface.blit(self.stopbt, (177, 1))
        if sound is True: self.surface.blit(self.soundon, (208, 1))   # if sound is on
        else: self.surface.blit(self.soundoff, (208, 1))
        self.surface.blit(self.menu, (176, 0))      # show main menu image again because of mouseover effects
    
    # settings menu
    def settings(self, mouse, antial, sound_volume, zoom, lang):
        pygame.draw.rect(self.surface, (255,255,255), (177,1,309,61))   # hide main menu
        if antial is True: pygame.draw.rect(self.surface, rgb.green1, (177,1,30,30))
        gr.mouseover_group(self.surface, mouse)   # mouseover effects for main menu
        gr.mouseover(self.surface, 1, 0, rgb.gray1, mouse)   # - sound
        gr.mouseover(self.surface, 4, 0, rgb.gray1, mouse)   # + sound
        gr.mouseover(self.surface, 5, 0, rgb.gray1, mouse)   # X
        gr.mouseover(self.surface, 4, 1, rgb.gray1, mouse)   # + zoom
        gr.mouseover(self.surface, 9, 1, rgb.green1, mouse)  # save
        self.surface.blit(self.setmenu, (177, 1))   # show settings menu img
        self.surface.blit(self.fontlg.render("V:" + str(sound_volume), True, rgb.black), (248, 6))   # sound volume text
        self.surface.blit(self.fontlg.render("Z:" + str(zoom), True, rgb.black), (248, 37))   # graph zoom text
        self.surface.blit(self.fontsm.render(lang, True, rgb.black), (180, 37))   # languages
    
    # graph values picker
    def picker(self, mouse, vals, val_names, val_colors, will_rec, will_graph):
        pygame.draw.rect(self.surface, (255,255,255), (1,1,self.windowx-2,self.windowy-2))   # blank screen
        gr.mouseover_coord(self.surface, 1, 1, rgb.gray1, mouse)   # back button mouseover effect
        self.surface.blit(self.back, (0, 0))   # back button
        # lines
        line_pos = 31   # horizontal lines start
        while line_pos < self.windowy - 28:
            pygame.draw.line(self.surface, rgb.black, (0, line_pos), (self.windowx, line_pos))   # draw horizontal lines
            line_pos += 30   # space between 2 lines
        vertical_lines = [0, 40, 80, 130, 490, 638, 680, 720, 770, 1130]   # where will be drawn verticallines
        for vline in vertical_lines:
            pygame.draw.line(self.surface, rgb.black, (vline, 31), (vline, self.windowy))   # draw vertical lines
            if vline == vertical_lines[5]:   # if it is middle line: draw more one line next to it
                pygame.draw.line(self.surface, rgb.black, (vline + 2, 31), (vline + 2, self.windowy))
        # texts
        self.surface.blit(self.fontmd.render(str((self.texts_arr[6]).rstrip()), True, rgb.black), (40, 7))   # explanation text
        for word_repeat in range(2):   # repeat it twice:
            if word_repeat == 1: vertical_lines = vertical_lines[5:]   # in second iterration move to right side
            for word_num, word in enumerate(self.texts_arr[7].replace("\n", "").split(" ")):   # for every word
                word_pos = vertical_lines[word_num] + 6   # increase word position by line position
                self.surface.blit(self.fontmd.render(word, True, rgb.black), (word_pos, 38))   # print column names
        for num, val_name in enumerate(val_names):   # for every value:
            column = 0   # on what side should be written, default = left
            if 62 + num * 30 > self.windowy: # if there is no more space on left:
                column = 640   # write on right side
                # num -=   ### ### ###
            pygame.draw.rect(self.surface, val_colors[num], (81 + column, 62 + num * 30, 49, 29))   # value color
            self.surface.blit(self.fontmd.render(val_name, True, rgb.black), (136 + column, 68 + num * 30))   # value name
            self.surface.blit(self.fontmd.render(str(round(vals[num], 2)), True, rgb.black), (496 + column, 68 + num * 30))   # value
            if will_rec[num] == True:   # if this value will be recorded:
                pygame.draw.rect(self.surface, rgb.green1, (1 + column, 62 + num * 30, 39, 29))   # background color green
                self.surface.blit(self.accept, (5 + column, 62 + num * 30))   # show accept
            else:   # if not:
                pygame.draw.rect(self.surface, rgb.red1, (1 + column, 62 + num * 30, 39, 29))   # background color red
                self.surface.blit(self.cancle, (5 + column, 62 + num * 30))   # show X
            if will_graph[num] == True:   # if this value will be graphed:
                pygame.draw.rect(self.surface, rgb.green1, (41 + column, 62 + num * 30, 39, 29))   # background color green
                self.surface.blit(self.accept, (45 + column, 62 + num * 30))   # show accept
            else:   # if not:
                pygame.draw.rect(self.surface, rgb.red1, (41 + column, 62 + num * 30, 39, 29))   # background color red
                self.surface.blit(self.cancle, (45 + column, 62 + num * 30))   # show X
    
    # help screen
    def help(self, mouse, whelp_all, lang, texts_arr):
        gr.mouseover(self.surface, 0, 0, rgb.gray1, mouse)   # back button mouseover effect
        self.surface.blit(self.back, (176, 0))   # back button
        gr.mouseover(self.surface, 8, 1, rgb.green1, (426, 33))   # make help button lime
        self.surface.blit(self.menu, (176, 0))      # show main menu image again because of mouseover effects
        self.surface.blit(self.help_graph_all, (208, 1))   # all help diagram button
        pygame.draw.rect(self.surface, (255,255,255), (177,271,109,267))   # hide part of left imputs
        pygame.draw.rect(self.surface, (255,255,255), (1,539,360,180))   # hide graph
        pygame.draw.line(self.surface, rgb.black, (176, 271), (176, 537))   # draw border over that hidden part
        pygame.draw.rect(self.surface, (255,255,255), (1104,1,175,718))   # hide right inputs
        self.surface.blit(self.rods_help, (294, 549))   # rods help picture
        self.surface.blit(self.fontlg.render(str((texts_arr[4]).rstrip()), True, rgb.black), (5,543))   # inside core text
        
        # normal help with mouseover
        if whelp_all is False:
            gr.mouseover(self.surface, 1, 0, rgb.gray1, mouse)   # help diagram button
            self.surface.blit(self.help_graph_all, (208, 1))   # help diagram button
            self.surface.blit(self.help_gui, (1107,4))   # show gui help 
            self.surface.blit(self.fontsm.render(lang, True, rgb.black), (1111, 630))   # add language name to gui help
            for line_num, lines in enumerate(self.gui_explarr):   # for each line in gui explanations:
                # print that line in new row
                self.surface.blit(self.fontsm.render(str((self.gui_explarr[line_num]).rstrip()), True, rgb.black), (1145, int(4+(line_num*15.5))))
            # explanation text
            gr.text_wrap(self.surface, str((texts_arr[3]).rstrip()), (5 ,5, 177, 530), self.fontsm, self.fontsm, rgb.black) 
            # main explanations
            for line_num, lines in enumerate(self.moverbox):   # for every line in file: (line contains coords of box)
                if lines[0] < mouse[0] < lines[2] + 1 and lines[1] < mouse[1] < lines[3] + 1:   # if mouse is over it
                    pygame.draw.line(self.surface, rgb.black, (165, 75), (190, 75))   # draw straight line
                    pygame.draw.line(self.surface, rgb.black, (190, 75), (lines[4], lines[5]))   # draw line conecting box
                    # draw outline
                    pygame.draw.rect(self.surface, rgb.black, (lines[0],lines[1],lines[2]-lines[0]+1,lines[3]-lines[1]+1), 1)
                    # print text
                    gr.text_wrap(self.surface, str((self. explarr[line_num]).rstrip()), (5 ,67, 172, 530),self.fontsm, self.fontsb, rgb.black)
            # rods explanations
            for line_num, lines in enumerate(self.rods_moverbox):   # for every line in file: (line contains coords of box)
                if lines[0] < mouse[0] < lines[2] + 1 and lines[1] < mouse[1] < lines[3] + 1:   # if mouse is over it
                    # draw outline
                    pygame.draw.rect(self.surface, rgb.black, (lines[0],lines[1],lines[2]-lines[0]+1,lines[3]-lines[1]+1), 1)
                    # print text
                    gr.text_wrap(self.surface, str((self. rods_explarr[line_num]).rstrip()), (5 ,565, 285, 720),self.fontsm, self.fontsb, rgb.black)
                       
        # all help
        if whelp_all is True:
            gr.mouseover(self.surface, 1, 0, rgb.green1, (209, 2))   # make all_help button lime
            self.surface.blit(self.help_graph_all, (208, 1))   # show all_help buton again
            gr.text_lines(self.surface, self.graph_names_l[:,6], (5,5,172,520), self.fontsb, 6)   # left all help
            gr.connect_lines(self.surface, self.graph_names_l, (177, 2, 22))   # draw lines connecting left text to elements
            gr.text_lines(self.surface, self.graph_names_r[:,6], (1110,5,1280,520), self.fontsb, 6)   # right all help
            gr.connect_lines(self.surface, self.graph_names_r, (1103, 2, 22))   # draw lines connecting right text to elements
            gr.text_lines(self.surface, self.graph_names_rods[:,6], (5,565,172,520), self.fontsb, 6)   # rods all help
            gr.connect_lines(self.surface, self.graph_names_rods, (177, 562, 22))   # draw lines connecting rods text to elements
            pygame.draw.line(self.surface, rgb.black, (176, 538), (176, 719))   # names border extended line
    
    # about screen
    def about(self, mouse, about_txt):
        pygame.draw.rect(self.surface, (255,255,255), (1,1,self.windowx-2,self.windowy-2))   # blank screen
        gr.mouseover_coord(self.surface, 625, 16, rgb.gray1, mouse)   # back button mouseover effect
        self.surface.blit(self.back, (624, 15))   # back button
        gr.text_lines(self.surface, about_txt, (529,60,800,500), self.fontxl, 10)   # show about text
        gr.mouseover_coord(self.surface, 680, 222, rgb.gray1, mouse)
        gr.mouseover_coord(self.surface, 680, 256, rgb.gray1, mouse)
        gr.mouseover_coord(self.surface, 680, 290, rgb.gray1, mouse)
        self.surface.blit(self.link, (679, 221))   # github button
        self.surface.blit(self.link, (679, 255))   # wiki button
        self.surface.blit(self.link, (679, 289))   # report bug button

    # show recorded
    def rec_show(self, mouse, mouse_wheel, records, sel_record, read_record, header_record, color_record, antial):
        pygame.draw.rect(self.surface, (255,255,255), (1,1,self.windowx-2,self.windowy-2))   # blank screen
        gr.mouseover_coord(self.surface, 1, 1, rgb.gray1, mouse)   # back button mouseover effect
        gr.mouseover_coord(self.surface, 32, 1, rgb.gray1, mouse)   # save image button mouseover effect
        self.surface.blit(self.back, (0, 0))   # back button
        self.surface.blit(self.camera, (32, 1))   # save image button
        # lines
        pygame.draw.line(self.surface, rgb.black, (200, 0), (200, self.windowy))   # vertical line
        pygame.draw.line(self.surface, rgb.black, (62, 1), (62, 31))   # vertical line button 2
        pygame.draw.line(self.surface, rgb.black, (93, 1), (93, 31))   # vertical line button 3
        pygame.draw.line(self.surface, rgb.black, (200, 620), (self.windowx, 620))   # horizontal line legend
        pygame.draw.line(self.surface, rgb.black, (200, 602), (self.windowx, 602))   # horizontal time scale line
        pygame.draw.line(self.surface, rgb.black, (0, 31), (200, 31))   # horizontal explanation line
        gr.mouseover_coord(self.surface, 1, 32 + sel_record * 31, rgb.gray1, (5, 35 + sel_record * 31), 200, 31)   # selected record
        # record picker
        self.surface.blit(self.fontmd.render(str((self.texts_arr[8]).rstrip()), True, rgb.black), (99, 7))   # explanation text
        for num, recording in enumerate(records):   # for every file:
            gr.mouseover_coord(self.surface, 1, 32 + num * 31, rgb.gray1, mouse, 200, 31)   # mouseover effect
            # print its name
            self.surface.blit(self.fontmd.render(recording.replace("Recording from ", ""), True, rgb.black), (5, 38 + num * 31))
            pygame.draw.line(self.surface, rgb.black, (0, 31 + num * 31), (200, 31 + num * 31))   # separator line
        pygame.draw.line(self.surface, rgb.black, (0, 62 + num * 31), (200, 62 + num * 31))   # end line
        # graph legend
        self.surface.blit(self.fontmd.render(str((self.texts_arr[9]).rstrip()), True, rgb.black), (1036, 626))   # explanation text
        self.surface.blit(self.fontmd.render(str((self.texts_arr[10]).rstrip()), True, rgb.black), (1036, 648))   # explanation text
        row = 0   # in which row is writting
        dif = 0   # difference for nex row
        column = 0   # in which column is writting
        color_record = color_record.replace("\n", "").replace('"', '').replace('(', '').split("),")   # colors string to list
        for num, val_name in enumerate(header_record):   # for every value:
            if 626 + 44 + row * 22 > self.windowy:   # if there are no more rows:
                column += 200   # write in new column
                dif = num   # update difference
            row = num - dif   # return to 0 row
            # color_record is read as list, not list of tuples
            color = tuple(list(map(int, color_record[num].replace(")", "").split(", "))))   # get tuple from list of strings
            self.surface.blit(self.fontsm.render(val_name, True, color), (206 + column, 626 + row * 22))   # value name
        # graph
        if mouse_wheel != 0:   # if mouse wheel has moved
            self.graph_index += mouse_wheel * 15   # add it to graph index
            mouse_wheel = 0   # reset it
        if self.graph_index < 0: self.graph_index = 0   # prevent index from going negative
        if self.graph_index > len(read_record) - 1078: self.graph_index = len(read_record) - 1078   # stop index from going over max
        display_vals = read_record[self.graph_index : self.graph_index + 1078, :]   # get slice of vals from graph index
        val_out = np.zeros([1078,2])   # array to separately store vals to be graphed
        val_out[:,0] = range(201, 1279)   # add x values to it
        for num, column in enumerate(display_vals.T):   # for every column in val array, (transpose to read rows)
            if num != 0:   # skip first column - it is x value
                val_out[0:len(column),1] = 601 - column   # add y and graph position
                color = tuple(list(map(int, color_record[num - 1].replace(")", "").split(", "))))   # get tuple from list of strings
                if antial is True: pygame.draw.aalines(self.surface, color, False, val_out, 2)   # draw graphed lines
                else: pygame.draw.lines(self.surface, color, False, val_out, 2)   # draw graphed lines
        # time scale
        if display_vals[1, 0] != 0:   # if there is existing data (second time value is not 0)
            for num, time in enumerate(display_vals[:, 0]):   # for every time value in time column 
                if time % 1 == 0:   # if divisable with 1
                    pygame.draw.line(self.surface, rgb.black, (200 + num, 602), (200 + num, 605))   # ones line
                    if time % 5 == 0:   # if divisable with 5
                        if time % 10 == 0:   # if divisable with 10
                            self.surface.blit(self.fontsm.render(str(round(time)), True, rgb.black), (202 + num, 603))   # number
                            pygame.draw.line(self.surface, rgb.black, (200 + num, 602), (200 + num, 615))   # tens line
                        else:   # if not divisable with 10 but with 5
                            self.surface.blit(self.fontsm.render(str(round(time)), True, rgb.gray), (202 + num, 603))  # number
                            pygame.draw.line(self.surface, rgb.black, (200 + num, 602), (200 + num, 610))   # fives line
        else: # if there is no data: print explanation
            self.surface.blit(self.fontmd.render(str((self.texts_arr[11]).rstrip()), True, rgb.black), (206, 626))
                
        
        
        
        
