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
from PIL import Image, ImageFont, ImageDraw


@njit(uint8[:](int16))
def colormap(n):
    out = np.zeros((3), dtype=uint8)
    if n >= 0 and n < 256:
        out[:] = np.array([255-(n % 256), 0, 255], dtype=uint8)
    elif n >= 256 and n < 512:
        out[:] = np.array([0, n % 256, 255], dtype=uint8)
    elif n >= 512 and n < 768:
        out[:] = np.array([0, 255, 255-(n % 256)], dtype=uint8)
    elif n >= 768 and n < 1024:
        out[:] = np.array([n % 256, 255, 0], dtype=uint8)
    elif n >= 1024 and n < 1280:
        out[:] = np.array([255, 255-(n % 256), 0], dtype=uint8)
    else:
        out[:] = np.array([0, 0, 0], dtype=uint8)
    return out


@njit(uint8[:, :, :](int16[:, :]), parallel=True)
def get_colormap(inn):
    (x, y) = inn.shape
    out = np.zeros((y, x, 3), dtype=uint8)
    for x_ in prange(x):
        for y_ in prange(y):
            out[y-1-y_, x_, :] = colormap(inn[x_, y_])
    return out


start = time.time()
samplerate, data_ = scipy.io.wavfile.read("in6.wav")
res = np.array([])
rea = np.array([])
ref = []
rep = []
w = 1080
print(f"===========Open {time.time() - start}")

start = time.time()
for i in range(samplerate*0, samplerate*193, w*2):
    data = data_[i:i+w*2, 0]

    spectrum = np.fft.rfft(data)
    magnitude = spectrum.real
    phase = spectrum.imag

    ref.append(magnitude)
    rep.append(phase)
print(f"===========FFT {time.time() - start}")
start = time.time()
bit = 1280-1

res = np.array(ref)
rea = np.array(rep)
res = np.cbrt(np.cbrt(res))
rea = np.cbrt(np.cbrt(rea))


min_ = res.min()
max_ = res.max()
res = (res-min_)/(max_-min_) * bit

minp_ = rea.min()
maxp_ = rea.max()
rea = (rea-minp_)/(maxp_-minp_) * bit

res = np.int16(res)
rea = np.int16(rea)
print(f"===========Calc {time.time() - start}")
start = time.time()
#(x,y) = res.shape
#imgf = [ [ colormap(res[x_, y_]) for x_ in range(x) ] for y_ in range(y)]
imgf = get_colormap(res)

#(x,y) = rea.shape
#imgp = [ [ colormap(rea[x_, y_]) for x_ in range(x) ] for y_ in range(y)]
imgp = get_colormap(rea)

# print(imgf.max())
print(f"===========Color {time.time() - start}")

start = time.time()
matplotlib.image.imsave("imga.png", imgf)
matplotlib.image.imsave("imgp.png", imgp)
print(f"===========Save {time.time() - start}")

start = time.time()
fnt = ImageFont.truetype('arial.ttf', 30)

tmp = np.int16(np.array([[x for _ in range(20)] for x in range(1280)]))
matplotlib.image.imsave("map.png", get_colormap(tmp))

mapc = Image.open('map.png')
imgm = Image.new('RGB', (1920, 500), color=(255, 255, 255))
x = int((1920-1280)/2)
y = 100
d = ImageDraw.Draw(imgm)
d.text((900, 10), "imga.png   (rfft().real)**(1/9)", font=fnt, fill=(0, 0, 0))
imgm.paste(mapc, (x, y), mask=mapc)
d.text((x, 150), f"min = {min_}", font=fnt, fill=(255, 0, 255))
d.text((x+800, 150), f"max = {max_}", font=fnt, fill=(255, 0, 0))

d.text((900, 250), "imgp.png   (rfft().imag)**(1/9)", font=fnt, fill=(0, 0, 0))
y = 300
imgm.paste(mapc, (x, y), mask=mapc)
d.text((x, 350), f"min = {minp_}", font=fnt, fill=(255, 0, 255))
d.text((x+800, 350), f"max = {maxp_}", font=fnt, fill=(255, 0, 0))

d.text((x, 400), f"sampling frequency {samplerate}Hz", font=fnt, fill=(0, 0, 0))
imgm.save("map_seckrum.png")

print(f"===========Other {time.time() - start}")


'''
start = time.time()
res = res*(max_-min_)/bit + min_
res = np.power(res, 9)
rea = rea*(maxp_-minp_)/bit + minp_
rea = np.power(rea, 9)
#res = res/samplerate
(x,y) = res.shape
ress = np.array([])
for i in range(x):
    s = np.fft.irfft(np.vectorize(complex)(res[i,:], rea[i,:]))
    ress = np.concatenate((ress,s))

#ress = -ress/samplerate

ress = np.int16(ress)
scipy.io.wavfile.write("out.wav", samplerate, ress)
print(f"===========Save WAV {time.time() - start}")

'''
