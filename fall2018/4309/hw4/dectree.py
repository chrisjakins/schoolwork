import numpy as np

class DecisionTree:

    def __init__(self, labels, mode):
        np.set_printoptions(threshold = np.inf, suppress = True)
        self.class_labels = np.unique(labels)
        self.num_labels = len(self.class_labels)
        self.mode = mode


    # Nodes used for the tree returned
    class TreeNode:
        # attr is the index of a row in data
        # thresh is the value to split on
        #   less than goes left
        #   greater than or equal to goes right
        def __init__(self, attr, thresh, dist = None):
            self.attr = attr
            self.thresh = thresh
            self.distr = dist
            self.left = None
            self.right = None

    #
    #   end TreeNode class
    #

    # default is a distribution over the labels
    # returns a TreeNode
    def dtl(self, ex, labels, default) -> TreeNode:
        if len(ex) == 0:
            newNode = self.TreeNode(-1, -1, default)
            return newNode

        if len(np.unique(labels)) == 1:
            dist = self.distribution(labels)
            newNode = self.TreeNode(-1, -1, dist)
            return newNode

        if self.mode == 'optimized':
            thresh, attr = self.choose_optimized(ex, labels)
        else:
            thresh, attr = self.choose_random(ex, labels)

        root = self.TreeNode(attr, thresh)

        left_cond = np.where(ex[:,attr] < thresh)
        right_cond = np.where(ex[:,attr] >= thresh)

        new_default = self.distribution(labels)

        root.left = self.dtl(ex[left_cond], labels[left_cond], new_default)
        root.right = self.dtl(ex[right_cond], labels[right_cond], new_default)
        
        return root


    def choose_random(self, ex, labels):
        max_gain = -1
        best_thresh = -1

        random_attr = np.random.randint(len(ex[0]))
        l = np.amin(ex[:,random_attr])
        m = np.amax(ex[:,random_attr])
        for i in range(1, 51):
            thresh = l + i * (m - l) / 51
            gain = self.information_gain(ex, labels, random_attr, thresh)

            if gain > max_gain:
                max_gain = gain
                best_thresh = thresh

        return best_thresh, random_attr


    def choose_optimized(self, ex, labels):
        max_gain = -1
        best_attr = -1
        best_thresh = -1

        for i in range(0, len(ex[0])):
            l = np.amin(ex[:,i])
            m = np.amax(ex[:,i])
           
            for k in range(1, 51):
                thresh = l + k * (m - l) / 51
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
        return info_gain


    def entropy(self, labels):
        k = len(labels)
        uniq, counts = np.unique(labels, return_counts = True)
        interim = np.multiply(np.divide(counts, k), np.log2(np.divide(counts, k)))
        entropy = np.negative(np.sum(interim))
        return entropy


    def distribution(self, labels):
        k = len(labels)
        uniq, counts = np.unique(labels, return_counts = True)
        distr = np.zeros(self.num_labels)
        for i in range(0, len(uniq)):
            index = np.argwhere(self.class_labels == uniq[i])
            distr[index] = counts[i]
            
        return np.divide(distr, k)


    def test(self, tree, test_data):
        while tree.attr != -1:
            if test_data[tree.attr] < tree.thresh:
                tree = tree.left
            else:
               tree = tree.right
        return tree.distr
