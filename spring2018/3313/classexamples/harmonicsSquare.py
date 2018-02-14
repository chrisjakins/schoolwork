"""
examples of periodic signals, p 64, McClellan

January 24, 2014     created
February 10, 2018    ported to Python
"""

import numpy as np
import matplotlib.pyplot as plt
t = np.arange(0, 0.1, 1/1000)
f = 25

# square wave
k = 1
x1 = 4/(k*np.pi)*np.cos(2*np.pi*k*f*t - np.pi/2)
k = 3
x3 = 4/(k*np.pi)*np.cos(2*np.pi*k*f*t - np.pi/2)
k = 5
x5 = 4/(k*np.pi)*np.cos(2*np.pi*k*f*t - np.pi/2)
k = 7
x7 = 4/(k*np.pi)*np.cos(2*np.pi*k*f*t - np.pi/2)

plt.subplot(4, 1, 1)
plt.title("uses 1 harmonic")
plt.plot(t, x1)

plt.subplot(4, 1, 2)
plt.title("uses 2 harmonics")
plt.plot(t, x1+x3)

plt.subplot(4, 1, 3)
plt.title("uses 3 harmonics")
plt.plot(t, x1+x3+x5)

plt.subplot(4, 1, 4)
plt.title("uses 4 harmonics")
plt.plot(t, x1+x3+x5+x7)

plt.tight_layout()
plt.show()


# use 25 harmonics
y = np.zeros(t.shape)

k = 1
while k < 51:
    x = 4/(k*np.pi)*np.cos(2*np.pi*k*f*t - np.pi/2)
    y = y + x
    k += 2

plt.figure(2)
# note that the little bump at the top of the square before the line
#   drops is called the Gibbs phenomenon
plt.title("uses first 25 harmonics")
plt.plot(t, y)

plt.tight_layout()
plt.show()
