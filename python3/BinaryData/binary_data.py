from pathlib import Path
import struct
import os

class Pixel :
    x : int
    y : int
    z : int
    val : float

    def __init__(self, x, y, z, val) -> None:
        self.x = x
        self.y = y
        self.z = z
        self.val = val

    def __eq__(self, __o) -> bool:
        ret = True
        ret &= __o.x == self.x
        ret &= __o.y == self.y
        ret &= __o.z == self.z
        ret &= __o.val == self.val
        return ret

    def from_binary(self, path : Path) :
        with open(path, "rb") as file :
            buffer = file.read(self.get_binary_length())
            self.from_bytes(buffer)

    def to_binary(self, path : Path) :
        with open(path, "wb") as file :
            file.write(self.to_bytes())

    @staticmethod
    def get_binary_length() -> int :
        return 3 + 8

    def to_bytes(self) -> bytes :
        out = bytes()
        out += self.x.to_bytes(1, byteorder="big")
        out += self.y.to_bytes(1, byteorder="big")
        out += self.z.to_bytes(1, byteorder="big")
        out += struct.pack("d", self.val)
        return out

    def from_bytes(self, buffer : bytes) :
        self.x = buffer[0]
        self.y = buffer[1]
        self.z = buffer[2]
        self.val = struct.unpack("d", buffer[3:])[0]

class Image :
    pixels : list[Pixel]

    def __init__(self) -> None:
        self.pixels = []

    def to_binary(self, path : Path) :
        with open(path, "wb") as file :
            for pixel in self.pixels :
                file.write(pixel.to_bytes())

    def from_binary(self, path : Path) :
        with open(path, "rb") as file :
            buffer =  file.read(Pixel.get_binary_length())
            while buffer :
                pixel = Pixel(0,0,0,0.0)
                pixel.from_bytes(buffer)
                self.pixels.append(pixel)
                buffer =  file.read(Pixel.get_binary_length())

    def from_xyz(self, path : Path) :
        with open(path, "r") as file :
            file.readline()
            for line in file.readlines() :
                trimmed = line.split(' ')
                pixel = Pixel(0,0,0,0.0)
                pixel.x = int(trimmed[0])
                pixel.y = int(trimmed[1])
                pixel.z = int(trimmed[2])
                pixel.val = float(trimmed[3].strip('\n'))
                self.pixels.append(pixel)

def generate_image() -> Image :
    image = Image()
    for i in range(128) :
        for j in range(128) :
            for k in range(128) :
                pixel = Pixel(i,j,k, 453.256)
                image.pixels.append(pixel)
    return image

def main() :

    script_directory = Path(os.path.dirname(os.path.realpath(__file__)))
    test_pixel_filepath = script_directory.joinpath("test_bin")

    print("Generating single pixel ...")
    pixel = Pixel(255,127,3, 0.2)
    pixel.to_binary(test_pixel_filepath)
    print("Done generating pixel")

    print("Reading back pixel ...")
    parsed_pixel = Pixel(0,0,0,0.0)
    parsed_pixel.from_binary(test_pixel_filepath)
    print("Done reading back pixel")

    assert(pixel == parsed_pixel)

    print("Generating image ...")
    image = generate_image()
    print("Done generating image")

    test_image_filepath = Path("test_image.bin")
    print("Writing image down ...")
    image.to_binary(Path("test_image.bin"))
    print("Done writing image")

    new_image = Image()
    print("Reading image back")
    new_image.from_binary(test_image_filepath)
    print("Done reading image back")

    # Comparing serialization symmetry
    assert(image.pixels[123] == new_image.pixels[123])

if __name__ == "__main__" :
    exit(main())