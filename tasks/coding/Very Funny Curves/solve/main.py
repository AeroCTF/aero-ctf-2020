#!/usr/bin/env python3

from pwn import *
import numpy as np
from PIL import Image
from scipy import misc
import numexpr
import matplotlib.pyplot as plt
import matplotlib
from os import listdir
import os
import bz2
import base64
import sys
import time
from numba import njit, prange, uint8, uint64, int64
from numba.types.containers import List as listt
import io

alph_base = []
alph_base_np = []

for img_src in listdir('alph'):

    baseh = 100
    img = Image.open(os.path.join('alph', img_src))
    wpercent = (baseh/float(img.size[1]))
    wsize = int((float(img.size[0])*float(wpercent)))
    img = img.resize((100, 100), Image.ANTIALIAS)

    im = np.array(img)
    tmp = im[:, :, 1]
    tmp = np.where(tmp < 200, 1, 0)

    alph_base.append(img_src[:-4])
    alph_base_np.append(tmp)


def ocr(inp):
    baseh = 100
    img = Image.fromarray(inp)
    wpercent = (baseh/float(img.size[1]))
    wsize = int((float(img.size[0])*float(wpercent)))
    img = img.resize((100, 100), Image.ANTIALIAS)

    im = np.array(img)[:, :, 1]
    im = np.where(im < 200, 1, 0)
    tmp = []

    for x in alph_base_np:

        b1 = im.copy()
        b2 = x.copy()
        (q, w) = b1.shape
        alll = q*w
        tmp.append(np.equal(b1, b2).sum()/alll)

    rr = np.argmax(np.array(tmp))
    return(alph_base[rr])


@njit(listt(uint8)(int64, uint8[:, :, :]))
def p_colum_min(w, im_p):
    colum_min = []
    for ncolum in prange(w):
        colum_min.append(im_p[:, ncolum, 1].min())
    return colum_min


@njit(listt(uint8)(int64, uint8[:, :]))
def p_row_min(w, im_p):
    row_min = []
    for nrow in prange(w):
        row_min.append(im_p[nrow, :].min())
    return row_min


@njit(listt(uint8[:, :, :])(uint8[:, :, :], int64[:], int64[:], int64, int64))
def crop_height(im_p, colum_list_max, colum_list_min, n, h):
    crop = []
    for ncolum in prange(n):
        x_max = colum_list_max[ncolum]
        x_min = colum_list_min[ncolum]
        tmp = im_p[:, x_min:x_max, 1]
        row_min = p_row_min(h, tmp)

        y_min = 0
        y_max = h-1

        for nrow in prange(h):
            if row_min[nrow] < 200:
                y_min = nrow
                break

        for nrows in prange(h-1, 0, -1):
            if row_min[nrows] < 200:
                y_max = nrows
                break

        crop.append(im_p[y_min:y_max, x_min:x_max, :])

    return crop


@njit(listt(uint8[:, :, :])(uint8[:, :, :]))
def img_split(im_p):

    (h, w, _) = im_p.shape

    f = False

    x_min = 0
    x_max = 0

    colum_min = p_colum_min(w, im_p)

    colum_list_max = []
    colum_list_min = []

    for ncolum in prange(w):
        if colum_min[ncolum] > 200:
            if f:
                f = False
                x_max = ncolum
                colum_list_min.append(x_min)
                colum_list_max.append(x_max)
        else:
            if f == False:
                f = True
                x_min = ncolum

    img_num = crop_height(im_p, np.array(colum_list_max),
                          np.array(colum_list_min), len(colum_list_min), h)
    return img_num


def main(host: str, port: int):
    t = np.linspace(0, 1, 10)
    while 1:
        r = remote(host, port)
        correct: int = 0

        buf = r.recvline()
        print(buf)
        buf = r.recv(12)
        # print(buf)

        r.send("Y\n")
        f_ = True
        while f_:
            start = time.time()
            plt.clf
            formuls: list = []
            plots: list = []

            buf = r.recvline().strip().decode("utf-8")
            if "Aero" in buf:
                print(buf)
                sys.exit(-1)

            if "Incor" in buf:
                print("incor")
                f_ = False
                sys.exit(-2)
                break
            r.recv(22)
            #buf = buf.strip().decode("utf-8")
            # print(buf)

            buf = bz2.decompress(base64.b85decode(buf)).strip().decode("utf-8")
            # print(buf)

            buf = buf.replace("{", "").replace("}", "").replace("^", "**")
            buf = buf.split('\n')[1:]
            for x in buf:
                formuls.append(x[8:-1].split("; "))
            print(f"===========start {time.time() - start}")
            start = time.time()

            plt.clf()
            pminx = []
            pmaxx = []
            pminy = []
            pmaxy = []
            for formul in formuls:
                #x = numexpr.evaluate(formul[0]+"+0*t")
                #y = numexpr.evaluate(formul[1]+"+0*t")
                x = eval(f"{formul[0]}+0*t")
                pminx.append(x.min())
                pmaxx.append(x.max())
                y = eval(f"{formul[1]}+0*t")
                pminy.append(y.min())
                pmaxy.append(y.max())
                plt.plot(x, y, 'black')

            minx = np.array(pminx).min()
            maxx = np.array(pmaxx).max()
            miny = np.array(pminy).min()
            maxy = np.array(pmaxy).max()

            pwidth = maxx-minx
            pheight = maxy-miny

            print(f"===========Calculete {time.time() - start}")

            plt.gca().set_aspect('equal', adjustable='box')
            plt.gca().invert_yaxis()
            plt.axis('off')

            start = time.time()
            io_buf = io.BytesIO()
            plt.savefig(io_buf, bbox_inches='tight', dpi=int(
                20*pwidth/pheight), orientation='portrait', pad_inches=0)
            plt.clf

            print(f"===========Save {time.time() - start}")
            start = time.time()

            img = Image.open(io_buf)
            # img.save("inn.png")
            im = np.array(img)
            img.close()

            print(f"=========== open {time.time() - start}")
            start = time.time()
            img_num_p = img_split(im)
            print(f"===========Crop {time.time() - start}")

            start = time.time()
            text = ""
            # print(len(img_num_p))
            for iii in img_num_p:
                text += ocr(iii)
            print(f"===========OCR {time.time() - start}")
            start = time.time()
            try:
                rrr = int(eval(text.replace("^", "**").replace("⁄", "/")))
                print(f"=={correct}\t{text}={rrr}")
                r.send(f'{rrr}\n')
            except:
                txt = text.replace("^", "**").replace('⁄', '/')
                print(f"ERROR {txt}")
                sys.exit(0)
                break
            print(f"===========END {time.time() - start}")

            correct += 1

        if correct > 50:
            print(correct)

        r.close()


if __name__ == "__main__":

    if len(sys.argv) > 2:
        host = sys.argv[1]
        port = int(sys.argv[2])
    else:
        print("Usage: python " + sys.argv[0] + " <host> <port>")
        sys.exit(-1)

    main(host, port)
