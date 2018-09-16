#!/usr/bin/python
import sys
import os
import numpy as np


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
    training_data.append(line.split())

training_data = np.asarray([[float(y) for y in x] for x in training_data])
training_classes = training_data[:, len(training_data[0]) - 1]
training_data = training_data[:, : -1]
print(len(training_data))

"""
test_file = open(test_file, 'r')
for line in test_file:
    print("test")
"""
