# Chris Jakins 1000802309
#
#
import numpy as np

delta = np.array([[0], [0], [.5]])

b1 = np.array([[1], [2.8], [4.61]])
a1 = np.array([[.1, .2, .3],
               [.4, .5, .6],
               [.7, .8, .91]])


b2 = np.array([[1], [3.2], [0.5]])
a2 = np. array([[.1, .2, .3],
                [.6, .5, .4],
                [.1, .5, -.8]])


x1 = np.linalg.solve(a1, b1)
x_hat1 = np.linalg.solve(a1, b1 + delta)

x2 = np.linalg.solve(a2, b2)
x_hat2 = np.linalg.solve(a2, b2 + delta)


print('A -------')
print('\nbefore perturbing:\n\n', x1)
print('\nafter perturbing:\n\n', x_hat1)
print('\nconclusion: ill-conditioned')
print('---------------------------\n')
print('B -------')
print('\nbefore perturbing:\n\n', x2)
print('\nafter perturbing:\n\n', x_hat2)
print('\nconclusion: well-conditioned')
print('---------------------------\n')
