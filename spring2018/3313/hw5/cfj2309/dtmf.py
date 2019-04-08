"""
    Chris Jakins
    1000802309
    HW5 CSE3313
    3/7
"""

import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import freqz

#   SETUP

filename = "tones.csv"
sampleRate = 8000
numSamples = 4000
filterLength = 64

frequencyBank = np.array([697, 770, 852, 941, 1209, 1336, 1477])
phoneDigits = [[1,   2,  3],
               [4,   5,  6],
               [7,   8,  9],
               ['*', 0, '#']]

filterBank = []

#   FUNCTIONS

def setupFilters() :
    for freq in frequencyBank :
        interim = []
        for n in range(0, filterLength) :
            interim.append(
                2 / filterLength * np.cos(2 * np.pi * freq * n / sampleRate)
            )
        filterBank.append(interim)

def printDigit(data) :
    # here I get the index values of the highest two elements of the input
    # I make the assumption (due to the my choice of data structure) that
    # one of the highest elements will be in the first four data values, and
    # the other will be in last 3
    ind1 = np.argmax(data[0:4])
    ind2 = np.argmax(data[4:])

    print(phoneDigits[ind1][ind2], end = "")

#
#   EFFECTIVE MAIN
#

data = np.genfromtxt(filename, delimiter = ',')
setupFilters()

for i in range(0, data.shape[0] // numSamples) :
    filterOuts = []
    for f in filterBank :
        filterOuts.append(np.convolve(f, data[i * 4000: 4000 + i * 4000]))

    filterOuts = np.asarray(filterOuts)
    filterOuts = [np.mean(x ** 2) for x in filterOuts]

    printDigit(np.asarray(filterOuts))


print()


x_ys = [freqz(filterBank[i], 1) for i in range(len(filterBank))]
#x, y = freqz(filterBank[0], 1) 
#plt.plot(x, abs(y))
for x_y in x_ys:
    plt.plot(x_y[0], abs(x_y[1]))

plt.show()
