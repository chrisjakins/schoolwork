#   Chris Jakins
#   HW10

import numpy as np

def svdStudent(A, b) :
    x1, residuals, rank, s = np.linalg.lstsq(A, b)
    norm1 = np.linalg.norm(b - A.dot(x1))

    u, s, v = np.linalg.svd(A)
    
    x2 = 0
    for i in range(0, A.shape[1]) :
        x2 += (u[:, i].T).dot(b) / s[i] * v[:, i]
    
    norm2 = np.linalg.norm(b - A.dot(x2))

    erank = np.sum(s >= 0.001)

    x3 = 0
    for i in range(0, erank) :
        x3 += (u[:, i].T).dot(b) / s[i] * v[:, i]

    norm3 = np.linalg.norm(b - A.dot(x3))

    return x1, norm1, x2, norm2, erank, x3, norm3
