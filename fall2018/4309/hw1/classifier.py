import numpy as np

class NaiveBayesClassifier:

    def __init__(self, data, labels):
        self.data = data
        self.num_dimensions = len(data[0])
        self.data_labels = labels
        self.classes = np.unique(self.data_labels)
        self.mean = np.zeros((len(self.classes), len(data[0])))
        self.s_deviation = np.zeros((len(self.classes), len(data[0])))


    def train(self):
        # get mean and standard deviation for each dimension for each class
        counts = np.zeros((len(self.classes), 1))
        for i in range(0, len(self.data)):
            class_number_index = np.where(self.classes == self.data_labels[i])[0][0]
            self.mean[class_number_index] += self.data[i]
            self.s_deviation[class_number_index] += np.square(self.data[i])
            counts[class_number_index] += 1

        self.s_deviation -= (np.divide(np.square(self.mean), counts))
        self.s_deviation /= (counts - 1)
        self.s_deviation = np.sqrt(self.s_deviation)
        self.s_deviation[self.s_deviation < 0.001] = 0.001
        self.mean /= counts # broadcasted

