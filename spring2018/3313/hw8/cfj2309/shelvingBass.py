import numpy as np
import matplotlib.pyplot as plt

#   setup
configFile = "shelvingConfig.txt"










#
#   effective main
#
config = open(configFile, "r")
args = config.read().split("\n")

infile = args[0]
gain = int(args[1])
cutoff = int(args[2])
