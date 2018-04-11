"""
    Chris Jakins
    HW8 CSE3313
    4/11
"""
import numpy as np
import matplotlib.pyplot as plt
import soundfile as sf

#
#   setup
#
configFile = "shelvingConfig.txt"
outfile = "shelvingOutput.wav"

#   defining these for later
infile = ""
gain = 0
cutoff = 0

#
#   effective main
#
config = open(configFile, "r")
args = config.read().split("\n")

infile = args[0]
gain = int(args[1])
cutoff = int(args[2])

data, sampleRate = sf.read(infile)

# setting up needed variables
fundamental = sampleRate / len(data)

mu = 10**(gain / 20)
thetaC = 2 * np.pi * cutoff / sampleRate

num = 1 - (4 / (1 + mu)) * np.tan(thetaC / 2)
den = 1 + (4 / (1 + mu)) * np.tan(thetaC / 2)

gamma = num / den
alpha = (1 - gamma) / 2
    

# this process taken from DSP First
outData = []
for i in range(len(data)):
    if i == 0:
        outData.append(alpha * (data[0]))
    else:
        outData.append(
                alpha * (data[i] + data[i - 1]) + gamma * outData[i - 1]
                )

finalData = []
for i in range(len(outData)):
    finalData.append(data[i] + (mu - 1) * outData[i])

#
#   plotting
#

freqData = np.fft.fft(data)
filteredFreq = np.fft.fft(finalData)

maxVal = np.amax(freqData)
#   generate the frequencies for corresponding bins in dft
xaxis = [fundamental * x for x in range(len(freqData) // 4)]

plt.subplot(1, 2, 1)
plt.plot(xaxis, abs(freqData[:len(freqData) // 4]))
ymin, ymax = plt.ylim()
plt.ylim([ymin, maxVal + 100])

plt.subplot(1, 2, 2)
plt.plot(xaxis, abs(filteredFreq[:len(finalData) // 4]))
plt.ylim([ymin, maxVal + 100])

plt.tight_layout()
plt.show()

#
#   write out modified soundfile
#

sf.write(outfile, finalData, sampleRate)
