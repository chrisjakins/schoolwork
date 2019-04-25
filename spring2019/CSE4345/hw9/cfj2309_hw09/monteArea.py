#   Chris Jakins
#   1000802309
#   HW9 4/30
import numpy as np
import matplotlib.pyplot as plt


def gen_random(n):
    x = np.random.uniform(2, 10, (n, 1))
    y = np.random.uniform(2, 6, (n, 1))
    
    return x,y


def in_bounds(x, y):
    return x >= (y + 2) / 2 and x <= (y + 15) / 2 \
       and y >= x / 7 + 12 / 7 and y <= -x / 6 + 20 / 3



def estArea(samples):
    xs, ys = gen_random(samples)
   
    points = []
    for x, y in zip(xs, ys):
        if in_bounds(x, y):
            points.append((x,y))

    [plt.scatter(point[0], point[1]) for point in points]
    plt.show()

    percentage = len(points) / samples
    print('Percentage = ', percentage)
    print('Area = ', percentage * 32)


########################  main  ########################
if __name__ == "__main__" :
    samples = 10000

    estArea(samples)

