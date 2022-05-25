# Binary | Bass Boosted

## Info

> New bass boosted mixes are quickly blocked.
>
> So we made an application that issues a new link only to the owner of the key.
>
> Try to restore the key and get a link to the new mix.
>

## Run

Give participants a binary from deploy/static

## Short description

> PE 32bit MSVC 2019 with boost

## Solution

> 1. The program checks that the entered characters belong to the flag characters. (A[a-f0-9]ro{})
>
> 2. User key is reversing with std::reverse
>
> 3. Each element passes through XOR with a special key for it, which is defined in the class dictionary.
> 
> 4. After that, the random number generator based on the sum of the keys is initialized
>
> 5. It goes through 10,000 idle iterations and then returns the value used to initialize another generator.
>
> 6. Using the second generator, numbers are obtained that are superimposed by the XOR on the sequence
> 
> 7. The resulting sequence is converted to hexadecimal and compared with the hash in memory
> 

[solution code](solve/bass_boosted_solution.cpp)

## Flag

`Aero{f9ab233aa72e71a6b688d78035e563673e92a62016baa60efee04ee6ae823f85}`
