# Binary | go away

## Info

> This binary is real angry.
>
> But he can give you a flag if you ask well
>

## Run

Give participants a binary from deploy/static

## Short description

> ELF64bit Golang, striped, packed 

## Solution

> 1. Each key character is hashed using MD5, but the constants for the algorithm have been changed
>
> 2. After hashing, the obtained value is compared with the stored value
>
> 3. If the key is correct, the program should display a flag, however, it displays a flag decrypted by another key.
> 
> 4. The easiest way is to find the storage location of the static key and replace it with the correct one.


## Flag

`Aero{3475964bdbfe31fbb40d812fa2f88114765baf72fd7ef0a912c746312bbdc07b}`
