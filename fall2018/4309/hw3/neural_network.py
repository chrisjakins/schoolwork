#Chris Jakins 1000802309
#!/usr/bin/python
#
#   Chris Jakins
#
#   NOTE:
#       if the program seems like it is taking a while to run,
#       it is probably searching through all of the files on the local
#       computer to find the specified training and test files
import sys
import numpy as np
from file_utility import FileUtility
from network import NeuralNetwork


def validate(arg_name: str, arg: int, val: int) -> int:
    if arg < val:
        print("argument '%s' must be greater than %d" % (arg_name, val - 1))
        quit()
    return arg


if len(sys.argv) != 6:
    print("Usage: python3 neural_network.py <training_file> <test_file> <layers> <units_per_layer> <rounds>")
    quit()

training_filename = sys.argv[1]
test_filename = sys.argv[2]

layers = validate("layers", int(sys.argv[3]), 2)
units_per_layer = validate("units_per_layer", int(sys.argv[4]), 1)
rounds = validate("rounds", int(sys.argv[5]), 1)


# find the file in the system with the specified filename
# load in all data from file using np.loadtxt()
# split the data into inputs and outputs


file_util = FileUtility(training_filename, test_filename)
training_data, training_classes, test_data, test_classes = file_util.get_dataset()


#
#   start up the model
#

neural_network = NeuralNetwork(layers, units_per_layer, rounds)
neural_network.initialize_training(training_data, training_classes)
neural_network.train_general()
predictions = neural_network.test(test_data)
total_accuracy = 0
for i in range(0, len(test_data)):
    prediction_index = np.argmax(predictions[:,i], axis = 0)
    count = np.count_nonzero(predictions[:,i] == predictions[prediction_index][i])
    acc = 1 / count if np.unique(test_classes)[prediction_index] == test_classes[i] else 0
    total_accuracy += acc

    print('ID=%5d, predicted=%3d, true=%3d, accuracy=%4.2f\n' % (i + 1, np.unique(test_classes)[prediction_index], test_classes[i], acc))

print('classification accuracy=%6.4f\n' % (total_accuracy / len(test_data)))
print(np.unique(test_classes))
