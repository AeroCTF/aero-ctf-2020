# Binary | Plane Market

## Info

> How about selling a few airplanes?
> 
> We have a simple service for this.
>  
> `nc <ip> <port>` 
>
> flag in /tmp/flag.txt

## Run

Give participants a zip-archive from deploy/static and ip:port of service

## Short description

> ELF 64bit, dynamic linked, no-pie, NX+

## Solution

> 1. You can get an address leak using your username
>
> 2. After that you can tcache poisoning and rewrite RA
> 
> 3. With ROP you can get leak libc and make final ROP using one_gadget
>

[solution script](solve/exploit.py)

## Flag

`Aero{13f96a24f185f0862ea1ecd88c854b12d5a4b7ba85b43dc42e0bb2d187a2ef9b}`
