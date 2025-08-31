"""
There are 86 classes therefore the labels csv must have 86 columns. 
"""

NUM_CLASSES = 86


import numpy as np


if __name__ == "__main__":
    labels = np.loadtxt("/home/vidhipatel/starry/data/idOnly.csv", dtype=int)
    cl = np.zeros((labels.size, NUM_CLASSES))
    cl[np.arange(labels.size), labels-1] = 1
    np.savetxt("/home/vidhipatel/starry/data/IDlabels.csv", cl, fmt="%d", delimiter=',')