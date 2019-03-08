# Chris Jakins 1000802309
# HW4 - 3/5/2019
#

import numpy as np

num_samples_per = 400
train_data = np.genfromtxt('digitsTrainCombined.csv', delimiter = ',')
test_data = np.genfromtxt('digitsTestCombined.csv', delimiter = ',')
ks = np.array([1, 5, 20, 100, 256])


def print_results(k, results):
    total = 0
    print('------------ k = %d -------------' % (k))
    for i in range(0, len(results)):
        print('digit = %d, right = %3d, wrong = %3d' % (i, results[i], 100 - results[i]))
        total += results[i]
    print('\nTotals:    right = %4d, wrong = %4d,  %.2f%%\n'
            % (total, 1000 - total, total / 10))


# get all U matrices for each digit
Us = []
for i in range(0, train_data.shape[1] // num_samples_per):
    u, sig, vt = np.linalg.svd(train_data[:, i * num_samples_per : i * num_samples_per + num_samples_per])
    Us.append(u)


# classify test data
for k in ks:
    results = np.zeros((10, 1))

    inners = []
    for u in Us:
        U = u[:,:k].reshape(u.shape[0], k)
        udot = np.dot(U, U.T)
        inners.append(np.identity(udot.shape[0]) - udot)

    inners = np.asarray(inners)

    for i in range(0, test_data.shape[1]):
        pre = inners.dot(test_data[:, i])
        norms = np.linalg.norm(pre, axis = 1, ord = 2)
        index = np.argmin(norms)

        if index == i // 100:
            results[i // 100] += 1

    print_results(k, results)
