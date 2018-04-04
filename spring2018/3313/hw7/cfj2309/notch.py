"""
    Chris Jakins
    HW7 CSE 3313
    4/4
"""

#
#   Setup
#

import numpy as np
import matplotlib.pyplot as plt

infile = "notchData.csv"
freq = 17
sampleFreq = 500
normFreq = 2 * np.pi * freq / sampleFreq

#
#   Functions
#

def filter(data) :
    output = []
    output.append( data[0] )
    output.append(1.8744 * np.cos(normFreq) * output[0] +
                  data[1] - 2 * np.cos(normFreq) * data[0])

    for i in range(2, len(data) + 100) :
        if i < len(data) :
            output.append(1.8744 * np.cos(normFreq) * output[i - 1] -
                          .9372**2 * output[i - 2] + 
                          (data[i] if i < len(data) else 0) -
                          2 * np.cos(normFreq) * (data[i - 1] if i < len(data) + 1 else 0) + 
                          (data[i - 2] if i < len(data) + 2 else 0)
                          )

    return output

#
#   Main
#

data = np.genfromtxt(infile, delimiter = ',')
filteredData = filter(data)


#
#   Plotting
#

time = np.arange(-25, 625)

plt.figure()
fixedData = np.concatenate([np.zeros(25), data, np.zeros(125)])
plt.plot(time, fixedData)
plt.title("Original data")

plt.figure()
fixedFiltered = np.concatenate([np.zeros(25), filteredData, np.zeros(125)])
plt.plot(time, fixedFiltered)
plt.title("Filtered data")

plt.figure()
time2 = np.arange(0, 1, 1/650)
plt.plot(time, np.cos(2 * np.pi * 10 * time2) + np.cos(2 * np.pi * 33 * time2))
plt.title("10 & 33 Hz signals combined")

plt.show()
