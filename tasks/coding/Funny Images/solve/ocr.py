#!/usr/bin/env python3

from pwn import *
import numpy as np
from PIL import Image
from os import listdir
import os
import sys
import time
from numba import njit, prange, uint8, int64
from numba.types.containers import List as listt
import matplotlib
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


def _ocr(io_buf):

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
    return text
