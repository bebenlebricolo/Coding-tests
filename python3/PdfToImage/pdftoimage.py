from pathlib import Path
import fitz
from PIL import Image

# Code partially taken from
# https://pymupdf.readthedocs.io/en/latest/tutorial.html#rendering-a-page
# https://pymupdf.readthedocs.io/en/latest/module.html
# https://stackoverflow.com/questions/53695675/how-to-render-a-pypdf-pageobject-page-to-a-pil-image-in-python
def main() :
    this_dir = Path(__file__).parent
    filename = "test.pdf"  # name of pdf file you want to render
    cache_directory = this_dir.joinpath(".cache")
    if not cache_directory.exists() :
        cache_directory.mkdir(parents=True)


    #render with PyMuPDF
    doc = fitz.Document(this_dir.joinpath(filename))
    page = doc.load_page(0)
    pix = page.get_pixmap()

    #convert to a PIL image
    mode = "RGBA" if pix.alpha else "RGB"
    img = Image.frombytes(mode, (pix.width, pix.height), pix.samples)
    img.save(cache_directory.joinpath("image.png"), format="PNG")


if __name__ == "__main__" :
    main()
