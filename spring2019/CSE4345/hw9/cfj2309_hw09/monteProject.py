import numpy as np

def estDuration(runs) :
    # put student code here

########################  main  ########################
if __name__ == "__main__" :
    runs = 1000

    minDays, maxDays, avg = estDuration(runs)

    print("min = %d, max = %d, average = %.1f" % (minDays, maxDays, avg))

