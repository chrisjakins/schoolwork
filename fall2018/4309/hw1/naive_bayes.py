#!/usr/bin/python

import sys
import os
import numpy

if len(sys.argv) != 3:
    print("Usage: python3 naive_bayes.py <training_file> <test_file>")
    quit()

training_filename = sys.argv[1]
test_filename = sys.argv[2]

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
