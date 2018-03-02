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
filterBank = []
outputs = []

#   FUNCTIONS

def setupFilters() :
    for freq in frequencyBank :
        interim = []
        for n in range(0, filterLength) :
            interim.append(
                2 / filterLength * np.cos(2 * np.pi * freq * n / sampleRate)
            )
        filterBank.append(interim)




#
#   EFFECTIVE MAIN
#

data = np.genfromtxt(filename, delimiter = ',')
setupFilters()

for f in filterBank :
    outputs.append(np.convolve(f, data))

print(outputs)

"""
x, y = freqz(filterBank[0], 1) 
plt.plot(x, abs(y))
plt.show()
"""
