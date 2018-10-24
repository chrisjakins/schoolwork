import numpy as np

class DecisionTree:
    def __init__(self):
        print('hello')


    def choose_attribute(self):
        print('choose_attribute')


    def information_gain(self):
        print('information_gain')



    def entropy(self, labels):
        k = len(labels)
        uniq, counts = np.unique(labels, return_counts = True)
        interim = np.multiply(np.divide(counts, k), np.log2(np.divide(counts, k)))
        entropy = np.negative(np.sum(interim))
        print(entropy)
        return entropy
