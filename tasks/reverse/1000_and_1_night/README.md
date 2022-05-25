# Binary | 1000 and 1 nigth

## Info

> I wrote all this manually in 1000 and 1 night. 
>
> It seems that the solution will take the same amount of time.
>
> After connecting to the server, it will ask you for a token for a binary. 
> 
> You need to enter the correct tokens for the requested files and you will receive a flag.
>
> `nc <ip> <port>`

## Run

Give participants a zip-archive from static/ and ip:port of service

## Short description

> 1001 ELF 64bit files with very simple xor-add-sub algo

## Solution

> 1. Check algo is very simple ((char+N)^K)-L))
>
> 2. In binary, you can find result string (in check function)
>
> 3. You need to automate the processing of each binary file.
> 
> 4. You can use objdump to get disassemble listing and parse it.
>
> 5. On server you need answer a 100 requests.

[solution script](solve/solver.py)
 
## Flag

`Aero{0f9e7ddd2be70f58b86f8f6589e17f182fc21c71437c2d9923fefa7ae281712b}`
