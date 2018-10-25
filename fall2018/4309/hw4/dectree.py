import numpy as np

class DecisionTree:
    def __init__(self):
        np.set_printoptions(threshold = np.inf, suppress = True)


    def choose_attribute_O(self, ex, labels, attr):
        print('choose_attribute')
        max_gain = -1
        best_attr = -1
        best_thresh = -1

        for i in range(0, len(ex[0])):
            l = np.amin(ex[:,i])
            m = np.amax(ex[:,i])
           
            # this may be temporary
            for k in range(1, 51):
                thresh = l + k * (m - l) / 51;
                gain = self.information_gain(ex, labels, i, thresh)
                
                if gain > max_gain:
                    max_gain = gain
                    best_thresh = thresh
                    best_attr = i

        return best_thresh, best_attr

    # attr is an index of the attribute 
    def information_gain(self, ex, labels, attr, thresh):
        parent_entropy = self.entropy(labels)

        left_labels = labels[np.where(ex[:,attr] < thresh)]
        right_labels = labels[np.where(ex[:,attr] >= thresh)]
        left_entropy = self.entropy(left_labels)
        right_entropy = self.entropy(right_labels)

        info_gain = parent_entropy - (
                    len(left_labels) * left_entropy / len(labels) +
                    len(right_labels) * right_entropy / len(labels)
                    )
        #print('info gain: ', info_gain)
        return info_gain


    def entropy(self, labels):
        k = len(labels)
        uniq, counts = np.unique(labels, return_counts = True)
        interim = np.multiply(np.divide(counts, k), np.log2(np.divide(counts, k)))
        entropy = np.negative(np.sum(interim))
        #print('Entropy: ', entropy)
        return entropy
