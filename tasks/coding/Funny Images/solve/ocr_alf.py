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


def save_symbol(io_buf):

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
    rnd = randint(1000000, 9999999)
    for i in range(len(img_num_p)):
        matplotlib.image.imsave(os.path.join("tmp", f"out_{rnd}_{i}.png"), img_num_p[i])
    print(f"===========Save symbol {time.time() - start}")
    return text
