import numpy as np
import matplotlib.pyplot as plt


def sum_of_squares(c, point):
    total = 0

    for i in range(0, c.shape[0]):
        total += np.sum(np.square(c[i,:] - point))

    return total


def gradient(c, point):
    sums = np.sum(c, axis = 0)
    grad = np.array([ -2 * sums[0] + 8 * point[0][0] ,
                      -2 * sums[1] + 8 * point[1][0] ])

    return grad



def positionHospital(c, h, alpha, tol):
    h = h.reshape(h.shape[0], 1)
    old_h = np.zeros(h.shape)
    i = 0

    while np.linalg.norm(h - old_h) > tol:
        print('iteration ', i + 1)
        ssd = sum_of_squares(c, h)
        print('Sum of Squared Differences = ', ssd)
        grad = gradient(c, h)
        print('Gradient = ', grad)

        old_h = h
        h = h - grad.reshape(grad.shape[0], 1) * alpha
        print('New hospital coordinates = \n', h)
        print('\n')

        i += 1

    return h


def plotCoor(cities, hospital):
    plt.plot(cities, 'o')
    plt.plot(hospital, 'x')
    plt.show()




###################  main  ###################
if __name__ == "__main__":
    #  coordinates of cities
    cities = np.array([[ 0,   0],
                       [30, 110],
                       [60, 100],
                       [50,  50]])
    
    #   initial coordinates of hospital
    hosp = np.array([0, 55])
    alpha = 0.01
    tol = 1
    
    hNew = positionHospital(cities, hosp, alpha, tol) 
    plotCoor(cities, hNew)
