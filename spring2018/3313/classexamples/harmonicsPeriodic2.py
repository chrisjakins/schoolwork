"""
    periodic waves

    Tue Feb 13 23:11:24 CST 2018
"""

import numpy as np
import matplotlib.pyplot as plt

t = np.arange(0, 2, 1/1000)

x1 = np.cos(2*np.pi*4.5*t)
x2 = np.cos(2*np.pi*7.5*t)

x = x1 + x2

plt.subplot(3, 1, 1)
plt.title("4.5 Hz signal")
plt.plot(t, x1)

plt.subplot(3, 1, 2)
plt.title("7.5 Hz signal")
plt.plot(t, x2)

plt.subplot(3, 1, 3)
plt.plot(t, x)
plt.title("Combined signal")

plt.tight_layout()
plt.show()
