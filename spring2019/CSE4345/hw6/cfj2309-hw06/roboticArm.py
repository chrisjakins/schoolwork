# Chris Jakins
# 1000802309
# 4/4
import numpy as np
import math 



def jacobian(x, d):
    return np.array([ [ -d[0] * np.sin(x[0][0]) - d[1] * np.sin(x[0][0] + x[1][0]), -d[1] * np.sin(x[0][0] + x[1][0]) ],
                      [  d[0] * np.cos(x[0][0]) + d[1] * np.cos(x[0][0] + x[1][0]),  d[1] * np.cos(x[0][0] + x[1][0]) ] ])


def f(x, d, p):
    return np.array([[ d[0] * np.cos(x[0][0]) + d[1] * np.cos(x[0][0] + x[1][0]) - p[0] ],
                     [ d[0] * np.sin(x[0][0]) + d[1] * np.sin(x[0][0] + x[1][0]) - p[1] ]])


def positioning(alpha, beta, d1, d2, p1, p2):
    x = np.array([[alpha], [beta]])
    d = np.array([d1, d2])
    p = np.array([p1, p2])

    for i in range(0, 6):
        jac = jacobian(x, d)
        f_x = f(x, d, p)
        s = np.linalg.solve(jac, f_x)

        x -= s
        print('[a b].T = \n', x, '\n')

    return x


##############  main  ##############
if __name__ == "__main__":
    #positioning(0.7, 0.7, 5, 6, 10, 4)
    positioning(0.7, 0.7, math.sqrt(29), math.sqrt(10), 6, 5)
