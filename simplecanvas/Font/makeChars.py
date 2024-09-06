import numpy as np
import matplotlib.pyplot as plt
import subprocess
import skimage.io
import os

for i in range(256):
    plt.clf()
    plt.scatter([-1, 1], [-1, 1]); plt.text(0, 0, chr(i)); 
    f = "{}.png".format(i)
    plt.savefig(f)
    subprocess.call(["convert", f, "-crop", "18x18+324+228", f])
    I = skimage.io.imread(f)
    I = I[:, np.sum(I, axis=0)/(255*I.shape[0]) < 1]
    if I.size > 0:
        skimage.io.imsave(f, I)
