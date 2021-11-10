from constants import p_mutation, w_range, b_range

import numpy as np
import copy

class IntNN:

    def __init__(self, inp_dim, out_dim, layers=[]):
        self.layers = [inp_dim] + layers + [out_dim]
        self.weights = [np.random.randint(-w_range, w_range + 1, (self.layers[i], self.layers[i - 1])) for i in range(1, len(self.layers))]
        self.biases = [np.random.randint(-b_range, b_range + 1, (layer, 1), np.int32) for layer in range(1, len(self.layers))]

    def forward(self, inp):
        x = np.array(inp, dtype=np.int32).reshape((self.layers[0], 1))
        for w, b in zip(self.weights[:-1], self.biases[:-1]):
            x = w @ x + b
            x[x < 0] = 0
        x = self.weights[-1] @ x + self.biases[-1]
        return x.transpose().tolist()[0]

    def __call__(self, inp):
        return self.forward(inp)

    def mutate(self):
        for i in range(len(self.weights)):
            self.weights[i] += np.random.binomial(1, p_mutation, self.weights[i].shape) * np.random.randint(-w_range, w_range + 1, self.weights[i].shape)
            self.biases[i] += np.random.binomial(1, p_mutation, self.biases[i].shape) * np.random.randint(-b_range, b_range + 1, self.biases[i].shape)
        return self

    def copy(self):
        nn = IntNN(self.layers[0], self.layers[-1], layers=self.layers[1:-1])
        nn.weights = copy.deepcopy(self.weights)
        nn.biases = copy.deepcopy(self.biases)
        return nn

    def generate_c_code(self):
        pass

    @staticmethod
    def crossover(nn1, nn2):
        nn = nn1.copy()
        for i in range(len(nn.weights)):
            c1 = np.random.binomial(1, 0.5, nn.weights[i].shape)
            c2 = 1 - c1
            nn.weights[i] = c1 * nn1.weights[i] + c2 * nn2.weights[i]
            c1 = np.random.binomial(1, 0.5, nn.biases[i].shape)
            c2 = 1 - c1
            nn.biases[i] = c1 * nn1.biases[i] + c2 * nn2.biases[i]

        return nn