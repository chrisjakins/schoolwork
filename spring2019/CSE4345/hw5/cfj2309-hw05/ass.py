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

b = data[:,-1]
A = data[:,:-1]

x = np.linalg.pinv(A.T @ A) @ A.T @ b
print('x = ')
print(x.reshape(x.shape[0], 1))

# print 2 norm of residual

ata = A.T @ A
atb = A.T @ b

x2 = np.linalg.solve(ata, atb)

print('\nx = ')
print(x2.reshape(x2.shape[0], 1))

# print 2 norm of residual

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


print('x = ')
print(x3.reshape(x3.shape[0], 1))

# print 2 norm of residual
print('Condition number of A.T A = ', end = '')
print(np.linalg.cond(ata))
