import sys
import numpy as np
from file_utility import FileUtility
from classifier import KMeansClassifier


if len(sys.argv) != 4:
    print("Usage: python3 k_means_cluster.py <data_file> <k> <iterations>")
    quit()

filename = sys.argv[1]
k = int(sys.argv[2])
iterations = int(sys.argv[3])


# find the file in the system with the specified filename
# load in all data from file using np.loadtxt()
# split the data into inputs and outputs


file_util = FileUtility(filename)
training_data = file_util.get_dataset()[0]


#
# start up the classifier
#

kmeans = KMeansClassifier(training_data, k, iterations)
kmeans.train()
