#   Chris Jakins
#   HW10 

import numpy as np

def aiSVDstudent(k, pClass, xClass, test1, test2) :
    pU, pS, pV = np.linalg.svd(pClass)
    xU, xS, xV = np.linalg.svd(xClass)

    Ukp = pU[:, 0:k]
    Ukx = xU[:, 0:k]

    intUKP = Ukp.dot(Ukp.T)
    intUKX = Ukx.dot(Ukx.T)

    intIMP = np.identity(intUKP.shape[0]) - intUKP
    intIMX = np.identity(intUKX.shape[0]) - intUKX

    np1 = np.linalg.norm(intIMP.dot(test1))
    nx1 = np.linalg.norm(intIMX.dot(test1))
    np2 = np.linalg.norm(intIMP.dot(test2))
    nx2 = np.linalg.norm(intIMX.dot(test2))

    return Ukp, Ukx, np1, nx1, np2, nx2
