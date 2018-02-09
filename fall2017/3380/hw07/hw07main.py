"""
    Mon Oct 16 15:13:40 CDT 2017

    DO NOT MODIFY THIS FILE
    edit the file hw07student.py
"""

import numpy as np
from hw07student import *

A = np.array([(1, 5, -6),
              (2, 0, 3),
              (4, 8, 2)])
b = np.array([46, -13, 34])

x, C, d, y, normXY = hw07student(A, b)

print( "x: ", x )
print( "\nC:\n", C )
print( "d:", d )
print( "y:", y )
print( "\n||x - y||: ", normXY )
