# Chris Jakins
# 1000802309
# HW7 - 4/11/2019
import numpy as np
import matplotlib.pyplot as plt


def sum_of_squares(c, point):
    return np.sum(np.square(point.T - c))


def gradient(c, x):
    n = c.shape[0]
    sums = np.sum(c, axis = 0)
    grad = np.array([ -2 * sums[0] + 2 * n * x[0][0] ,
                      -2 * sums[1] + 2 * n * x[1][0] ])

    return grad



def positionHospital(c, h, alpha, tol):
    h = h.reshape(h.shape[0], 1)
    old_h = np.zeros(h.shape)
    i = 0

    hosp_c = [h]
    while np.linalg.norm(h - old_h) > tol:
        ssd = sum_of_squares(c, h)
        grad = -1 * gradient(c, h)

        old_h = h
        h = h + grad.reshape(grad.shape[0], 1) * alpha

        print('k = %d, fVal = %.2f, grad = [%.2f, %.2f], h = [%.2f, %.2f]\n'
              % (i, ssd, grad[0], grad[1], h[0], h[1]))
        hosp_c.append(h)
        i += 1

    return np.asarray(hosp_c)


def plotCoor(cities, hospital):
    plt.plot(cities[:,0], cities[:,1], 'o')
    plt.plot(hospital[:,0], hospital[:,1], 'x')
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
