import numpy as np
import open3d as o3d
import os
import sys
import random

def map_to_float(value : float, rangeIn : list[int], rangeOut : list[float]) -> float :
    ret = (rangeIn[1] - value) / (rangeIn[1] - rangeIn[0]) * (rangeOut[1] - rangeOut[0]) + rangeOut[0]
    return ret

class RgbColor :
    red : float
    green : float
    blue : float
    def __init__(self, r : float = 1, g : float = 1, b : float = 1) -> None:
        self.red = r
        self.green = g
        self.blue = b

    def pick_random(self) -> None :
        self.red = map_to_float(random.randint(0,255), [0,255], [0,1])
        self.green = map_to_float(random.randint(0,255), [0,255], [0,1])
        self.blue = map_to_float(random.randint(0,255), [0,255], [0,1])


if __name__ == "__main__":

    print("Displaying pointsets recursively")

    point_clouds = []
    surfaces = []
    for path, _, files in os.walk(sys.argv[1]):
        for name in files:
            file = os.path.join(path, name)
            if file.endswith(".xyz") :
                print("Found XYZ file : {}".format(file))
                point_clouds.append(o3d.io.read_point_cloud(file))
                continue
            if file.endswith(".obj") :
                print("Found OBJ file : {}".format(file))
                surfaces.append(o3d.io.read_triangle_mesh(file))



    geometries = point_clouds + surfaces
    for mesh in surfaces :
        color = RgbColor()
        color.pick_random()
        mesh.compute_vertex_normals()
        mesh.paint_uniform_color([color.red, color.green, color.blue])

    for pointset in point_clouds :
        color = RgbColor()
        color.pick_random()
        pointset.paint_uniform_color([color.red, color.green, color.blue])

    o3d.visualization.draw_geometries(geometries, mesh_show_back_face=True)