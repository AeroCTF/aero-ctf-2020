from pwn import *
from base64 import b64encode, b64decode
import sys

alph = 'Aero{0123456789abcdef}' 

if __name__ == "__main__":

	r = remote( 'tasks.aeroctf.com', 44323 )

	cur_flag = ''

	for i in range( 0, 16 ):
		for char in alph:
			r.recvuntil( "> " )
			r.send( '3\n' )

			payload  = 'a'*(15-len(cur_flag)) + cur_flag + char # 16 byte
			payload += 'a'*(15-len(cur_flag))

			r.recvuntil( ": " )
			r.send( payload + '\n' )

			data = r.recvline().split(':')[1][3:-2]
			parts = b64decode( data ).encode( 'hex' )
			
			guesed = parts[0:32]
			nedded = parts[32:64]

			if guesed == nedded:
				cur_flag += char
				break

	for i in range( 0, 16 ):
		for char in alph:
			r.recvuntil( "> " )
			r.send( "3\n" )

			payload = cur_flag[1+i:] + char
			payload += 'a'*(15-i)

			r.recvuntil( ": " )
			r.send( payload + '\n' )

			data = r.recvline().split(':')[1][3:-2]
			parts = b64decode( data ).encode( 'hex' )

			guesed = parts[0:32]
			nedded = parts[64:96]

			if guesed == nedded:
				cur_flag += char
				break

	for i in range( 0, 6 ):
		for char in alph:
			r.recvuntil( "> " )
			r.send( "3\n" )

			payload = cur_flag[17+i:] + char
			payload += 'a'*(15-i)

			r.recvuntil( ": " )
			r.send( payload + '\n' )

			data = r.recvline().split(':')[1][3:-2]
			parts = b64decode( data ).encode( 'hex' )

			guesed = parts[0:32]
			nedded = parts[96:128]

			if guesed == nedded:
				cur_flag += char
				break

	print "{+} Flag: %s" % cur_flag
