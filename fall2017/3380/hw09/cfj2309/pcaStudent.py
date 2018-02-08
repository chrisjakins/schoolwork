# Chris Jakins CSE 3380 HW9
import numpy as np

def pcaStudent(points) :
    meanArray = np.mean(points, axis = 0)

    S = np.array(points - meanArray)
    covMatrix = (S.T).dot(S)

    eigValues, eigVectors = np.linalg.eig(covMatrix)
    fpc = eigVectors[np.argmax(eigValues)]

    return S, covMatrix, fpc
