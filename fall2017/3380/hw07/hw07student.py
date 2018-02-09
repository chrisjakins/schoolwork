"""
    Chris Jakins
    CSE 3380 HW7
    10/24
"""

import numpy as np

def hw07student(A, b) :
    x = np.linalg.solve(A, b)

    eye3 = np.eye(A.shape[0]) 
    C = A + eye3 

    ones3 = np.ones(b.shape)
    d = b + ones3.transpose()

    y = np.linalg.solve(C, d)
    normXY = np.linalg.norm(x - y) 

    #  keep this return statement
    return x, C, d, y, normXY
