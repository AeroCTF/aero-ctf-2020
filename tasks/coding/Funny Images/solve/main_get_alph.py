import requests
import re
import os
import sys
import subprocess
from ocr_alf import save_symbol

try:
    from PIL import Image, ImageDraw
except ImportError:
    import Image
    import ImageDraw
import pytesseract

font_path = "./font"

if __name__ == "__main__":

    if len(sys.argv) > 2:
        hostt = sys.argv[1]
        port = int(sys.argv[2])
    else:
        print("Usage: python " + sys.argv[0] + " <host> <port>")
        sys.exit(-1)

    host = "http://"+hostt+":"+str(port)
    session = requests.Session()

    for _ in range(20):
        session.get(host + "/reg.php", allow_redirects=True)
        r = session.get(host + "/gen.php", allow_redirects=True)

        open('tmp.png', 'wb').write(r.content)
        image = Image.open("tmp.png")  # Открываем изображение.
        draw = ImageDraw.Draw(image)  # Создаем инструмент для рисования.
        width = image.size[0]  # Определяем ширину.
        height = image.size[1]  # Определяем высоту.
        pix = image.load()

        name_f = f'{pix[0, 0][0]}_{pix[0, 0][1]}_{pix[0, 0][2]}'
        # Открываем изображение.
        image_fon = Image.open(os.path.join(font_path, f"{name_f}.png"))
        pix_fon = image_fon.load()

        for i in range(width):
            for j in range(height):
                if pix[i, j][0] != pix_fon[i, j][0] or pix[i, j][1] != pix_fon[i, j][1] or pix[i, j][2] != pix_fon[i, j][2]:
                    a = 0
                else:
                    a = 255

                draw.point((i, j), (a, a, a))
        image.save("ans.png", "PNG")
        #image.save("ans.jpg", "JPEG")
        del draw

        save_symbol("ans.png")
