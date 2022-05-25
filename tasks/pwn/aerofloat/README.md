# Binary | Aerofloat

## Info

> Aerofloat is looking forward to your feedback on flights.
>
> You can leave feedback for any of the tickets you have.
>
> To do this, you need to use this service.
>
> `nc <ip> <port>` 
>
> flag in /tmp/flag.txt

## Run

Give participants a zip-archive from deploy/static and ip:port of service

## Short description

> ELF 64bit, dynamic linked, no-pie, NX+, No-canary

## Solution

> 1. Stack overflow with two-field sturct
>
> 2. The return address is rewritten with a floating-point number
> 
> 3. You need to get a leak using the 'puts' function
>
> 4. After that, you can use one_gadget
> 

[solution script](solve/exploit.py)

## Flag

`Aero{8c911e90f6ff8ecb6a333ebacfccd28b36d1f9b02386cc884b343f1f02da62e6}`
