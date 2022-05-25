#!/usr/bin/env python3

import numpy as np
import scipy.io.wavfile
from scipy import io as sio
import wave
import scipy
import matplotlib.pyplot as plt
import matplotlib
from numba import njit, prange, jit
from numba import njit, prange, uint8, uint64, int64, int16, float64
from numba.types.containers import List as listt
import time
from PIL import Image

min_ = -6.0746113944589
max_ = 5.992195705070817
minp_ = -6.044441747168795
maxp_ = 5.969421831281398

bit = 1279
samplerate = 44100


@njit
def uncolormap(inn):
    r = inn[0]
    g = inn[1]
    b = inn[2]
    if b == 255 and g == 0:
        return 255-(r % 256)
    elif r == 0 and b == 255:
        return 256+g
    elif r == 0 and g == 255:
        return 512 + (255-(b % 256))
    elif g == 255 and b == 0:
        return 768 + r
    elif r == 255 and b == 0:
        return 1024 + (255-(g % 256))
    else:
        return -1


@njit(int16[:, :](uint8[:, :, :]), parallel=True)
def un_colormap(inn):
    (x, y, z) = inn.shape
    out = np.zeros((y, x), dtype=int16)
    for x_ in prange(x):
        for y_ in prange(y):
            out[y_, x_] = uncolormap(inn[x-1-x_, y_])
    return out


def ifft(res, rea):
    (x, y) = res.shape
    #tmp = np.fft.irfft(np.vectorize(complex)(res[0,:], rea[0,:]))
    y_ = (y-1)*2  # len(tmp)
    out = np.zeros((x, y_), dtype='int16')

    ress = np.array([])
    for i in range(x):
        out[i, :] = np.array(np.fft.irfft(np.vectorize(
            complex)(res[i, :], rea[i, :])), dtype='int16')

    return out


if __name__ == '__main__':

    start = time.time()
    img = Image.open("imga.png")
    amp = np.array(img)
    img.close()

    img = Image.open("imgp.png")
    phs = np.array(img)
    img.close()
    print(f"===========Open img {time.time() - start}")

    start = time.time()
    res = un_colormap(amp)
    rea = un_colormap(phs)
    print(f"===========Un color {time.time() - start}")

    start = time.time()
    res = res*(max_-min_)/bit + min_
    res = np.power(res, 9)
    rea = rea*(maxp_-minp_)/bit + minp_
    rea = np.power(rea, 9)
    print(f"===========Calck {time.time() - start}")

    start = time.time()
    ress = ifft(res, rea)
    ress = np.concatenate((ress))
    print(f"===========ifft {time.time() - start}")

    start = time.time()
    ress = np.int16(ress)
    scipy.io.wavfile.write("out.wav", samplerate, ress)
    print(f"===========Save WAV {time.time() - start}")
