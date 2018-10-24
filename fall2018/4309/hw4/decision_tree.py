import sys
import numpy as np
from file_utility import FileUtility
from dectree import DecisionTree


if len(sys.argv) != 5:
    print("Usage: python3 decision_tree.py <training_file> <test_file> <option> <pruning_thr>")
    quit()

training_filename = sys.argv[1]
test_filename = sys.argv[2]
option = sys.argv[3]
pruning_thr = int(sys.argv[4])


# find the file in the system with the specified filename
# load in all data from file using np.loadtxt()
# split the data into inputs and outputs


file_util = FileUtility(training_filename, test_filename)
training_data, training_classes, test_data, test_classes = file_util.get_dataset()

#
# start up the tree
#

tree = DecisionTree()

data = np.asarray([1, 1, 1, 1, 1, 1, 1, 1])
tree.entropy(data)
