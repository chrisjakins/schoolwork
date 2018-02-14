"""
examples of periodic signals, p 64, McClellan

January 24, 2014    created
February 10, 2018   ported to Python
"""

import numpy as np
import matplotlib.pyplot as plt

t = np.arange(0, 01., 1/1000)
f = 25

# triangle wave
k = 1
x1 = -8/(k*k*np.pi*np.pi)*np.cos(2*np.pi*k*f*t)
k = 3
x3 = -8/(k*k*np.pi*np.pi)*np.cos(2*np.pi*k*f*t)
k = 5
x5 = -8/(k*k*np.pi*np.pi)*np.cos(2*np.pi*k*f*t)
k = 7
x7 = -8/(k*k*np.pi*np.pi)*np.cos(2*np.pi*k*f*t)

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
plt.plot(t, x1+x3+x5+x7)
plt.title("uses 4 harmonics")

plt.tight_layout()
plt.show()

y = np.zeros(t.shape)

k = 1
while k < 51 :
    x = -8/(k*k*np.pi*np.pi)*np.cos(2*np.pi*k*f*t)
    y = y + x
    k += 2

plt.figure(2)
plt.plot(t, y)
plt.title("uses first 25 harmonics")

plt.show()
