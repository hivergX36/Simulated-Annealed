from SimulatedAnealed import SimulatedAnealed
import random
import os

T = 400
LowTemperature = 10
alpha = 0.5
pallier = 2
fileDirectory = os. getcwd()
fileName = "C:/Users/viche/Documents/Programmation/Metaheuristics/GreedyKnapsack/GreedyKnapsack_Python/knapsack.txt"
print(fileName)
simulatedanealed = SimulatedAnealed(T,LowTemperature,alpha,pallier)
simulatedanealed.parseKnapsack(fileName)
simulatedanealed.resolve()
simulatedanealed.DisplaySolution()