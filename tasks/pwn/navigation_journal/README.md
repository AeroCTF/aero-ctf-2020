# Binary | Navigation Journal

## Info

> This system was created to simplify the work of dispatchers. 
>
> However, it does not work correctly. 
>
> Something is wrong with the files.
>
> `nc <ip> <port>` 
>
> flag in /tmp/flag.txt

## Run

Give participants a zip-archive from deploy/static and ip:port of service

## Short description

> ELF 32bit, dynamic linked, no-pie, NX+, Canary+

## Solution

> 1. Leak libc with FSB bug in new filename
>
> 2. Rewrite pointer to main-journal
> 
> 3. Create a valid fake object of struct FILE and rewrite vtable offset to redefine pointer to fclose
> 
> 4. Rewrite fclose to system and close main journal with arg "/bin/sh"
>

[solution script](solve/exploit.py)

## Flag

`Aero{e9b132dd85f0c1be26c01ab22e2e7d545dff7d52dbda745fe3dd5796bea14153}`
