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

testData, testSampleRate = sf.read(testFilename)
songs = glob.glob(pattern)
signatures = [] 

results = []



for f in songs:
    data, sampleRate = sf.read(f)
    f, t, sxx = spectrogram(data, fs = sampleRate, nperseg = int(.5 * sampleRate))
