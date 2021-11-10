import os
import numpy as np

from constants import inp_dim, out_dim, layers, body_1_color
from objects import MovingBox, Collision
from nn import IntNN

class Agent(MovingBox, Collision):

    def __init__(self, x, y, w, h):
        super().__init__(x, y, w, h, color=body_1_color)
        self.brain = IntNN(inp_dim, out_dim, layers=layers)
        self.fitness = 0

    def think(self, inp):
        o_x, o_y = self.brain(inp)
        if np.abs(o_x) >= np.abs(o_y):
            self.dx = np.sign(o_x)
            self.dy = 0
        else:
            self.dx = 0
            self.dy = np.sign(o_y)

    def update(self):
        self.fitness += 1
        return super().update()

    def collide(self, rect):
        pass

    def mutate(self):
        self.brain.mutate()
        return self
    
    def save(self, dir):
        for i, (w, b) in enumerate(zip(self.brain.weights, self.brain.biases)):
            np.save(dir + f"weights_{i}.npy", np.array(w, np.int32))
            np.save(dir + f"biases_{i}.npy", np.array(b, np.int32))

    def load(self, dir):
        self.brain.weights = list(np.load(dir + "weights.npy"))
        self.brain.biases = list(np.load(dir + "biases.npy"))
        for i, (w, b) in enumerate(zip(self.brain.weights, self.brain.biases)):
            np.load(dir + f"weights_{i}.npy", np.array(w, np.int32))
            np.save(dir + f"biases_{i}.npy", np.array(b, np.int32))

    @staticmethod
    def crossover(a1, a2):
        a = Agent(a1.x, a1.y, a1.w, a1.h)
        a.brain = IntNN.crossover(a1.brain, a2.brain)
        return a