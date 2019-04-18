# Chris Jakins
# 1000802309
# HW8 4/23
import numpy as np
import matplotlib.pyplot as plt
from PIL import Image


def showImages(images):
    for image in images:
        plt.figure()
        plt.imshow(image)
    plt.show()


def writeToFile(images):
    for i in range(1, len(images) + 1):
        plt.imsave("mid%02d.jpg" % (i), images[i - 1])


def intermediate(firstImage, lastImage, N, display) :
    firstImage = plt.imread(firstImage).astype(np.int16)
    lastImage = plt.imread(lastImage).astype(np.int16)

    steps = (lastImage - firstImage) / N
    images = [firstImage]
    
    for i in range(1, N):
        images.append(images[-1][:,:] + steps)
    images.append(lastImage)
    images = [x.astype(np.uint8) for x in images]

    if display:
        showImages(images)
    else:
        writeToFile(images)



###############  main  ###############
if __name__ == "__main__" :
    name1 = "darinYoung.jpg"  # first image
    name2 = "darinOld.jpg"    #  last image
    
    N = 10    # should produce N-1 intermediate images
    
    display = False   # True means display intermediate images
                     # False means save intermediate images
    intermediate(name1, name2, N, display)
