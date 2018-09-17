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
        """
        print("Mean")
        print(self.mean)
        print("S_Deviation")
        print(self.s_deviation)
        print("Test_data")
        print(test_data)
        print(self.class_frequencies)
        """
        p_x = 0
        interim = 0
        probabilities = []
        for i in range(0, len(self.classes)):
            # calculate gaussians for each dimension for the i-th class
            numerator = np.negative(np.square(np.subtract(test_data, self.mean[i])))
            denominator = np.multiply(np.square(self.s_deviation[i]), 2)
            #print("Numerator")
            #print(numerator)
            #print("Denominator")
            #print(numerator)
            exponential = np.exp(np.divide(numerator, denominator))
            gaussian_value = np.divide(exponential, np.multiply(self.s_deviation[i], np.sqrt(2 * np.pi)))

            #print("Gaussian")
            #print(gaussian_value)
            # correct up to here

            # p(x|Ck) * p(Ck)
            interim = np.multiply(np.prod(gaussian_value), self.class_frequencies[i])
            """
            np.set_printoptions(suppress=True)
            print(gaussian_value)
            print("%.5f" % np.prod(gaussian_value))
            print("interim")
            print(interim)
            """

            # add to p(x) (SUM RULE)
            p_x += interim

            probabilities.append(interim)

        probabilities = np.asarray(probabilities)
        probabilities = np.divide(probabilities, p_x)
        probability = probabilities[np.argmax(probabilities)]
        results = []
        for i in range(0, len(probabilities)):
            if probabilities[i] == probability:
                results.append(self.classes[i])

        #result_class = self.classes[np.argmax(probabilities)]
        return results, probability
