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
import os
import numpy as np
from logreg_classifier import LogisticRegression


if len(sys.argv) != 4:
    print("Usage: python3 logistic_regression.py <training_file> <degree> <test_file>")
    quit()

training_filename = sys.argv[1]
degree = sys.argv[2]
test_filename = sys.argv[3]

# locating files

def find(name, path):
    for root, dirs, files in os.walk(path, topdown = False):
        if name in files:
            return os.path.join(root, name)

def file_search(name):
    new_file = find(name, './')
    if new_file == None:
        new_file = find(name, '/')

    if new_file == None:
        print('%s not found. Quitting...' % (name))
        quit()
    
    return new_file


training_file = file_search(training_filename)
test_file = file_search(test_filename)

# reading files and convert to numpy array
# split class data off of training data

def convertClasses(arr):
    for i in range(0, len(arr)):
        arr[i] = 1 if arr[i] == 1 else 0
    return arr


training_data = np.loadtxt(training_file)
training_classes = convertClasses(training_data[:, -1])
training_data = training_data[:, : -1]

test_data = np.loadtxt(test_file)
test_classes = convertClasses(test_data[:, - 1])
test_data = test_data[:, : -1]

# running the model

classifier = LogisticRegression(training_data, training_classes, degree)
weights = classifier.train()

for i in range(0, len(weights)):
    print('w%d=%.4f\n' % (i, weights[i]))

total_accuracy = 0
for i in range(0, len(test_data)):
    predicted, probability = classifier.test(test_data[i], test_classes[i])
    if predicted == test_classes[i]:
        accuracy = 1
    else:
        accuracy = 0
    
    total_accuracy += accuracy
    print('ID=%5d, predicted=%3d, probability = %.4f, true=%3d, accuracy=%4.2f\n' % (i + 1, predicted, probability, test_classes[i], accuracy))

print('classification accuracy=%6.4f\n' % (total_accuracy / len(test_data)))
