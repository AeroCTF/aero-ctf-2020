import requests
import sys
import os

try:
    from PIL import Image, ImageDraw
except ImportError:
    import Image
    import ImageDraw

font_path = "./font"

if __name__ == "__main__":

    if len(sys.argv) > 2:
        hostt = sys.argv[1]
        port = int(sys.argv[2])
    else:
        print("Usage: python " + sys.argv[0] + " <host> <port>")
        sys.exit(-1)

    os.makedirs(font_path, exist_ok=True)

    host = "http://"+hostt+":"+str(port)
    session = requests.Session()
    f = True
    apix: dict = {}
    for i in range(100):
        rec = session.get(host + "/gen.php", allow_redirects=True)
        open('tmp.png', 'wb').write(rec.content)
        image = Image.open("tmp.png")
        pix = image.load()

        if not (f'{pix[0, 0][0]}_{pix[0, 0][1]}_{pix[0, 0][2]}' in apix):
            apix[f'{pix[0, 0][0]}_{pix[0, 0][1]}_{pix[0, 0][2]}'] = []
        apix[f'{pix[0, 0][0]}_{pix[0, 0][1]}_{pix[0, 0][2]}'].append(pix)

    width = image.size[0]
    height = image.size[1]
    draw = ImageDraw.Draw(image)

    for k in apix:
        arrpix = apix[k]
        print(f'{k} {len(apix[k])}')
        for i in range(width):
            for j in range(height):
                r = [e[i, j][0] for e in arrpix]
                r = max(r, key=r.count)

                g = [e[i, j][1] for e in arrpix]
                g = max(g, key=g.count)

                b = [e[i, j][2] for e in arrpix]
                b = max(b, key=b.count)

                draw.point((i, j), (r, g, b))
        image.save(os.path.join(font_path, f"{k}.png"), "PNG")
    del draw
