import numpy as np

class NaiveBayesClassifier:

    def __init__(self, data, labels):
        self.data = data
        self.num_dimensions = len(data[0])
        self.data_labels = labels
        self.classes = np.unique(self.data_labels)
        self.mean = np.zeros((len(self.classes), len(data[0])))
        self.s_deviation = np.zeros((len(self.classes), len(data[0])))
        self.class_frequencies = np.asarray([np.count_nonzero(self.data_labels == x) for x in self.classes]) / len(self.data_labels)


    def train(self):
        # get mean and standard deviation for each class
        counts = np.zeros((len(self.classes), 1))
        for i in range(0, len(self.data)):
            class_number_index = np.where(self.classes == self.data_labels[i])[0][0]
            counts[class_number_index] += 1
            self.mean[class_number_index] += self.data[i]
            self.s_deviation[class_number_index] += np.square(self.data[i])

        self.s_deviation = np.subtract(self.s_deviation, np.divide(np.square(self.mean), counts))
        self.s_deviation = np.divide(self.s_deviation, np.subtract(counts, 1))
        self.s_deviation = np.sqrt(self.s_deviation)
        self.s_deviation[self.s_deviation < 0.01] = 0.01
        self.mean /= counts # broadcasted
        return self.classes, self.mean, self.s_deviation


    def test(self, test_data):
        p_x = 0
        probabilities = []
        for i in range(0, len(self.classes)):
            gaussian_value = self.calcGaussians(test_data, self.mean[i], self.s_deviation[i])
            # p(x|Ck) * p(Ck)
            interim = np.multiply(np.prod(gaussian_value), self.class_frequencies[i])

            # add to p(x) (SUM RULE)
            p_x += interim

            probabilities.append(interim)

        probabilities = np.asarray(probabilities)
        probabilities = np.divide(probabilities, p_x)
        # find max probability
        probability = probabilities[np.argmax(probabilities)]
        # get ties
        results = []
        for i in range(0, len(probabilities)):
            if probabilities[i] == probability:
                results.append(self.classes[i])

        return results, probability

    def calcGaussians(self, values, means, std):
        numerator = np.negative(np.square(np.subtract(values, means)))
        denominator = np.multiply(np.square(std), 2)
        exponential = np.exp(np.divide(numerator, denominator))
        return np.divide(exponential, np.multiply(std, np.sqrt(2 * np.pi)))
