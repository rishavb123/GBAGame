from constants import *

import sys
import time
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
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

def run_game(population):

    agents = [agent for agent in population]
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

        if t % 3 == 0:
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
        if len(agents) == 0:
            return t

if __name__ == "__main__":
    population = [make_agent() for _ in range(population_size)]
    best = population[0]
    top_scores = []

    for itr in range(iterations):
        highest_fitness = run_game(population)
        print(f"Iteration: {itr};\tHighest Fitness: {highest_fitness}")
        top_scores.append(highest_fitness)
        population.sort(key=lambda x:-x.fitness)
        parents = population[:population_size // 20]
        best = parents[0]
        total_fitness = sum([parent.fitness for parent in parents])
        p = [parent.fitness / total_fitness for parent in parents]
        population = [Agent.crossover(np.random.choice(parents, p=p), np.random.choice(parents, p=p)).mutate() if i < population_size * 0.95 else make_agent() for i in range(population_size - 1)]
        population.append(best)
        plt.plot(top_scores)
        plt.savefig('./graph.png')
        best.save("./models/cur/")