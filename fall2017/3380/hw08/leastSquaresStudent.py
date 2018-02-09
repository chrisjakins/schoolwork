import numpy as np

def leastSquaresStudent(t, ft) :
    # 2 x N
    A = np.transpose(np.array((np.ones(t.shape), t)))
    b = np.transpose(np.array([ft]))

    xlin = np.linalg.lstsq(A, b)[0]
    norml = np.linalg.norm(b - A.dot(xlin))

    Aquad = np.transpose(np.array((np.ones(t.shape), t, t * t)))

    xq = np.linalg.lstsq(Aquad, b)[0]
    normq = np.linalg.norm(b - Aquad.dot(xq)) 

    #xq, normq = helper(Aquad, b)

    return xlin, norml, xq, normq


def helper(A, b) :
    interim = np.transpose(A).dot(A)
    x = np.linalg.inv(interim).dot(np.transpose(A)).dot(b)

    interim = A.dot(x)
    norm = np.linalg.norm(b - interim)

    return x, norm
