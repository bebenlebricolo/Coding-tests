from array import array
import math
import sys
import cv2
import numpy as np
from matplotlib import pyplot as plt
from pathlib import Path

from skimage import measure
from skimage.draw import polygon
import scipy.ndimage as ndimage

from PIL import Image


def draw_contours_1(img : cv2.Mat, gray : cv2.Mat, output_filepath : Path, show_fig = True) :
    # setting threshold of gray image
    # Selecting subpart of the image, that more or less matches the zone where data is being located
    height = len(gray)
    width = len(gray[0])

    _, threshold = cv2.threshold(gray, 195, 200, cv2.THRESH_BINARY)
    contours, hierarchy = cv2.findContours(threshold, cv2.RETR_LIST, cv2.CHAIN_APPROX_NONE)
    contours_image : np.ndarray = np.zeros((height, width , 3), dtype=np.uint8)

    # list for storing names of shapes
    cv2.drawContours(image=contours_image, contours=contours, contourIdx=-1, color=(255, 255, 255), thickness=1)

    #Displaying the image after drawing contours
    fig = plt.figure()
    fig.add_subplot(1, 4 , 1)

    plt.imshow(threshold)
    fig.add_subplot(1, 4 , 2)

    plt.imshow(contours_image)

    #print(type(contours_image))
    #print(contours_image.dtype)
    #print(contours_image.shape)

    contours1_to_gray = cv2.cvtColor(contours_image, cv2.COLOR_RGB2GRAY)
    contours_2, _ = cv2.findContours(contours1_to_gray, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
    contours_image_2 = np.zeros((height, width , 3), np.uint8)
    cv2.drawContours(image=contours_image_2, contours=contours_2, contourIdx=-1, color=(255, 255, 255), thickness=1)
    fig.add_subplot(1, 4 , 3)

    plt.imshow(contours_image_2)

    fig.add_subplot(1,4,4)
    plt.imshow(gray)

    if show_fig :
        plt.show()

    # Save figure to disk
    fig.savefig(output_filepath.as_posix(), dpi=300)



def draw_contours_2(img : cv2.Mat, gray : cv2.Mat) :
    # perform edge detection
    edges = cv2.Canny(gray, 127, 250)

    # detect lines in the image using hough lines technique
    lines = cv2.HoughLinesP(edges, 1, np.pi/180, 60, np.array([]), 50, 5)

    # iterate over the output lines and draw them
    for line in lines:
        for x1, y1, x2, y2 in line:
            cv2.line(img, (x1, y1), (x2, y2), (20, 220, 20), 3)

    # show the image
    plt.imshow(img)
    plt.show()

    pass


def compute_perimeter(data : array) -> float:
    perimeter = 0.0
    for i in range(0,len(data)):
        if i == len(data) - 1 :
            pass
        # Should wrap back to 0 when i == len(data), so that we also compute the distance between the first and last item
        next = (i + 1) % (len(data))
        distance = math.sqrt(math.pow(data[i][0] - data[next][0], 2) + math.pow(data[i][1] - data[next][1], 2))
        perimeter += distance

    return perimeter

def _find_min_max(value : float, boundaries : list[float]) -> list[float] :
    if value < boundaries[0] :
        boundaries[0] = value
    if value > boundaries[1] :
        boundaries[1] = value
    return boundaries

def compute_aspect_ratio(contour : array) -> float :
    x_boundaries = [0.0, 0.0]
    y_boundaries = [0.0, 0.0]

    for point in contour :
        x_boundaries = _find_min_max(point[0], x_boundaries)
        y_boundaries = _find_min_max(point[1], y_boundaries)

    aspect_ratio = (x_boundaries[1] - x_boundaries[0]) / (y_boundaries[1] - y_boundaries[0])
    return aspect_ratio

def scikit_find_biggest_contour(gray : cv2.Mat) -> tuple[float, float, np.ndarray]:
     # Find contours at a constant value of 0.8
    contours : array = measure.find_contours(gray, 190)

    # Contours shaping / datastructure :
    # unique contour = list[2D arrays] -> list of x,y points in image space where [x, y] are stored in a 2d array
    # array of contours : list[contour] -> list[list[2D array]]
    # -> Points are very probably listed in direct order (order in which their linking constructs a non-crossing contour)
    # Api reference : https://scikit-image.org/docs/stable/api/skimage.measure.html#skimage.measure.find_contours
    perimeter_contour_map = []
    for contour in contours:
        #ax.plot(contour[:, 1], contour[:, 0], linewidth=2)
        perimeter = compute_perimeter(contour)
        perimeter_contour_map.append([perimeter, contour])

    # Sort decreasing, biggest perimeter first
    perimeter_contour_map.sort(key = lambda x : x[0], reverse=True)

    biggest_contour = perimeter_contour_map[0][1]

    # Save figure to disk
    perimeter = perimeter_contour_map[0][0]
    aspect_ratio = compute_aspect_ratio(biggest_contour)
    return (perimeter, aspect_ratio, biggest_contour)

# Using scikit image
def draw_contours_3(contour : np.ndarray, gray : cv2.Mat, output_filepath : Path, show_fig = True) :
    # Display the image and plot all contours found
    fig, ax = plt.subplots()
    ax.imshow(gray, cmap = 'gray')

    # Contours shaping / datastructure :
    # unique contour = list[2D arrays] -> list of x,y points in image space where [x, y] are stored in a 2d array
    # array of contours : list[contour] -> list[list[2D array]]
    # -> Points are very probably listed in direct order (order in which their linking constructs a non-crossing contour)
    # Api reference : https://scikit-image.org/docs/stable/api/skimage.measure.html#skimage.measure.find_contours

    ax.axis('image')
    ax.plot(contour[:, 1], contour[:, 0], linewidth=2)
    ax.set_xticks([])
    ax.set_yticks([])

    if show_fig :
        plt.show()

    # Save figure to disk
    fig.savefig(output_filepath.as_posix(), dpi=300)

def extract_image(img : cv2.Mat, contour : np.ndarray, output_filepath : Path) :

    # Fill in the hole created by the contour boundary
    height = len(img)
    width = len(img[0])

    # Heavily inspired from http://tonysyu.github.io/scikit-image/auto_examples/plot_shapes.html
    transparent = np.zeros((height, width, 4), dtype=np.uint8)
    rr, cc = polygon(contour[:,0], contour[:,1], img.shape )
    rgb_img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    transparent[rr, cc, 0:3] = rgb_img[rr, cc, 0:3]
    transparent[rr,cc,3] = 255

    output_image = Image.fromarray(transparent, mode="RGBA")
    output_image.save(output_filepath)

def _ensure_folder_exist(folder_path : Path) :
    if not folder_path.exists():
        folder_path.mkdir(parents=True)

def main(args) -> int :
    script_dir = Path(__file__).parent
    test_images_dir = script_dir.joinpath("TestImages")
    opencv_contouring_output_folder = script_dir.joinpath("Produced/OpenCVContouring")
    scikit_contouring_output_folder = script_dir.joinpath("Produced/ScikitContouring")
    extracted_images_folder = script_dir.joinpath("Produced/ExtractedImages")

    # Ensure output folders are there
    _ensure_folder_exist(opencv_contouring_output_folder)
    _ensure_folder_exist(scikit_contouring_output_folder)
    _ensure_folder_exist(extracted_images_folder)

    can_image_path = test_images_dir.joinpath("can.png")
    bottle_image_path = test_images_dir.joinpath("bottle.png")
    keg_image_path = test_images_dir.joinpath("keg.png")

    images_path = [
        can_image_path,
        bottle_image_path,
        keg_image_path
    ]

    for image in images_path :
        if not image.exists() :
            print("Could not find input image at pointed disk node : {}".format(image))
            return -1


        img = cv2.imread(image.as_posix())
        gray = cv2.cvtColor(img, cv2.COLOR_RGB2GRAY)

        # Try with basic pixel thre
        scikit_img_filepath = scikit_contouring_output_folder.joinpath(image.name)
        opencv_img_filepath = opencv_contouring_output_folder.joinpath(image.name)
        [perimeter, aspect_ratio,contour] = scikit_find_biggest_contour(gray)

        print("Extracted contour for image \"{}\" with perimeter : {} and aspect ratio : {}".format(image.name, perimeter, aspect_ratio))
        draw_contours_3(contour, gray, output_filepath=scikit_img_filepath, show_fig=False)
        extract_image(img, contour, extracted_images_folder.joinpath(image.name))

    return 0

if __name__ == "__main__" :
    exit(main(sys.argv[1:]))
