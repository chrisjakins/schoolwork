import numpy as np

class KMeansClassifier:

    def __init__(self, data, k, iterations):
        np.set_printoptions(threshold = np.inf, suppress = True)
        self.data = data
        self.k = k
        self.iter = iterations

    def train(self):
        self.clusters = self.random_assignment()
        self.means = self.calc_means()
        print(self.means)


    def calc_means(self):
        means = []
        for i in range(0, self.k):
            means.append(np.mean(self.data[self.clusters[i]], axis = 0))

        return means


    def random_assignment(self):
        clusters = {}
        for i in range(0, self.k):
            clusters[i] = []

        for i in range(0, len(self.data)):
            index = np.random.randint(0, self.k)
            clusters[index].append(i)

        return clusters
