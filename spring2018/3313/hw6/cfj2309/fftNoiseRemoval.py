"""
    Chris Jakins
    CSE3313 HW6
    3/21

    Code is not producing the correct output currently
"""

import numpy as np
import soundfile as sf
import matplotlib.pyplot as plt

infile = "P_9_2.wav"
outfile = "cleanMusic.wav"

data, sampleRate = sf.read(infile)

freqData = np.fft.fft(data)
numSamples = freqData.shape[0]
x = np.arange(0, numSamples)

plt.plot(x, abs(freqData))
plt.show()

midIndex = numSamples // 2
offset = midIndex - 30000 # hardcoded from sample set

freqData[midIndex - offset: midIndex + offset + 1] = 0

plt.plot(x, abs(freqData))
plt.show()

newData = np.fft.ifft(freqData)
sf.write(outfile, newData.real, sampleRate)
