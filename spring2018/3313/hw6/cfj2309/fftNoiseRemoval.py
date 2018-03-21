import numpy as np
import soundfile as sf
import matplotlib.pyplot as plt

infile = "P_9_2.wav"
outfile = "cleanMusic.wav"

data, sampleRate = sf.read(infile)

freqData = abs(np.fft.fft(data))
numSamples = freqData.shape[0]
x = np.arange(0, numSamples)
"""
plt.plot(x, freqData)
plt.show()
"""
midIndex = numSamples // 2
offset = midIndex - 30000 # hardcoded from sample set
print(numSamples)
print(freqData[29999])
print(freqData[47825])
print(midIndex - offset + 1)
print(midIndex + offset + 1)

#freqData[midIndex - offset: midIndex + offset + 1] = 0
freqData[29999 : 47826] = 0
print(freqData[29999])
print(freqData[47825])

print(midIndex)
print(freqData[midIndex - offset + 1])

plt.plot(x, freqData)
plt.show()

newData = np.fft.ifft(freqData)
sf.write(outfile, newData.real, sampleRate)
