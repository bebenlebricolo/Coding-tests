from binary_data import Image, Pixel
from pathlib import Path
import sys
import time

def main(fpath : Path) :
    image = Image()
    time_before = time.perf_counter()
    image.from_xyz(fpath)
    time_after = time.perf_counter()
    print("Time for parsing xyz : {:0.4f} seconds".format(time_after - time_before))

    time_before = time.perf_counter()
    image.to_binary(fpath.parent.joinpath("converted.bin"))
    time_after = time.perf_counter()
    print("Time for writing binary : {:0.4f} seconds".format(time_after - time_before))

    time_before = time.perf_counter()
    image.pixels.clear()
    image.from_binary(fpath.parent.joinpath("converted.bin"))
    time_after = time.perf_counter()
    print("Time for parsing binary : {:0.4f} seconds".format(time_after - time_before))

if __name__ == "__main__" :
    exit(main(Path(sys.argv[1])))