# Chris Jakins
# 1000802309
# HW8 4/23
import numpy as np
import matplotlib.pyplot as plt


def resizeImage(name) :
    image = plt.imread(name)

    resized = np.zeros((image.shape[0] * 2 - 1, image.shape[1] * 2 - 1, 3))

    for i in range(0, resized.shape[0]):
        for j in range(0, resized.shape[1]):

            if i % 2 == 0 and j % 2 == 0:
                resized[i, j, :] = image[i//2, j//2, :]

            elif i % 2 == 0:
                resized[i, j, :] = (image[i//2, j//2 + 1, :] + image[i//2, j//2, :]) / 2

            elif j % 2 == 0:
                resized[i, j, :] = (image[i//2 + 1, j//2, :] + image[i//2, j//2,:]) / 2

            else:
                resized[i, j, :] = (image[i//2, j//2, :] + image[i//2 + 1, j//2, :] + image[i//2, j//2 + 1, :] + image[i//2 + 1, j//2 + 1, :]) / 4

    resized = np.floor(resized)

    plt.imshow(image)
    plt.show()
    plt.imshow(resized)
    plt.show()



####################  main  ####################
if __name__ == "__main__" :
    filename = "book_fausett_small.jpg"
    resizeImage(filename) 
