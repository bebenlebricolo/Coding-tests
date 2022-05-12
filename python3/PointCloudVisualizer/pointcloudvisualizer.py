import numpy as np
import open3d as o3d
import os
import sys

if __name__ == "__main__":

    print("Displaying pointsets recursively")

    point_clouds = []
    for path, _, files in os.walk(sys.argv[1]):
        for name in files:
            file = os.path.join(path, name)
            if file.endswith(".xyz") :
                print("Found XYZ file : {}".format(file))
                point_clouds.append(o3d.io.read_point_cloud(file))

    if len(point_clouds) >= 1 :
        o3d.visualization.draw_geometries(point_clouds)
    else :
        print("No XYZ files found in targeted folder")