# PIC | Mental_Adventure: Give Me My Cap

## Info

> Last task brought bad influence for our mental. 
> We hope it'll not happen with you.

## Run

Give a *.HEX

## Short description

> Small PIC assembled program
> You need to enter valid key to UART or
> Decode the flag
> XOR encryption with LCG

## Solution

> 1. Try to load this program to Proteus
>
> 2. You have LCG generator code
>
> 3. 1st seed is 0x1337, this seed help you to decode key for UART
>
> 4. 2nd seed is 0x6724, this seed help you to decode flag
>
> 5. You have 2 ways:
>     1. Enter valid key to UART: "jgznmhf,jnf726"
>     2. Decode flag[] = {0x3b, 0xbd, 0xbc, 0x95, 0x6, 0xe1, 0xdb, 0x36, 0xc9, 0x3a, 0xa9, 0x3b, 0x61, 0x44, 0x99, 0x50, 0xc4, 0xde, 0x85, 0x84};
## Flag

`AERO{UART1_WITH_MLG}`
