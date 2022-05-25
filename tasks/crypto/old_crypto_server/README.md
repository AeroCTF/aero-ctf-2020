# Crypto | Old Crypto Server

## Info

> We found a very old crypto server. 
>
> He has a secret that we want to get.
>
> However, he will not give it up so easily.
>
> nc <ip> <port>
>
> * flag form for this task is Aero{[0-9a-f]{32}} * 
> 

## Run

Give participants a script from deploy static and ip:port of service
```
cd deploy
docker-compose -p oldcryptoserver up --build -d # or ./run.sh
```

## Short description

> Python 2.7 script with AES ECB
> 

## Solution

> 1. Server use AES ECB algo and add secret(flag) to your input 
>
> 2. You can make a buffer that allows you to get 1 flag symbol due to the features of the ECB mode
>
> 3. This way you can get all the symbols of the flag
> 

[solution script](solve/solver.py)
 
## Flag

`Aero{5013a76ed3b98bae1e79169b3495f47a}`
