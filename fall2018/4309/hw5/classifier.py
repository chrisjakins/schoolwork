import numpy as np

class KMeansClassifier:

    def __init__(self, data, k, iterations):
        np.set_printoptions(threshold = np.inf, suppress = True)
        self.data = data
        self.k = k
        self.iter = iterations + 1


    def train(self):
        for i in range(0, self.iter):
            if i == 0:
                self.clusters = self.random_assignment()
            else:
                self.clusters = self.reassign()
            
            self.means = self.calc_means()
            
            error = self.calc_error()
            
            if i == 0:
                print('After initialization: error = %.4f' % (error))
            else:
                print('After iteration %d: error = %.4f' % (i, error))


    def reassign(self):
        clusters = {}
        for i in range(0, self.k):
            clusters[i] = []

        for i in range(0, len(self.data)):
            row = self.data[i]
            dists = np.zeros(self.k)
            for j in range(0, self.k):
                dist = np.linalg.norm(np.subtract(row, self.means[j]), ord = 2)
                dists[j] = dist
            
            clusters[np.argmin(dists)].append(i)

        return clusters


    def calc_means(self):
        means = []
        for i in range(0, self.k):
            means.append(np.mean(self.data[self.clusters[i]], axis = 0))

        return means


    def calc_error(self):
        error = 0
        for i in range(0, self.k):
            dist = np.linalg.norm(np.subtract(self.data[self.clusters[i]], self.means[i]), axis=1)
            error += np.sum(dist)

        return error


    def random_assignment(self):
        clusters = {}
        for i in range(0, self.k):
            clusters[i] = []

        for i in range(0, len(self.data)):
            index = np.random.randint(0, self.k)
            clusters[index].append(i)

        return clusters
