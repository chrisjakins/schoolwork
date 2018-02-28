"""
    Chris Jakins
    1000802309
    HW4 CSE3313
    2/28
"""
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
from scipy import ndimage

#   SETUP

filenames = ["clock-5.1.12.tiff", "boat.512.tiff", "man-5.3.01.tiff", "tank-7.1.07.tiff"]

filenameDarin = "darinGrayNoise.jpg"

lpFilter = np.empty(10)
lpFilter.fill(.1)

hpFilter = np.array([1, -1])

#   FUNCTIONS

def imageProcessing(filename) :
    img = mpimg.imread(filename)

    plt.imshow(img)
    plt.title("Original image : %s" % (filename))
    plt.show()
    
    plt.imshow(lowpassFilter(img))
    plt.title("Applying lowpass filter : %s" % (filename))
    plt.show()

    plt.imshow(highpassFilter(img))
    plt.title("Applying highpass filter : %s" % (filename))
    plt.show()

def noiseRemoval(filename) :
    img = mpimg.imread(filename)

    plt.imshow(img)
    plt.title("Original image : %s" % (filename))
    plt.show()

    plt.imshow(lowpassFilter(img))
    plt.title("Applying lowpass filter : %s" % (filename))
    plt.show()

    plt.imshow(medianFilter(img))
    plt.title("Applying median filter : %s" % (filename))
    plt.show()

#   FILTERS

def lowpassFilter(img) :
    lowpassedImg = []
    for row in range(0, img.shape[0]) :
        lowpassedImg.append(np.convolve(img[row, :], lpFilter))

    return np.asarray(lowpassedImg)

def highpassFilter(img) :
    highpassedImg = []
    for row in range(0, img.shape[0]) :
        highpassedImg.append(np.convolve(img[row, :], hpFilter))

    return np.asarray(highpassedImg)

def medianFilter(img) :
   return ndimage.median_filter(img, 5)

#
#   EFFECTIVE MAIN
#

for filename in filenames :
    imageProcessing(filename)

noiseRemoval(filenameDarin)
