from pathlib import Path
import fitz
from PIL import Image

# Code partially taken from
# https://pymupdf.readthedocs.io/en/latest/tutorial.html#rendering-a-page
# https://pymupdf.readthedocs.io/en/latest/module.html
# https://stackoverflow.com/questions/53695675/how-to-render-a-pypdf-pageobject-page-to-a-pil-image-in-python

filename = "test.pdf"  # name of pdf file you want to render
n = 0  # n is the page number
this_dir = Path(__file__).parent

#render with PyMuPDF
doc = fitz.Document(this_dir.joinpath(filename))
page = doc.load_page(n)
pix = page.get_pixmap()

#convert to a PIL image
mode = "RGBA" if pix.alpha else "RGB"
img = Image.frombytes(mode, [pix.width, pix.height], pix.samples)
img.show()


