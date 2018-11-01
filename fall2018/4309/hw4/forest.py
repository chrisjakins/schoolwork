import numpy as np
from dectree import DecisionTree

class Forest:
    def __init__(self, num_trees, mode, data, labels):
        self.num_trees = num_trees
        self.mode = mode
        self.ex = data
        self.data_labels = labels
        self.labels = np.unique(self.data_labels)


    def train(self):
        trees = []
        results = []
        
        for i in range(0, self.num_trees):
            print('Training forest ', i)
            trees.append(DecisionTree(self.data_labels, self.mode))
            dist = trees[i].distribution(self.data_labels)
            results.append(trees[i].dtl(self.ex, self.data_labels, dist))

        self.model = results

    def test(self, data):
        average_dist = np.zeros(len(self.labels))
        myTree = DecisionTree('None', None)
        for tree in self.model:
            prediction = myTree.test(tree, data)
            average_dist = average_dist + prediction

        return average_dist / len(self.model)
