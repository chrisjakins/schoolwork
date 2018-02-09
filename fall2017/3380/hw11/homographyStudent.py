import numpy as np

def homographyStudent(sk, corr, test) :


    T = np.array([[sk[0][0], sk[1][0], 1, 0, 0, 0, 0, 0, -corr[0][0], 0, 0, 0],
                  [0, 0, 0, sk[0][0], sk[1][0], 1, 0, 0, -corr[1][0], 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, sk[0][0], sk[1][0], -1, 0, 0, 0],
                  [sk[0][1], sk[1][1], 1, 0, 0, 0, 0, 0, 0, -corr[0][1], 0, 0],
                  [0, 0, 0, sk[0][1], sk[1][1], 1, 0, 0, 0, -corr[1][1], 0, 0],
                  [0, 0, 0, 0, 0, 0, sk[0][1], sk[1][1], 0, -1, 0, 0],
                  [sk[0][2], sk[1][2], 1, 0, 0, 0, 0, 0, 0, 0, -corr[0][2], 0],
                  [0, 0, 0, sk[0][2], sk[1][2], 1, 0, 0, 0, 0, -corr[1][2], 0],
                  [0, 0, 0, 0, 0, 0, sk[0][2], sk[1][2], 0, 0, -1, 0],
                  [sk[0][3], sk[1][3], 1, 0, 0, 0, 0, 0, 0, 0, 0, -corr[0][3]],
                  [0, 0, 0, sk[0][3], sk[1][3], 1, 0, 0, 0, 0, 0, -corr[1][3]],
                  [0, 0, 0, 0, 0, 0, sk[0][3], sk[1][3], 0, 0, 0, -1]])

    d = np.array([0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1])

    hVector = np.linalg.solve(T, d.T)

    H = np.array([[hVector[0], hVector[1], hVector[2]],
                  [hVector[3], hVector[4], hVector[5]],
                  [hVector[6], hVector[7], 1]])

    projected = H.dot(test)

    for i in range(0, projected.shape[1]) :
        projected[:, i] /= projected[2][i]

    return H, projected
