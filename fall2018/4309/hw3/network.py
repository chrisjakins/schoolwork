import numpy as np

class NeuralNetwork:

    def __init__(self, l, upl, r):
        np.set_printoptions(threshold = np.inf, suppress = True)

        # initialize hyperparameters
        self.num_layers = l
        self.upl = upl
        self.num_rounds = r
        self.learning_rate = 1


    def initialize_training(self, data, labels):
        self.num_examples = len(data)

        # initialize training data matrix
        self.num_dimensions = len(data[0])

        # normalize the attributes based on the largest attribute value
        self.max_normalize = np.amax(data)
        data = np.divide(data, self.max_normalize)

        # add the bias input x_0 = 1 to each training example
        self.train_data = np.ones((len(data), 1))
        self.train_data = np.hstack((self.train_data, data)).T

        # initialize training classes vector
        # TODO generalize based off index in labels
        self.num_classes = len(np.unique(labels))
        self.train_labels = np.zeros((self.num_classes, self.num_examples))
        for i in range(self.num_examples):
            index = np.where(np.unique(labels) == labels[i])[0][0]
            #self.train_labels[int(labels[i]) - 1][i] = 1
            self.train_labels[index][i] = 1
       

    def train_general(self):
        self.model = {}
        if self.num_layers == 2:
            self.model['W1'] = np.subtract(np.multiply(np.random.rand(self.num_dimensions + 1, self.upl), .1), .05)
        else:
            self.model['W1'] = np.subtract(np.multiply(np.random.rand(self.num_dimensions + 1, self.upl), .1), .05)
            for i in range(2, self.num_layers - 1):
                self.model['W' + str(i)] = np.subtract(np.multiply(np.random.rand(self.upl + 1, self.upl), .1), .05)
            self.model['W' + str(self.num_layers - 1)] = np.subtract(np.multiply(np.random.rand(self.upl + 1, self.num_classes), .1), .05)

        self.outs = {}
        for i in range(0, self.num_rounds):
            for j in range(0, self.num_examples): #self.num_examples
                # forward
                z = self.train_data[:,j].reshape(self.num_dimensions + 1, 1)
                self.outs['Z0'] = z
                for k in range(0, self.num_layers - 2):
                    a = np.dot(self.model['W' + str(k + 1)].T, self.outs['Z' + str(k)])
                    z = self.sigmoid(a).reshape(self.upl, 1)
                    z = np.vstack((np.ones((1,1)), z))
                    self.outs['Z' + str(k + 1)] = z

                # do final layer
                a = np.dot(self.model['W' + str(self.num_layers - 1)].T, self.outs['Z' + str(self.num_layers - 2)])
                self.outs['Z' + str(self.num_layers - 1)] = self.sigmoid(a)

                # backward
                # compute deltas
                labels = self.train_labels[:,j].reshape(self.num_classes, 1)
                delta_out = np.multiply(np.subtract(self.outs['Z' + str(self.num_layers - 1)], labels), self.outs['Z' + str(self.num_layers - 1)])
                delta_out = np.multiply(delta_out, 1 - self.outs['Z' + str(self.num_layers - 1)])
                delta = {}
                delta = {'D' + str(self.num_layers - 1) : delta_out}
                
                for x in range(self.num_layers - 2, 0, -1):
                    right = np.multiply(self.outs['Z' + str(x)], 1 - self.outs['Z' + str(x)])
                    weights = self.model['W' + str(x + 1)]
                    delt = delta['D' + str(x + 1)]
                    delt = delt if x == self.num_layers - 2 else delt[1:]
                    delta['D' + str(x)] = np.multiply(np.dot(delt.T, weights.T).T, right)

                # update weights

                for j in range(1, self.num_layers):
                    if j > 0 and j < self.num_layers - 1:
                        d = delta['D' + str(j)][1:]
                    else:
                        d = delta['D' + str(j)]
                    gradient = self.learning_rate * d * self.outs['Z' + str(j - 1)].T
                    self.model['W' + str(j)] = self.model['W' + str(j)] - gradient.T

            self.learning_rate *= .98


    def test(self, data):
        data = np.divide(data, self.max_normalize)
        z = data.T

        for i in range(1, self.num_layers):
            temp = np.ones((len(z[0]), 1)).T
            z = np.vstack((temp, z))
            a = np.dot(self.model['W' + str(i)].T, z) 
            z = self.sigmoid(a)

        return z


    def sigmoid(self, val):
        temp = np.exp(np.negative(val))
        temp = np.add(1, temp)
        return np.divide(1, temp)
