"""
    periodic waves

    February 2, 2014    created
    February 10, 2018   ported to Python
"""

import numpy as np
import matplotlib.pyplot as plt

t = np.arange(0, 1, 1/1000)

x1 = 3 * np.cos(2*np.pi*4*t)
x2 = np.cos(2*np.pi*6*t - np.pi/4)

x = x1 + x2

plt.subplot(3, 1, 1)
plt.title("4 Hz signal")
plt.plot(t, x1)

plt.subplot(3, 1, 2)
plt.title("6 Hz signal")
plt.plot(t, x2)

plt.subplot(3, 1, 3)
plt.plot(t, x)
plt.title("Combined signal")

plt.tight_layout()
plt.show()
