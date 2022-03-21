import pygame

class Logger():
    def __init__(self):
        self.mem_text = ""   # to store previous text
        self.text1, self.text2, self.text3 = "", "", ""   # text buffer
        self.text_color1, self.text_color2, self.text_color3 = (0,0,0), (0,0,0), (0,0,0)   # text color buffer
        self.max_width = 100
        
    # log displayed on surface during simulation
    def gui_logger(self, surface, font):
        surface.blit(font.render(str(self.text1), True, self.text_color1), (363, 669))   # text output line 1
        surface.blit(font.render(str(self.text2), True, self.text_color2), (363, 684))   # text output line 2
        surface.blit(font.render(str(self.text3), True, self.text_color3), (363, 699))   # text output line 3
        
    # add new text to log
    def log_add(self, text, text_color=(0,0,0)):
        if text != self.mem_text:   # if new text is sent:
            self.text3, self.text2, self.text1 = self.text2, self.text1, text   # add it to begenning, and shift others
            self.text_color3, self.text_color2, self.text_color1 = self.text_color2, self.text_color1, text_color   # same for colors
            if len(text) > self.max_width:   # if text is larger than window: split it and shift again
                self.text3, self.text2, self.text1 = self.text2, text[self.max_width : len(text)], text[0 : self.max_width]
                self.text_color3, self.text_color2, self.text_color1 = self.text_color2, text_color, text_color   # same for colors
        self.mem_text = text   # update mem
    
    # load max text width
    def gui_max_width(self, max_width):
        self.max_width = max_width

