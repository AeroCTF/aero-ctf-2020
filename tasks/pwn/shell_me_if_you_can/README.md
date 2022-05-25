# Binary | Shell Me If You Can

## Info

> Modern firewalls can detect popular shellcodes.
>
> Therefore, you can often find something like what you see in a binary file.
>
> Try to get a shell.
>
> nc ip port
>
> flag in /tmp/flag.txt

## Run

Give participants a binary from deploy static and ip:port of service
```
cd deploy
docker-compose -p shellme up --build -d # or ./run.sh
```

## Short description

> ELF 64bit, C, strip, no pack
> 
> re / pwn task

## Solution

> 1. You have stripped binary with simple logic
>
> 2. Input shellcode xor's with 0x7f and run with rules
>
> 3. "R" rule - "replace" all bytes that less of num after "R"
> 
> 4. "S" rule - "swap" all bytes of first arg to second 
>
> 5. "L" rule - "layout", this is code segment size
>
> 6. "C" rule -  "code", this is code start offset
>
> 7. The standard set of rules is very inconvenient
>
> 8. You can send our rules and run simple shellcode
>
>

[solution script](solve/exploit.py)
 
## Flag

`Aero{dad088ac762b071665d321c2aa22c5f84f66dca4e8865da998666d15b3ca0e0a}`
