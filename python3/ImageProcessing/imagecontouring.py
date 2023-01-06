import sys
import cv2
import numpy as np
from matplotlib import pyplot as plt
from pathlib import Path


def draw_contours_1(img : cv2.Mat, gray : cv2.Mat) :
    # setting threshold of gray image
    # Selecting subpart of the image, that more or less matches the zone where data is being located
    height = len(gray)
    width = len(gray[0])

    _, threshold = cv2.threshold(gray, 195, 200, cv2.THRESH_BINARY)
    contours, hierarchy = cv2.findContours(threshold, cv2.RETR_LIST, cv2.CHAIN_APPROX_NONE)
    blank_image = np.zeros((height, width , 3), np.uint8)

    # list for storing names of shapes
    cv2.drawContours(image=blank_image, contours=contours, contourIdx=-1, color=(255, 255, 255), thickness=1)

    #Displaying the image after drawing contours
    fig = plt.figure()
    fig.add_subplot(1, 3 , 1)
    plt.imshow(threshold)
    fig.add_subplot(1, 3 , 2)
    plt.imshow(blank_image)

    # iterate over the output lines and draw them
    # for line in edges:
    #     for x1, y1, x2, y2 in line:
    #         cv2.line(blank_image_2, (x1, y1), (x2, y2), (20, 220, 20), 3)

    fig.add_subplot(1,3,3)
    plt.imshow(gray)

    plt.show()

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


def main(args) -> int :
    script_dir = Path(__file__).parent
    test_images_dir = script_dir.joinpath("TestImages")

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
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

        # Try with basic pixel threshold
        draw_contours_1(img, gray)

    return 0

if __name__ == "__main__" :
    exit(main(sys.argv[1:]))
