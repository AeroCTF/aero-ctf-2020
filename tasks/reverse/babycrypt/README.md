# Binary | Babycrypt

## Info

> We develope our own program for encrypting text.
>
> But it is not very convenient and seems to encrypt not secure. 
>
> Try a plaintext attack to get key and decode flag!
>

## Run

Give participants a binary and note.dat from deploy/static

## Short description

> ELF 64bit and file with crypto and plaintexts

## Solution

> 1. You have 3 encryption result and plaintext
>
> 2. In binary, you can find simple XOR algo ((data[i]^key[i%len(key)]) + key[i%len(key)])
>
> 3. The key for all encryption is the same
> 
> 4. In binary, you can find key restrictions (0123456789abcdefgh)
>
> 5. With three encryption you can recover almost all the characters of the key and just have to sort out

[solution script](solve/solve.py)
 
## Flag

`Aero{381a95d003629088c8f1ebc189ab6fe7}`
