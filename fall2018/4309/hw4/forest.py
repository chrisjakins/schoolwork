import numpy as np
from dectree import DecisionTree

class Forest:
    def __init__(self, num_trees):
        self.num_trees = num_trees
