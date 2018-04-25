"""
    Chris Jakins
    1000802309
    HW8 CSE3313
    4/11
"""
import numpy as np
import matplotlib.image as mpimg
import matplotlib.pyplot as plt
from skimage.feature import match_template


#
#   SETUP
#

filenameSmall = "ERBwideColorSmall.jpg"
filenameTemplate = "ERBwideTemplate.jpg"

#
#   Functions
#

# function taken from 
# stackoverflow.com/questions/12201577/
#    how-can-i-convert-an-rgb-image-into-grayscale-in-python
def rgb2gray(img):
    r, g, b = img[:,:,0], img[:,:,1], img[:,:,2]
    gray = 0.2989 * r + 0.587 * g + 0.114 * b

    return gray

#
#   Main
#

img = mpimg.imread(filenameSmall)
template = mpimg.imread(filenameTemplate)

img = rgb2gray(img)
template = rgb2gray(template)

plt.imshow(img, cmap = "gray")
plt.show()

plt.imshow(template, cmap = "gray")
plt.show()

# this code taken from 
# http://scikit-image.org/docs/dev/auto_examples/features_detection/plot_template.html
result = match_template(img, template)
ij = np.unravel_index(np.argmax(result), result.shape)
x, y = ij[::-1]

print(x, y)

# how do i do this better
for i in range(y, y + template.shape[1]):
    for j in range(x, x + template.shape[0]):
        img[i][j] = 0

plt.imshow(img, cmap = "gray")
plt.show()
