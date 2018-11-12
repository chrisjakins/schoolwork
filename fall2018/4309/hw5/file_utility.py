import os
import numpy as np

class FileUtility:

    def __init__(self, training, test = None):
        self.training_data, self.training_classes = self.getData(training)
        self.test_data, self.test_classes = self.getData(test)


    def get_dataset(self):
        return self.training_data, self.training_classes, self.test_data, self.test_classes

    def find(self, name, path):
        for root, dirs, files in os.walk(path, topdown = False):
            if name in files:
                return os.path.join(root, name)


    def file_search(self, name):
        new_file = self.find(name, './')

        if new_file == None:
            new_file = self.find(name, '../')
        if new_file == None:
            new_file = self.find(name, '/')
        if new_file == None:
            print('%s not found. Quitting...' % (name))
            quit()
        
        return new_file


    def getData(self, filename):
        if filename == None:
            return None, None

        infile = self.file_search(filename)
        data = np.loadtxt(infile)
        classes = data[:, -1]
        data = data[:, :-1]
        return data, classes
