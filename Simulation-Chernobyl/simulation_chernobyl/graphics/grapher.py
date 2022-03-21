import pygame
import numpy as np
import csv
import datetime
import os
from ..graphics import graphics as gr

class Grapher():
    def __init__(self):
        self.mem = 1
        self.x1, self.y1, self.x2, self.y2 = 0, 0, 300, 150
        self.length = self.x2 - self.x1
        self.height = self.y1 - self.y2
        self.val = np.zeros([int(self.length),4])
        self.val0 = np.zeros([int((self.length)),2])
        self.counter_step = 1
        
    # graph dimensions
    def graph_dim(self, x1, y1, x2, y2, counter_step):
        self.x1, self.y1, self.x2, self.y2 = x1, y1, x2, y2   # absolute graph dimensions
        self.length = x2 - x1   # graph length
        self.height = y2 - y1   # graph height
        self.counter_step = counter_step   # counter step
        self.vals_num = 3   # number of values to be graphed
        vals = np.zeros(self.vals_num, dtype=object)
        self.val0 = np.zeros([int(self.length/(self.counter_step*10)),2])   # graph empty matrix
        
    # set line colors and number of values that will be imported
    def set_line_color(self, vals_num, line_colors):
        self.line_colors = line_colors   # line colors
        self.vals_num = vals_num   # line number
        self.val = np.zeros([int(self.length/(self.counter_step*10)),vals_num + 1])   # graph buffer matrix
    
    # add values to graph
    def add_val(self, counter, in_arr):
        self.val = np.roll(self.val, 1, axis=0)   # move all values in buffer
        self.val[:1] = np.zeros((self.val[:1].shape))   # one place down
        self.val[0,1:] = in_arr   # add new imputs
        self.val[0,0] = counter * 10   # add new x to buffer
        if counter >= ((self.length/2)/5):   # if buffer overflows:
            self.val[:,0] -= self.counter_step * 10   # substract 1 step from x coords
            if counter > ((self.length/2)/5): # in all next iterrations:
                self.val[0,0] -= (counter * 10 - (self.length/2)*2)   # make first x constant
                
    # draw graph
    def draw_graph(self, surface, antial=False):
        self.val0[:,0] = self.val[:,0] + self.x1   # add x values to seed from buffer
        for column_num, column in enumerate(self.val.T):   # for every column in val array (transpose to read rows)
            if column_num != 0:   # skip first column - it is x value
                val_out = self.val0   # load x values in output line array
                val_out[:,1] = self.height - column + self.y1   # from buffer add y, and graph y coordinates
                color = self.line_colors[column_num - 1]   # set line color
                if antial is True: pygame.draw.aalines(surface, color, False, val_out, 2)   # draw graphed lines
                else: pygame.draw.lines(surface, color, False, val_out, 2)   # draw graphed lines
    
    # initialise recording
    def record_start(self, names_rec, colors_rec):
        now_time = datetime.datetime.now()   # get current date and time
        now_time_short = (now_time.strftime("%Y-%m-%d %H-%M-%S"))   # remove milliseconds
        if os.path.isdir("records") is False: os.mkdir("records")   # if there is no records dir: create it
        self.csv_file = open("records/Recording from " + now_time_short + ".csv", mode='w', newline="")   # create new file
        self.writer = csv.writer(self.csv_file, delimiter=',')   # prepare writer
        self.writer.writerow(np.insert(names_rec, 0, "time"))   # add value names to csv header
        self.writer.writerow(colors_rec)   # add value colors to csv header
    
    # add value to csv file
    def rec_val(self, counter, vals_graph):
        self.writer.writerow(np.concatenate([[counter], vals_graph]))   # append data to csv file
    
    # save csv file to storage
    def record_stop(self):
        self.csv_file.close()   # close and save csv file
    
