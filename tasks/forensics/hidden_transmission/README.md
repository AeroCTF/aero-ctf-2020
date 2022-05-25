# Forensic | Hidden Transmission

## Info

> Some jokers like to spam on the net with all the funny pictures. 
>
> But they say that this is just a cover for the transfer of something more important.
>


## Run

Give participants a file from deploy/static

## Short description

> Network traffic file with custom protocol over UDP

## Solution

> 1. There is a lot of garbage in the traffic and some funny pictures over TCP
>
> 2. A lot of data is being transmitted over the UPD, but it looks weird.
> 
> 3. If you take it apart, you can understand that the packages are built on a fairly simple type.
>
> 4. The first 4 bytes is the checksum from the data
> 
> 5. The second 4 bytes is the size of the data.
> 
> 6. The subsequent bytes specify the initial and final offset of the data inside the transmitted file.
> 
> 7. Thus, several files were transferred
> 
> 8. You need "udp.stream eq 28"

[decoder script](solve/decoder.py)

## Flag

`Aero{00283f897b86f877f1fb738eeb2d0465c28fc495cad200c755f985b832912a59}`
