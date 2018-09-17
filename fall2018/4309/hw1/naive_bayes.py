#!/usr/bin/python
import sys
import os
import numpy as np
from classifier import NaiveBayesClassifier


if len(sys.argv) != 3:
    print("Usage: python3 naive_bayes.py <training_file> <test_file>")
    quit()

training_filename = sys.argv[1]
test_filename = sys.argv[2]

# locating files

def find(name, path):
    for root, dirs, files in os.walk(path, topdown = False):
        if name in files:
            return os.path.join(root, name)

training_file = find(training_filename, './')
if training_file == None:
    training_file = find(training_filename, '/')

test_file = find(test_filename, './')
if test_file == None:
    test_file = find(test_filename, '/')

# reading files and convert to numpy array
# split class data off of training data

training_file = open(training_file, 'r')
training_data = []
for line in training_file:
    training_data.append([float(x) for x in line.split()])

training_data = np.asarray(training_data)
training_classes = training_data[:, -1]
training_data = training_data[:, : -1]

test_file = open(test_file, 'r')
test_data = []
for line in test_file:
    test_data.append([float(x) for x in line.split()])

test_data = np.asarray(test_data)
test_classes = test_data[:, - 1]
test_data = test_data[:, : -1]

# naive bayes classifier

# training

def print_training(labels, mean, s_deviation):
    for i in range(0, len(labels)):
        for j in range(0, len(mean[i])):
            print("Class: %d, attribute: %d, mean = %.2f, std = %.2f" % (labels[i], j + 1, mean[i][j], s_deviation[i][j]))


cfier = NaiveBayesClassifier(training_data, training_classes)
class_labels, mean, s_deviation = cfier.train()

print_training(class_labels, mean, s_deviation)

# test

def print_test(row, prediction, probability, actual, accuracy):
    print("ID = %5d, predicted = %3d, probability = %.4f, true = %3d, accuracy = %4.2f\n" % (row, prediction, probability, actual, accuracy))

count = 0
"""
predicitions, probability = cfier.test(test_data[1])
print(predictions)
print(test_classes[1])
"""
total = 0
for i in range(0, len(test_data)):
    predictions, probability = cfier.test(test_data[i])
    if test_classes[i] in predictions:
        accuracy = 1 / len(predictions)
        print(accuracy)
        print_test(i + 1, test_classes[i], probability, test_classes[i], accuracy)
    else:
        print_test(i + 1, predictions[0], probability, test_classes[i], 0)
    
    total += accuracy

    if predictions == test_classes[i]:
        count += 1

print("Classification accuracy = %6.4f" % (total / len(test_data)))
#print(count)
