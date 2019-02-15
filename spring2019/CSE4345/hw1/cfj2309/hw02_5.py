# Chris Jakins 1000802309
#
#
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm

h1_string = 'book_horstmann1_gray.jpg'
h2_string = 'book_horstmann1_gray2.png'
faus_string = 'book_fausett_gray.jpg'

horst1 = plt.imread(h1_string)
horst2 = plt.imread(h2_string)
faus = plt.imread(faus_string)


def show_images():
    fig = plt.figure()
    fig.add_subplot(1, 3, 1)
    plt.imshow(horst1, cmap = cm.gray)
    fig.add_subplot(1, 3, 2)
    plt.imshow(horst2, cmap = cm.gray)
    fig.add_subplot(1, 3, 3)
    plt.imshow(faus, cmap = cm.gray)
    fig.tight_layout()

    plt.show()


def norm_and_print(name1, name2, norm, img1, img2):
    print('%s, %s' % (name1, name2))
    print(norm, '=', np.linalg.norm(img1 - img2, ord = norm))


show_images()
norm_and_print(h1_string, h2_string, 'fro', horst1, horst2)
print('------------------------------------')
norm_and_print(h1_string, faus_string, 'fro', horst1, faus)
print('------------------------------------')
norm_and_print(h2_string, faus_string, 'fro', horst2, faus)
print('------------------------------------')


norm_and_print(h1_string, h2_string, 2, horst1.flatten('F'), horst2.flatten('F'))
print('------------------------------------')
norm_and_print(h1_string, faus_string, 2, horst1.flatten('F'), faus.flatten('F'))
print('------------------------------------')
norm_and_print(h2_string, faus_string, 2, horst2.flatten('F'), faus.flatten('F'))
print('------------------------------------')
