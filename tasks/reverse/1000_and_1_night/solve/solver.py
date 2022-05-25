from pwn import *
import os
import ast
import re

buf = open( 'valids.txt', 'rb' ).read().strip()

if len( buf ) < 1000:
	os.system( "python binary_proceeder.py > valids.txt" )
	buf = open( 'valids.txt', 'rb' ).read().strip()

valids = ast.literal_eval( buf ) 
print( len( valids.keys() ) ) 

while 1:
	r = remote( 'localhost', 31337 )
	correct = 0 

	while 1:

		buf = r.recvline()

		if "Aero" in buf:
			print buf
			break

		line = re.findall( "<[0-9a-f]{32}>", buf.strip() )
		binary_name = line[0][1:-1]
		r.recvuntil( ": " )
		try:
			r.send( valids[ binary_name ] + '\n' )
		except:
			break

		correct += 1

	if correct > 50:
		print correct
	r.close()
