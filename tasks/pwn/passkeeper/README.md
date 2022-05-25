# Binary | Password Keeper

## Info

> You can save all your passwords here. 
>
> It's safe, probably.
>
> `nc <ip> <port>` 
>
> flag in /tmp/flag.txt

## Run

Give participants a zip-archive from deploy/static and ip:port of service

## Short description

> ELF 64bit, dynamic linked, no-pie, NX+, Canary+

## Solution

> 1. You can use off-by-one to leak libc
>
> 2. After leak you can use house-of-spirit attack to spawn chunk in .bss section 
> 
> 3. In .bss you can rewrite print_function to system and call it with "/bin/sh"
> 

[solution script](solve/exploit.py)

## Flag

`Aero{a9b57185b3799a0bb4c0bdd01156ae2d5eeea046513a4faf1d51e114df91679e}`
