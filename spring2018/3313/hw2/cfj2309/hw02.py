"""
    Chris Jakins
    1000802309
    CSE 3313
    HW2 2/7/18
"""

import numpy as np
import scipy.io.wavfile

noteNums = np.array([52, 52, 59, 59, 61, 61, 59, 59,
                     57, 57, 56, 56, 54, 54, 52, 52,
                     59, 59, 57, 57, 56, 56, 54, 54])

frequencies = 440 * ( 2**( (noteNums - 49)/12 ) )
sampleFreq = 8000
time = np.arange(0, .5, 1 / sampleFreq)

notes = np.array([])
for f in frequencies :
    samples = np.cos( 2 * np.pi * f * time )
    notes = np.append(notes, samples)

scipy.io.wavfile.write("twinkle.wav", sampleFreq, notes)
