import numpy as np
import matplotlib.pyplot as plt
import soundfile as sf

#   setup
configFile = "shelvingConfig.txt"










#
#   effective main
#
config = open(configFile, "r")
args = config.read().split("\n")

infile = args[0]
data, sampleRate = sf.read(infile)
fundamental = sampleRate / len(data)
gain = int(args[1])
cutoff = int(args[2])

freqData = abs(np.fft.fft(data))


mu = 10**(gain / 20)
thetaC = 2 * np.pi * cutoff / sampleRate

num = 1 - (4 / (1 + mu)) * np.tan(thetaC / 2)
den = 1 + (4 / (1 + mu)) * np.tan(thetaC / 2)

gamma = num / den
alpha = (1 - gamma) / 2
    



#
#   plotting
#

xaxis = [fundamental * x for x in range(len(freqData) // 4)]

plt.plot(xaxis, freqData[:len(freqData) // 4])
plt.show()
