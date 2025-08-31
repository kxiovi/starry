"""
Convert labels.txt to csv.
"""

import csv

txtf = "/home/vidhipatel/starry/data/image_constellation/constellation_names.txt"
# csvf = "/home/vidhipatel/starry/data/labels.csv"
csvf = "/home/vidhipatel/starry/data/idOnly.csv"

if __name__ == "__main__":
    with open(txtf, 'r') as inputf, open(csvf, 'w', newline="") as outputf:
        starwriter = csv.writer(outputf)
        for line in inputf:
            parts = line.strip().split(maxsplit=1)
            label_id, label_name = parts
            # starwriter.writerow([label_id, label_name])
            starwriter.writerow([label_id])
