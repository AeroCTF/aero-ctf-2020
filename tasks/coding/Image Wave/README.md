# Code | Image Wave

## Info

> A friend of mine recently told me something about FFT. 
> 
> And the fact that you can restore the signal from the spectrum. 
> 
> Just recently, he threw off a few pictures. 
> 
> I don’t know what to do with this, help me!
>
> \*NOTE: Wrap the resulting value in the flag-format Aero{[0-9]\*}

## Run

Distribute files from deploy / static to participants

## Short description

> 3 pictures are given (imga.png - (rfft (x) .real) ** (1/9); imgp.png - (rfft (x) .imag) ** (1/9); map_seckrum.png - with color scale scale). It is necessary to fulfill irfft knowing the values of the real and imaginary parts of the spectrum.

## Solution

> 1. Read images into numpy arrays
>
> 2. We convert colors to the value 0..1279 (scale width).
>
> 3. Convert Scale to Values
>
> 4. Combine arrays into a complex number
>
> 5. execute irfft
>
> 6. save WAV

**[Solve sploit](solve/)**

## Flag

`Aero{44130800454087113922111421638436416130198703185043619684674310673384316}`
