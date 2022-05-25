# Binary | Ticket Storage

## Info

> This is a completely secure ticket reservation service!
>
> Change my mind!
>
> `nc <ip> <port>` 
>
> flag in /tmp/flag.txt

## Run

Give participants a zip-archive from deploy/static and ip:port of service

## Short description

> ELF 64bit, dynamic linked, no-pie, NX+, Canary+

## Solution

> 1. You need to create 7 tickets to initialize the cache.
>
> 2. The first cache entry can be rewritten by reading the username
> 
> 3. By rewriting it to an address in .bss, you can read the address on the heap where the ticket is located from the file /tmp/flag.txt
>
> 4. After that, you can read the ticket id and see the ticket by id
> 

[solution script](solve/exploit.py)

## Flag

`Aero{4af2aea9b7dea9aabbc1c9a423e4957fd4c615821f4ded0f618b629651a9d67c}`
