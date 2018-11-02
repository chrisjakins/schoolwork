import queue
import numpy as np
from dectree import DecisionTree

class Forest:
    def __init__(self, num_trees, mode, data, labels, prune):
        self.num_trees = num_trees
        self.mode = mode
        self.ex = data
        self.data_labels = labels
        self.labels = np.unique(self.data_labels)
        self.prune = prune


    def train(self):
        trees = []
        results = []
        
        for i in range(0, self.num_trees):
            trees.append(DecisionTree(self.data_labels, self.mode, self.prune))
            dist = trees[i].distribution(self.data_labels)
            results.append(trees[i].dtl(self.ex, self.data_labels, dist, 1))

        self.model = results
        self.print_forest()


    def print_forest(self):
        for i in range(0, len(self.model)):
            q = queue.Queue()
            q.put(self.model[i])
            j = 1
            while not q.empty():
                node = q.get()
                if node.left != None:
                    q.put(node.left)
                if node.right != None:
                    q.put(node.right)

                print('tree=%2d, node=%3d, feature=%2d, thr=%6.2f, gain=%f' %
                      (i + 1, j, node.attr, node.thresh, node.gain))
                j += 1


    # ignore my terrible code 
    def test(self, data):
        average_dist = np.zeros(len(self.labels))
        myTree = DecisionTree('None', None, None)
        for tree in self.model:
            prediction = myTree.test(tree, data)
            average_dist = average_dist + prediction

        return average_dist / len(self.model)
