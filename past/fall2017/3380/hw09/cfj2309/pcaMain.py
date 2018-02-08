"""
    ported from MATLAB to Python
    Sun May  7 14:02:32 CDT 2017
"""
import numpy as np
from pcaStudent import *
import matplotlib.pyplot as plt

#
#  DO NOT MODIFY THIS FILE
#  create the file pcaStudent.py
#

def plotPCA(points, fpc) :
    x = points[:, 0];   # make plotting easier to write
    y = points[:, 1];

    plt.plot(x, y, '.')
    mult = 10
    plt.plot([-mult*abs(fpc[0]), mult*abs(fpc[0])], [-mult*abs(fpc[1]), mult*abs(fpc[1])], 'm-')

    xmin = min(x) - 1
    xmax = max(x) + 1
    ymin = min(y) - 1
    ymax = max(y) + 1
    plt.axis([xmin, xmax, ymin, ymax])
    plt.title("points and first principal component")

    # from https://stackoverflow.com/questions/16183462/saving-images-in-python-at-a-very-high-quality
    #plt.savefig('pca.eps', format='eps', dpi=1000)

    plt.show()     # this causes the plot to display


######   main   ######
points = np.array([[2, 4, 3, 5, 6, 4, 5, 7, 5, 6, 7],
                   [2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 6]]).T

shiftedPoints, covMatrix, fpc = pcaStudent(points)
# shiftedPoints is a nx2 matrix
# covMatrix is a 2x2 matrix
# fpc is an 2x1 column vector

print("part a: shifted points")
print(shiftedPoints.T)  # transpose to use less space in displaying

print("\npart b: covariance matrix")
print(covMatrix)

print("\npart c: first principal component")
print(fpc)

plotPCA(points, fpc)
