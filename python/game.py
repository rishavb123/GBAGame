from constants import *

import sys
import time
import numpy as np
import pygame

from objects import Collision, MovingBox
from agent import Agent

if draw:
    pygame.init()

    surface = pygame.display.set_mode((width * multiplier, height * multiplier))
    pygame.display.set_caption('GBA Game Simulation')

def make_box():
    return MovingBox(np.random.randint(3, width - 3), np.random.randint(3, height - 3), 10, 10, np.random.randint(-2, 3), np.random.randint(-2, 3))

def make_agent():
    return Agent(np.random.randint(3, width - 3), np.random.randint(3, height - 3), 5, 5)

def d(agent, box):
    dx = agent.x - box.x
    dy = agent.y - box.y
    dx = min(dx, width - dx)
    dy = min(dy, width - dy)
    return dx ** 2 + dy  ** 2

agents = [make_agent() for _ in range(population_size)]
boxes = [make_box() for _ in range(num_boxes)]
t = 0

# game loop
while True:

    for obj in boxes:
        obj.update()

    t += 1
    if t % 500 == 0:
        boxes.append(make_box())

    for agent in agents:
        agent.update()

    if t % 10 == 0:
        agent_ind = 0
        while agent_ind < len(agents):
            agent = agents[agent_ind]

            min_ind = -1
            min_ind_2 = -1
            min_distance = width * width + height * height
            min_distance_2 = min_distance
            for i, box in enumerate(boxes):
                dist = d(agent, box)
                if dist < min_distance:
                    min_distance_2 = min_distance
                    min_ind_2 = min_ind
                    min_distance = dist
                    min_ind = i
                elif dist < min_distance_2:
                    min_distance_2 = dist
                    min_ind_2 = i


            agent.think([
                boxes[min_ind].x - agent.x,
                boxes[min_ind].y - agent.y,
                boxes[min_ind_2].x - agent.x,
                boxes[min_ind_2].y - agent.y
            ])

            for box in boxes:
                if Collision.check(agent, box):
                    agent.collide(box)
                    if agent in agents:
                        agents.remove(agent)
                    i -= 1

            agent_ind += 1
    
    if draw:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

        surface.fill(background_color)

        for obj in boxes:
            obj.draw(surface)

        for obj in agents:
            obj.draw(surface)

        time.sleep(1/60)

        pygame.display.update()
    
    print(f"Agents: {len(agents)} \t Time: {t}   ", end="\r")