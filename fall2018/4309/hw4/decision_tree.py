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
tree = DecisionTree(training_classes, option)
myTree = tree.dtl(training_data, training_classes, tree.distribution(training_classes))

labels = np.unique(training_classes)
total_accuracy = 0
for i in range(0, len(test_data)):
    predictions = tree.test(myTree, test_data[i])
    prediction_index = np.argmax(predictions)

    count = np.count_nonzero(predictions == predictions[prediction_index])
    acc = 1 / count if np.unique(test_classes)[prediction_index] == test_classes[i] else 0

    total_accuracy += acc

    print('ID=%5d, predicted=%3d, true=%3d, accuracy=%4.2f\n' % 
            (i + 1, labels[prediction_index], test_classes[i], acc))

print('classification accuracy=%6.4f\n' % (total_accuracy / len(test_data)))
