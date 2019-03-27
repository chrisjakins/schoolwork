# Chris Jakins
# 1000802309
# HW5
#

#
# The condition number is very high
# Looking at the data, m > n, meaning that our
#   solutions may be over-constrained
# The effective rank of A is 6 meaning that there
#   is one column that is not contributing much towards
#   A
#

import numpy as np

data = np.genfromtxt('svd-data.csv', delimiter = ',')

x_real = np.array([[1,1,1,1,1,1,1]]).T
b = data[:,-1]
A = data[:,:-1]

x = np.linalg.pinv(A.T @ A) @ A.T @ b
x = x.reshape(x.shape[0], 1)
print('x1 = ')
print(x)

# print 2 norm of residual
print('\nNorm = ', np.linalg.norm(x_real - x, ord = 2))

ata = A.T @ A
atb = A.T @ b

x2 = np.linalg.solve(ata, atb)
x2 = x2.reshape(x2.shape[0], 1)
print('\nx2 = ')
print(x2)

# print 2 norm of residual
print('\nNorm = ', np.linalg.norm(x_real - x2, ord = 2))

u, sig, vt = np.linalg.svd(A)

print('\nsingular values = ')
print(sig.reshape(sig.shape[0], 1))

eff_rank = np.count_nonzero(sig > .1)
print('\neffective rank of A = ', end = '')
print(eff_rank)

# method for hw with loop
x3 = np.zeros((vt.shape[0], 1))
for i in range(0, eff_rank):
    numer = u[:,i].T @ b.T
    x3 = x3 + (numer / sig[i] * vt[i,:]).reshape(vt[i,:].shape[0], 1)

x3.reshape(x3.shape[0], 1)
print('x3 = ')
print(x3)

# print 2 norm of residual
print('\nNorm = ', np.linalg.norm(x_real - x3, ord = 2))

print('Condition number of A.T A = ', end = '')
print(np.linalg.cond(ata))
