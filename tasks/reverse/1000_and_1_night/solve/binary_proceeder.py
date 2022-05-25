from subprocess import Popen, PIPE
import os
from binascii import unhexlify

files = os.listdir( '../dev/binarys' )
valids = {}

for file in files:
	if file == 'solver.py':
		continue

	p = Popen( [ 'objdump', '-M', 'intel', '-d', "../dev/binarys/" + file ], 
		stdin=PIPE, stdout=PIPE, stderr=PIPE )

	output, err = p.communicate()

	start = output.index("<check>:")
	output = output[start:]
	end = output.index( "ret" )
	output = output[:end]
	output = output.split( '\n' )

	try:
		res = ''
		res += unhexlify(output[ 5 ].strip().split( ' ' )[-1].split(',')[1][2:])[::-1]
		res += unhexlify(output[ 7 ].strip().split( ' ' )[-1].split(',')[1][2:])[::-1]
		res += unhexlify(output[ 11 ].strip().split( ' ' )[-1].split(',')[1][2:])[::-1]
		res += unhexlify(output[ 13 ].strip().split( ' ' )[-1].split(',')[1][2:])[::-1]

		add_val = int( output[ 24 ].strip().split( ' ' )[-1].split(',')[1], 16 )
		xor_val = int( output[ 25 ].strip().split( ' ' )[-1].split(',')[1], 16 )
		sub_val = int( output[ 26 ].strip().split( ' ' )[-1].split(',')[1].split('-')[1][:-1], 16 )
	except:
		print output[5]
		print output[7]
		print output[11]
		print output[13]
		continue

	token = ''

	for i in res:
		token += chr( ( ( ord( i ) + sub_val ) ^ xor_val ) - add_val )

	valids[ file ] = token

print valids