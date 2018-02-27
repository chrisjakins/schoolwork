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


def highpass() :
    print("Hello")





filename = "data-filtering.csv"
sampleRate = 2000

data = np.genfromtxt(filename, delimiter=',')
time = np.arange(0, 2020)

lowpassData = lowpass(data)

plt.subplot(3, 1, 1)
plt.plot(time, lowpassData)



plt.tight_layout()
plt.show()
