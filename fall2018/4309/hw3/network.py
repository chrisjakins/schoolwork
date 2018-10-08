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
        self.num_classes = len(np.unique(labels))
        self.train_labels = np.zeros((self.num_classes, self.num_examples))
        for i in range(self.num_examples):
            self.train_labels[int(labels[i]) - 1][i] = 1
        
        print(self.train_labels[:,10])


    def train(self):
        self.model = {}
        # INPUT LAYER
        W1 = np.subtract(np.multiply(np.random.rand(self.num_dimensions + 1, self.upl), .1), .05)
        W2 = np.subtract(np.multiply(np.random.rand(self.upl + 1, self.num_classes), .1), .05)
        self.model['W1'] = W1
        self.model['W2'] = W2

        for i in range(0, self.num_rounds):

            a = np.dot(W1.T, self.train_data[:,10])
            Z1 = self.sigmoid(a)
            self.outs = {'Z1' : Z1}
            print('After input layer -> hidden layer feedforward')
            print(self.train_data[:,10])
            print(W1)
            print(a)
            print(Z1)

            # OUTPUT LAYER
            # check these two lines below when generalizing
            Z1 = np.reshape(Z1, (1, len(Z1)))
            layer_in = np.ones((1,1))
            layer_in = np.hstack((layer_in, Z1)).T

            a = np.dot(W2.T, layer_in)
            Z2 = self.sigmoid(a)
            self.outs['Z2'] = Z2
            print('After hidden layer -> output feedforward')
            print(layer_in)
            print(W2)
            print(a)
            print(Z2)

            # BACKWARDS
            # OUTPUT LAYER
            labels = self.train_labels[:,10].reshape((10,1))
            delta_out = np.multiply(np.subtract(self.outs['Z2'], labels), self.outs['Z2']) 
            delta_out = np.multiply(delta_out, (1 - self.outs['Z2']))
            print('Delta of output layer')
            print(delta_out)

            # HIDDEN LAYER
            # need to exclude bias units
            right = np.multiply(self.outs['Z1'], 1 - self.outs['Z1'])
            delta_hidden = np.multiply(np.sum(np.multiply(delta_out, self.model['W2'][1])), right)
            print('Delta of hidden layer')
            print(right)
            print(delta_hidden)

            # UPDATE
            # INNER LAYER
            print('Update inner -> hidden')
            print(self.model['W1'])
            update_weightLayer1 = np.multiply(self.learning_rate * delta_hidden, self.train_data[:,10])
            self.model['W1'] = np.subtract(self.model['W1'].T, update_weightLayer1).T
            print(update_weightLayer1)
            print(self.model['W1'])

            # HIDDEN LAYER
            print('Update hidden -> output')
            print(self.model['W2'])
            update_weightLayer2 = np.multiply(self.learning_rate * delta_out, self.outs['Z1'])
            self.model['W2'][1] = np.subtract(self.model['W2'][1], update_weightLayer2.T).T.reshape(10,)
            print(update_weightLayer2)
            print(self.model['W2'])

            self.learning_rate *= .98

        print(self.outs['Z2'])


    def forward(self):
        print('hello')


    def test(self, data, labels):
        # don't forget to normalize attributes
        data = np.divide(data, self.max_normalize)


    def sigmoid(self, val):
        temp = np.exp(np.negative(val))
        temp = np.add(1, temp)
        return np.divide(1, temp)
