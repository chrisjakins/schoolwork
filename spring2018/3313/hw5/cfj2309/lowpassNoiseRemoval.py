"""
    Chris Jakins
    1000802309
    HW5 CSE3313
    3/7

    must have pysoundfile installed
        'pip install pysoundfile' in your shell of choice

    filter and hamming window from 
        http://www.labbookpages.co.uk/audio/firWindowing.html
"""

import numpy as np
import soundfile as sf
from scipy.signal import freqz
import matplotlib.pyplot as plt

#   SETUP

infile = "P_9_2.wav"
outfile = "cleanMusic.wav"

cutoff = 7500
filterLength = 101
M = filterLength - 1

#   FUNCTIONS

def applyHammingWindow(weights) :
    n = np.arange(0, filterLength)
    return weights * (.54 - .46 * np.cos(2 * np.pi * n / M))

def generateLowpassFilter(sampleRate) :
    normCutoff = cutoff / sampleRate
    
    filterWeights = []
    for n in range(0, filterLength) :
        if n == M / 2 :
            filterWeights.append(2 * normCutoff)
        else :
            filterWeights.append(
                np.sin(2 * np.pi * normCutoff * (n - M / 2)) / (np.pi * (n - M / 2))
            )
    return np.asarray(filterWeights)

#
#   EFFECTIVE MAIN
#

data, sampleRate = sf.read(infile)
lpWeights = generateLowpassFilter(sampleRate)

x, y = freqz(lpWeights, 1)
plt.plot(x, abs(y))

newWeights = applyHammingWindow(lpWeights)
x, y = freqz(newWeights, 1)
plt.plot(x, abs(y))
plt.show()

filteredData = np.convolve(data, newWeights)
sf.write(outfile, filteredData, sampleRate)
