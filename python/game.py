from constants import *

import pygame

from python.objects import MovingBox

if draw:
    pygame.init()

    surface = pygame.display.set_mode((width, height))
    pygame.display.set_caption('GBA Game Simulation')

objects = [MovingBox(0, 0, 100, 100)]

# game loop
while True:
    for event in pygame.event.get():
        if event.type==QUIT:
            pygame.quit()
            sys.exit()
    pygame.display.update()