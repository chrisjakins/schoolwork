import numpy as np
import time

class LogisticRegression:

    def __init__(self, arr, labels, degree):
        self.degree = int(degree)
        self.data = arr
        self.num_dimensions = len(self.data[0])
        self.num_examples = len(self.data)
        self.data_labels = labels
        self.weights = np.zeros((self.num_dimensions + 1, 1))
        self.phi_x = self.degree1() if self.degree == 1 else self.degree2()
            

    def degree1(self):
        self.phi_x = []
        for i in range(0, self.num_examples):
            temp = [1]
            for j in range(0, self.num_dimensions):
                temp.append(self.data[i][j])

            self.phi_x.append(temp)

        return np.asarray(self.phi_x)


    def degree2(self):
        self.phi_x = []
        for i in range(0, self.num_examples):
            temp = [1]
            for j in range(0, self.num_dimensions):
                temp.append(np.square(self.data[i][j]))

            self.phi_x.append(temp)

        return np.asarray(self.phi_x)


    def train(self):
        np.set_printoptions(threshold=np.inf)
        diff = 1
        old_ew = 1
        itera = 0

        while diff > 0.001 and old_ew > 0.001:
            diff = 0
            old_ew = 0
            #print(itera)
            itera += 1
            a = np.dot(self.weights.T, self.phi_x.T)
            z = self.sigmoid(a)
            p_y = self.prob(z)
            r = self.comp_r(z)
            y = self.prob_convert(p_y)

            e_w = self.comp_error(y)
            h = np.dot(self.phi_x.T, np.dot(r, self.phi_x))

            offset = np.dot(np.linalg.pinv(h), e_w)
            new_w = np.subtract(self.weights, offset)

            diff += np.sum(np.absolute(np.subtract(new_w, self.weights)))
            if diff > 0.001:
                self.weights = new_w

            error_diff = np.sum(np.absolute(np.subtract(e_w, old_ew)))
            if error_diff > 0.001:
                old_ew = error_diff

        return self.weights


    def test(self, test_data, test_classes):
        temp = np.ones((test_data.shape[0] + 1, 1))
        for i in range(0, len(test_data)):
            temp[i + 1] = test_data[i]

        a = np.dot(self.weights.T, temp)
        y = self.sigmoid(a)

        return self.prob_convert(y), y


    def sigmoid(self, val):
        temp = np.exp(np.negative(val))
        temp = np.add(1, temp)
        return np.asarray(np.divide(1, temp))


    def prob(self, arr):
        left = np.power(np.ones(arr.shape) - arr, np.ones(self.data_labels.shape) - self.data_labels)
        right = np.power(arr, self.data_labels)
        return np.multiply(left, right)


    def prob_convert(self, arr):
        for i in range(0, len(arr[0])):
            if arr[0][i] <= 0.5:
                arr[0][i] = 0
            else:
                arr[0][i] = 1

        return arr


    def comp_error(self, y):
        right = np.subtract(y, self.data_labels)
        error = np.dot(self.phi_x.T, right.T)
        return error

   
    def comp_r(self, y):
        r = np.zeros((self.num_examples, self.num_examples))
        for i in range(0, len(y[0])):
            r[i][i] = y[0][i] * (1 - y[0][i])

        return r



