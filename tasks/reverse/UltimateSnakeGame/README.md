# Binary | Ultimate Snake Game

## Info

> This is a super secure "Snake" game, but the rules are incredible. 
>
> And the snake does not move correctly.
>

## Run

Give participants a binary from deploy/static

## Short description

> Windows x64 binary with VMProtect

## Solution

> 1. It’s better not to start reversing this file and trying to bypass VMProtect
>
> 2. You need to look in procmon or something like that (e.x. some Api monitor)
> 
> 3. And you can see a query which return a free disk space in bytes (this is a GetDiskFreeSpaceExA)
>
> 4. You can create a new disk or use some USB-device and fill-up them.
> 
> 5. Run the program on a disk with no free space and you will get a flag

## Flag

`Aero{68b05fb8a0a617c4771d76b7f0e6df63b4f728ef3966bf6a9a69f53c8d882eac}`
