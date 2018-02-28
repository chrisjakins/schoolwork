"""
    Chris Jakins
    1000802309
    HW4 CSE3313
    2/28
"""
import numpy as np
import matplotlib.pyplot as plt

def lowpass(signal) :
    cutoff = 50
    filterLength = 21
    M = filterLength - 1
    normCutoff = cutoff / sampleRate

    filterWeights = []
    for n in range(0, filterLength) :
        if n == M / 2 :
            filterWeights.append(2 * normCutoff)
        else :
            filterWeights.append(
                np.sin(2 * np.pi * normCutoff * (n - M / 2)) / (np.pi * (n - M / 2))
            )
    return np.convolve(signal, filterWeights)


def highpass(signal) :
    cutoff = 280
    filterLength = 21
    M = filterLength - 1
    normCutoff = cutoff / sampleRate

    filterWeights = []
    for n in range(0, filterLength) :
        if n == M / 2 :
            filterWeights.append(1 - (2 * normCutoff))
        else :
            filterWeights.append(
                -1 * np.sin(2 * np.pi * normCutoff * (n - M / 2)) / (np.pi * (n - M / 2))
            )
    return np.convolve(signal, filterWeights)
#
#   EFFECTIVE MAIN
#

#   SETUP

filename = "data-filtering.csv"
sampleRate = 2000

data = np.genfromtxt(filename, delimiter=',')

time1 = np.arange(0, 2000)      # sample values for original data
time2 = np.arange(0, 2020)      # sample values for lowpassed data
time3 = np.arange(0, 1, 1/2000) # time values for 4 Hz & 330 Hz sinusoids
time4 = np.arange(0, 100)       # time values for highpassed data

lowpassData = lowpass(data)
highpassData = highpass(data)
sig4 = np.cos(2 * np.pi * 4 * time3)
sig330 = np.cos(2 * np.pi * 330 * time3)

#   LOWPASSED PLOTTING

plt.figure()
plt.subplot(3, 1, 1)
plt.plot(time1, data)
plt.title("Original data")

plt.subplot(3, 1, 2)
plt.plot(time1, sig4)            # plots with 2000 sample values
plt.title("4 Hz signal")

plt.subplot(3, 1, 3)
plt.plot(time2, lowpassData)
plt.title("Application of lowpass filter")

plt.tight_layout()

#   HIGHPASSED PLOTTING

plt.figure()
plt.subplot(3, 1, 1)
plt.plot(time4, data[0: 100])
plt.title("Original data")

plt.subplot(3, 1, 2)
plt.plot(time4, sig330[0: 100])
plt.title("330 Hz signal")

plt.subplot(3, 1, 3)
plt.plot(time4, highpassData[0: 100])
plt.title("Application of highpass filter")

plt.tight_layout()
plt.show()
