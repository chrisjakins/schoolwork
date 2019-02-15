# Chris Jakins 1000802309
#
#
import numpy as np
import matplotlib.pyplot as plt

x_y = np.genfromtxt('circle-data.csv', delimiter = ',')

b = np.sum(np.square(x_y), axis = 1).reshape(len(x_y), 1)

a = np.multiply(x_y, 2)
ones = np.ones(len(x_y)).reshape(len(x_y), 1)
a = np.append(a, ones, 1)

x, res, rank, s = np.linalg.lstsq(a, b, rcond = None)
r = np.sqrt(x[-1] - x[0]**2 - x[1]**2)

print('h = ', x[0])
print('k = ', x[1])
print('r = ', r)

c = plt.Circle((x[0], x[1]), radius = r, fill = False)
ax = plt.gca()
ax.add_patch(c)
plt.axis('equal')
plt.scatter(x_y[:,0], x_y[:,1])
plt.scatter(x[0], x[1], marker = 'x')
plt.show()
