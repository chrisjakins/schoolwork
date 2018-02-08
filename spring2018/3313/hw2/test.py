"""
    Chris Jakins
    1000802309
    CSE 3313
    HW2 2/7/18
"""

import numpy as np
import scipy.io.wavfile

noteNumsTreb = np.array([52, 52, 59, 59, 61, 61, 59, 59,
                         57, 57, 56, 56, 54, 54, 52, 52,
                         59, 59, 57, 57, 56, 56, 54, 54])

noteNumsBass = np.array([28, 40, 44, 40, 45, 40, 44, 40,
                         42, 39, 40, 37, 33, 35, 28, 28,
                         44, 35, 42, 35, 40, 35, 39, 35])

frequenciesTreb = 440 * ( 2**( (noteNumsTreb - 49)/12 ) )
frequenciesBass = 440 * ( 2**( (noteNumsBass - 49)/12 ) )

sampleFreq = 8000
time = np.arange(0, .5, 1 / sampleFreq)

notes = np.array([])
i = 0
while i < frequenciesTreb.shape[0] :
    samplesTreb = np.cos( 2 * np.pi * frequenciesTreb[i] * time )
    samplesBass = np.cos( 2 * np.pi * frequenciesBass[i] * time )
    notes = np.append(notes, samplesTreb + samplesBass)
    i += 1

scipy.io.wavfile.write("twinkle.wav", sampleFreq, notes)
