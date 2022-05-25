#!/usr/bin/env python3

import random
from des import DesKey
import struct

all_partially_weak_keys = [
		[b'\x01\x1F\x01\x1F\x01\x0E\x01\x0E',b'\x1F\x01\x1F\x01\x0E\x01\x0E\x01'],
		[b'\x01\xE0\x01\xE0\x01\xF1\x01\xF1',b'\xE0\x01\xE0\x01\xF1\x01\xF1\x01'],
		[b'\x1F\xFE\x1F\xFE\x0E\xFE\x0E\xFE',b'\xFE\x1F\xFE\x1F\xFE\x0E\xFE\x0E'],
		[b'\x01\xFE\x01\xFE\x01\xFE\x01\xFE',b'\xFE\x01\xFE\x01\xFE\x01\xFE\x01'],
		[b'\x1F\xE0\x1F\xE0\x1F\xE0\x1F\xE0',b'\xE0\xF1\xE0\xF1\xE0\xF1\xE0\xF1'],
		[b'\xE0\xFE\xE0\xFE\xF1\xFE\xF1\xFE',b'\xFE\xE0\xFE\xE0\xFE\xE0\xFE\xE0']
	]

p_8  = lambda val : struct.pack( "!B", val )
p_16 = lambda val : struct.pack( "!H", val )
p_32 = lambda val : struct.pack( "!L", val )

u_8  = lambda val : struct.unpack( "!B", val )[ 0 ]
u_16 = lambda val : struct.unpack( "!H", val )[ 0 ]
u_32 = lambda val : struct.unpack( "!L", val )[ 0 ]

rol = lambda val, r_bits, max_bits: \
    (val << r_bits%max_bits) & (2**max_bits-1) | \
    ((val & (2**max_bits-1)) >> (max_bits-(r_bits%max_bits)))
 
ror = lambda val, r_bits, max_bits: \
    ((val & (2**max_bits-1)) >> r_bits%max_bits) | \
    (val << (max_bits-(r_bits%max_bits)) & (2**max_bits-1))

ror8 = lambda val, r_bits : ror( val, r_bits, 8 )
rol8 = lambda val, r_bits : rol( val, r_bits, 8 )


def shuffle(seed, array):
    random.seed(seed)
    array_ = array[:]
    random.shuffle(array_)
    return array_

def unshuffle(seed, array):
    indexes = list(range(len(array)))
    shuffled = shuffle(seed, indexes)
    trans = {i: shuffled.index(i) for i in indexes}
    return [array[trans[i]] for i in trans]

def e3_decode( data, keys ):
	seed = 0
	res_block = b''

	for i in range( len( keys ) ):
		key = keys[ i ]

		seed += u_32( key[ 0 : 4 ] )
		seed += u_32( key[ -4 : ] )

	random.seed( seed )

	for i in range( 0, len( data ) ):
		x_key = random.randint( 0x00, 0xff )
		val   = data[ i ] 

		res_block += bytes( [ x_key ^ val ] )

	return res_block

def e1_decode( data, keys ):
	shuffle_seed = 0

	for i in range( len( keys ) ):
		key = keys[ i ]

		for j in key:
			shuffle_seed += j

	res_block = unshuffle( shuffle_seed, list( data ) )
	res_block = bytes( res_block )

	return res_block

def e0_decode_8( data, key ):
	key = DesKey( key )
	res = key.decrypt( data )

	block = list( res )

	for i in range( 0, len( block ), 2 ):
		block[ i ] = rol8( block[ i ], 5 )
		block[ i + 1 ] = ror8( block[ i + 1 ], 3 )

	return bytes( block ) 

def e0_decode( data, keys ):
	res = b''

	key_idx = 0
	for i in range( 0, len( data ), 8 ):
		key = keys[ key_idx ]
		key_idx += 1
		block = data[ i : i + 8 ]

		res += e0_decode_8( block, key ) 

	return res 


def decode_buf( buf, keys, e_seq ):

	idx = 0 
	out = b''

	for i in e_seq:
		block = buf[ idx : idx + 64 ]
		idx += 64

		if i == 0:
			out += e0_decode( block, keys )
		elif i == 1:
			out += e1_decode( block, keys )
		elif i == 2:
			out += block
		elif i == 3:
			out += e3_decode( block, keys )

	return out


	
if __name__ == "__main__":

	# Looking at the file, you can find unencrypted zones.
	# This could only happen with e_type == 2 since it uses double encryption using DES and two consecutive keys. 
	# These keys can potentially be part of partially weak keys.

	# Now you can try to find the initial seed by sorting through possible weak keys.
	buf = open( 'out.enc', 'rb' ).read()

	possible_keys = [
		b'\x01\xFE\x01\xFE\x01\xFE\x01\xFE',
		b'\x1F\xE0\x1F\xE0\x1F\xE0\x1F\xE0',
		b'\x01\xE0\x01\xE0\x01\xF1\x01\xF1',
		b'\x1F\xFE\x1F\xFE\x0E\xFE\x0E\xFE',
		b'\x01\x1F\x01\x1F\x01\x0E\x01\x0E',
		b'\xE0\xFE\xE0\xFE\xF1\xFE\xF1\xFE'
	]

	for key in possible_keys:
		seed = 0

		for i in key:
			seed += i 

		random.seed( seed )

		e_seq = []

		for i in range( 0, 16 ):
			e_seq.append( random.randint( 0, 3 ) )

		if e_seq[ 8 ] == 2 and e_seq[ 10 ] == 2 and e_seq[ 11 ] == 2:
			#print( "seed = %d, key = %s" % ( seed, key ) )
			#print( e_seq ) # e_seq[ 0 ] == 0 

			# After we detected the correct key, we will try to decrypt the first 8 bytes of the file using the key
			decrypt = e0_decode_8( buf[ 0:8 ], key )

			# For the first key, we can notice the signature of the JPEG file
			if decrypt[0:4] == b"\xFF\xD8\xFF\xE0":
				print( "correct key =", key )
				print( "correct seq = ", e_seq )

	# Now we know the first two keys for sure
	# It remains for us to take the remaining pairs of partially weak keys and, 
	# by rearranging their positions, find the correct sequence and decrypt the file
	
	valid_seq = [
		b'\x01\xFE\x01\xFE\x01\xFE\x01\xFE',
		b'\xFE\x01\xFE\x01\xFE\x01\xFE\x01'
	]

	count = 0
	e_seq = []
	seed = 0

	# get full e_seq 
	for i in valid_seq[0]:
		seed += i 

	random.seed( seed )

	for i in range( 0, len( buf ) // 64 ):
		e_seq.append( random.randint( 0, 3 ) )


	for elem1 in all_partially_weak_keys:
		for elem2 in all_partially_weak_keys:
			for elem3 in all_partially_weak_keys:
				
				try_seq = []
				try_seq.append( valid_seq[ 0 ] )
				try_seq.append( valid_seq[ 1 ] )
				try_seq.append( elem1[ 0 ] )
				try_seq.append( elem1[ 1 ] )
				try_seq.append( elem2[ 0 ] )
				try_seq.append( elem2[ 1 ] )
				try_seq.append( elem3[ 0 ] )
				try_seq.append( elem3[ 1 ] )


				output = decode_buf( buf, try_seq, e_seq )	

				fname = "test_%d.jpg" % count
				fd = open( fname, 'wb' )
				fd.write( output )
				fd.close()

				count += 1 