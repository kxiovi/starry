"""
Convert jpg image folder to csv i.e. vectorize the images
Reference: 
    https://stackoverflow.com/questions/67810179/how-to-convert-the-data-of-all-images-in-a-folder-into-a-csv-file
"""

import os
from PIL import Image
import numpy as np
from numpy import savetxt

def walk_files(dir):
    """
    Walk the files in the image folder and return as list.
    """

    files = []
    for root, dir_name, fname in os.walk(dir):
        for name in fname:
            full_name = os.path.join(root, name)  # dir_name is included in root
            files.append(full_name)
    return files

if __name__ == "__main__":
    image_folder_list = walk_files("/home/vidhipatel/starry/data/image_constellation/stars")
    pixels = []
    for f in image_folder_list:
        im = Image.open(f)
        im = im.resize((28, 28))  # all img need to be the same size
        arr = np.asarray(im) / 255  # normalize
        pixels.append(arr.flatten())  # need 1D arr
        # break
    pixels_arr = np.asarray(pixels)
    print((pixels_arr.shape))
    np.savetxt("img.csv", pixels_arr, delimiter=',', fmt="%.6f")
        
