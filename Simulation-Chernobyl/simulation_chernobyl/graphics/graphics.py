import pygame
import numpy as np
from ..graphics import rgb

# mouseover button effect, buttons are numerated by position
def mouseover(surface, x, y, color, mouse):
    if 177 + x * 31 < mouse[0] < 177 + x * 31 + 30 and 1 + y * 31 < mouse[1] < 1 + y * 31 + 30:   # if mouse is over button:
        pygame.draw.rect(surface, color, (177 + x * 31,1 + y * 31,30,30))  # color it

# mouseover button effect, buttons are defined by coordinates
def mouseover_coord(surface, x, y, color, mouse, x1=31, y1=31):
    if x < mouse[0] < x + x1 and y < mouse[1] < y + y1:   # if mouse is over button:
        pygame.draw.rect(surface, color, (x, y, x1 - 1, y1 -1))  # color it

# group of mouseover button effects
def mouseover_group(surface, mouse):
    # button location                            main set                  settings set
    mouseover(surface, 0, 0, rgb.gray1, mouse)   # start / stop            # antialiasing
    mouseover(surface, 1, 0, rgb.gray1, mouse)   # sound switch            # - sound
    mouseover(surface, 6, 0, rgb.gray1, mouse)   # graph picker            # X
    mouseover(surface, 7, 0, rgb.gray1, mouse)   # save                    # X
    mouseover(surface, 8, 0, rgb.gray1, mouse)   # settings                # X
    mouseover(surface, 9, 0, rgb.red1, mouse)    # quit                    # cancle
    mouseover(surface, 0, 1, rgb.gray1, mouse)   # record                  # language
    mouseover(surface, 1, 1, rgb.gray1, mouse)   # show recorded graph     # - zoom
    mouseover(surface, 5, 1, rgb.gray1, mouse)   # simulation speed plus   # X
    mouseover(surface, 6, 1, rgb.gray1, mouse)   # X                       # X
    mouseover(surface, 7, 1, rgb.gray1, mouse)   # load                    # X
    mouseover(surface, 8, 1, rgb.gray1, mouse)   # help                    # X

# prints text in box with word wrapping, with separator for bold tittle
def text_wrap(surface, text, pos, font, tittle_font, color=(0,0,0)):
    words = text.split(' ')   # convert string to list of words
    space = font.size(' ')[0]   # the width of a space
    x, y, maxw, maxh = pos   # get dimensions
    outfont = tittle_font   # set font to tittle font
    for word in words:   # for each word in list:
        word_surf = outfont.render(word, True, color)   # create word surface
        wordw, wordh = word_surf.get_size()   # get word size
        if x + wordw >= maxw or word == "///":   # if word goes over max or word is separator mark
            x = pos[0]   # reset x
            y += wordh   # start on new row
            if word == "///": outfont = font   # if word is separator mark change font to normal
        if word != "///":   # if word is not separator mark:
            surface.blit(word_surf, (x, y))   # show word
            x += wordw + space   # go to next word position

# prints text in box with word wrapping by readding line by line
def text_lines(surface, text_list, pos, font, line_space=0, color=(0,0,0)):
    x, y, maxw, maxh = pos   # get dimensions
    space = font.size(' ')[0]   # the width of a space
    for line_num, line in enumerate(text_list):   # for each row
        words = str((text_list[line_num]).rstrip()).split(' ')   # convert string to list of words
        x = pos[0]   # x dimension
        for word in words:   # for each word in list:
            word_surf = font.render(word, True, color)   # create word surface
            wordw, wordh = word_surf.get_size()   # get word size
            if x + wordw >= maxw:   # if word goes over max
                x = pos[0] + space   # reset x
                y += wordh   # start on new row
            surface.blit(word_surf, (x, y))   # show word
            x += wordw + space   # go to next word position
        y += wordh + line_space   # new row

# connect lines from element on graph to its corespondong name and draw outine box
def connect_lines(surface, coords_graph, coords_text, color=(0,0,0)):
    x_text, y_text, y_step_text = coords_text   # get text coordinates and step size
    for row_num, row in enumerate(coords_graph):   # for each row in graph coords matrix
        x1_scr, y1_scr, x2_scr, y2_scr, xc_scr, yc_scr = row[:6].astype(int)   # get graph coordinates
        # draw line
        pygame.draw.line(surface, color, (x_text, y_text + y_step_text/2 + row_num * y_step_text), (xc_scr, yc_scr))
        pygame.draw.rect(surface, color, (x1_scr, y1_scr, x2_scr - x1_scr +1, y2_scr - y1_scr + 1), 1)  # draw outline
