"""
    Chris Jakins
    HW9 CSE3313
    4/18
"""

import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import spectrogram
import soundfile as sf
import glob

#
#   Setup
#

testFilename = "testSong.wav"
pattern = "song-*.wav"

songDB = {}


#
#   Functions
#

def calcSignature(data, fs):
    f, t, sxx = spectrogram(data, fs = fs, nperseg = int(.5 * fs))
    return f[np.argmax(sxx, axis = 0)]

#
#   Main
#


testData, testSampleRate = sf.read(testFilename)
testSignature = calcSignature(testData, testSampleRate)
testNorm = np.linalg.norm(testSignature, ord = 1)

songs = glob.glob(pattern)

for f in songs:
    data, sampleRate = sf.read(f)
    signature = calcSignature(data, sampleRate)
    songDB[f] = np.linalg.norm(signature - testSignature, ord = 1)

for key, value in sorted(songDB.items(), key = lambda x: x[1]):
    print("%.1f %s" % (value, key))
