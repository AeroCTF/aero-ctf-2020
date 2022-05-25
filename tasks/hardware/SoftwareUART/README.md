# PIC | Mental Adventure: Orderly Trap

## Info

> You wanted to escape, but fell into the trap of an orderly. 
>
> Try to get out of it.
>

## Run

Give a *.HEX

## Short description

> Small PIC assembled program
> You need to enter valid key to UART
> Each symbol encrypted by crc16
> And XOR with key

## Solution

> 1. Get CRC16 with every symbol
>
> 2. XOR with key
>
> 3. Compare with flag in memory
## Flag

`Aero{331c6883dd6010864b7ead130be77cd5}`
