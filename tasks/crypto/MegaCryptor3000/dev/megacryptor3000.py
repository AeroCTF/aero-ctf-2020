#!/usr/bin/env python3

import sys
import os
import random
import argparse
import string
import struct

from binascii import unhexlify, hexlify
from des import DesKey

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

ror16 = lambda val, r_bits : ror( val, r_bits, 16 )
rol16 = lambda val, r_bits : rol( val, r_bits, 16 )

ror32 = lambda val, r_bits : ror( val, r_bits, 32 )
rol32 = lambda val, r_bits : rol( val, r_bits, 32 )

alphanumeric = string.ascii_lowercase + string.ascii_uppercase + string.digits

class CONST:
	DES_DEFAULT_KEY_SIZE = 8
	DEFAULT_BLOCK_SIZE   = 64

class ERR:
	ARG_PARSE_ERR			= 0x7001
	FILE_IS_NOT_EXIST		= 0x7002
	CANNOT_FILE_OPEN		= 0x7003
	FILE_IS_EMPTY			= 0x7004
	KEYFILE_FORMAT_ERORR 	= 0x7005
	WEAK_KEYS_FOUND			= 0x7006
	WEAK_KEYLINE			= 0x7007
	INTERSECTIONS_COUNT		= 0x7008
	ALPHANUMERIC_COUNT		= 0x7009 
	INDEX_OUT_OF_RANGE		= 0x700a
	INCORRECT_BLOCK_SIZE	= 0x700b
	INCORRECT_COUNT_OF_KEYS = 0x700c

class Key:
	m_keys = []
	weak_keys = [ 
		b'\x01\x01\x01\x01\x01\x01\x01\x01', 
		b'\xfe\xfe\xfe\xfe\xfe\xfe\xfe\xfe',
		b'\x1f\x1f\x1f\x1f\x0e\x0e\x0e\x0e',
		b'\xe0\xe0\xe0\xe0\xf1\xf1\xf1\xf1'
	]

	def __init__( self, keydata ):
		self.parse_keydata( keydata )

		if len( self.m_keys ) // 8 != 1:
			print( "[-] Count of keys is not valid!" )
			print( "[-] Should be divisible by 8" )
			sys.exit( ERR.INCORRECT_COUNT_OF_KEYS )

	def shuffle_keys( self ):
		seed = 0

		for key in self.m_keys:
			for sym in key:
				seed += sym

		random.seed( seed )
		random.shuffle( self.m_keys )

	def parse_keydata( self, keydata ):
		tmp_keys = keydata.split( b'\n' )
		
		for i in range( len( tmp_keys ) ):
			if tmp_keys[ i ] == '':
				continue

			keyline = unhexlify( tmp_keys[ i ] )

			if len( keyline ) != CONST.DES_DEFAULT_KEY_SIZE:
				print( "[-] Incorrect keyfile format!" )
				sys.exit( ERR.KEYFILE_FORMAT_ERORR )

			if keyline in self.weak_keys:
				print( "[-] Keyfile has weak keys!" )
				sys.exit( ERR.WEAK_KEYS_FOUND )

			alphanum_count = 0

			for key_symbol in keyline:
				if keyline.count( key_symbol ) > 4:
					print( "[-] Weak keyline!" )
					sys.exit( ERR.WEAK_KEYLINE )
				
				if chr(key_symbol) in alphanumeric:
					alphanum_count += 1 

			if alphanum_count > 4:
				print( "[-] To much alpha-numeric symbols in key!" )
				sys.exit( ERR.ALPHANUMERIC_COUNT )

			if len( self.m_keys ) != 0:
				last_key = self.m_keys[ -1 ]

				if len( list( set( last_key ) & set( keyline ) ) ) > 4:
					print( "[-] To much intersections with last key!" )
					sys.exit( ERR.INTERSECTIONS_COUNT )

			self.m_keys.append( keyline )

	def get( self, idx ):
		assert( type( idx ) == int )

		if idx >= len( self.m_keys ):
			print( "[-] Index out of range in keys!" )
			sys.exit( ERR.INDEX_OUT_OF_RANGE )

		return self.m_keys[ idx ]

	def get_keys_count( self ):
		return len( self.m_keys )

class Encryptor:
	m_key = None
	e_seq = []

	def __init__( self, key ):
		self.m_key = key

	def encrypt( self, data ):
		seed = 0
		out = b''
		key = self.m_key.get( seed )

		for i in key:
			seed += i 

		if len( data ) % CONST.DEFAULT_BLOCK_SIZE != 0:
			data += b'\x00' * ( CONST.DEFAULT_BLOCK_SIZE - 
				( len( data ) % CONST.DEFAULT_BLOCK_SIZE ) )

		random.seed( seed )

		for i in range( 0, len( data ) // CONST.DEFAULT_BLOCK_SIZE ):
			self.e_seq.append( random.randint( 0, 3 ) )

		for i in range( 0, len( data ), CONST.DEFAULT_BLOCK_SIZE ):
			e_idx = i // CONST.DEFAULT_BLOCK_SIZE
			block = data[ i : i + CONST.DEFAULT_BLOCK_SIZE ] 
			out += self.encrypt_block( block, self.e_seq[ e_idx ] )
			
		return out

	def encrypt_block( self, block, e_type ):
		if len( block ) != CONST.DEFAULT_BLOCK_SIZE:
			print( "Error in block encryption!" )
			sys.exit( ERR.INCORRECT_BLOCK_SIZE )

		keys_count = self.m_key.get_keys_count()	
		res_block = b''
 
		if e_type == 0:
			key_idx = 0

			block = list( block )

			for i in range( 0, len( block ), 2 ):
				block[ i ] = ror8( block[ i ], 5 )
				block[ i + 1 ] = rol8( block[ i + 1 ], 3 )

			block = bytes( block )

			for i in range( 0, len( block ), 8 ):
				key_idx %= keys_count

				block_part = block[ i : i + 8 ]
				
				key = self.m_key.get( key_idx )
				key_idx += 1
				key = DesKey( key )

				res_block += key.encrypt( block_part )

		elif e_type == 1:

			shuffle_seed = 0

			for i in range( keys_count ):
				key = self.m_key.get( i )

				for j in key:
					shuffle_seed += j

			block = list( block )
			random.seed( shuffle_seed )
			random.shuffle( block )

			res_block = bytes( block )

		elif e_type == 2:
			key_idx = 0

			for i in range( 0, len( block ), 8 ):
				key_idx %= keys_count

				block_part = block[ i : i + 8 ]

				key = self.m_key.get( key_idx )
				key = DesKey( key )
				key_idx += 1
				
				block_part = key.encrypt( block_part )
				
				key = self.m_key.get( key_idx )
				key = DesKey( key )
				key_idx += 1

				res_block += key.encrypt( block_part )


		elif e_type == 3:
			seed = 0

			for i in range( keys_count ):
				key = self.m_key.get( i )

				seed += u_32( key[ 0 : 4 ] )
				seed += u_32( key[ -4 : ] )

			random.seed( seed )

			for i in range( 0, len( block ) ):
				x_key = random.randint( 0x00, 0xff )
				val   = block[ i ] 

				res_block += bytes( [ x_key ^ val ] )

		return res_block

def SaveData( Data, Filename ):
	fd = None

	try:
		fd = open( Filename, 'wb' )
	except:
		print ( "[-] Error in file <%s> creation!" )
		sys.exit( ERR.CANNOT_FILE_CREATE )

	nbytes = fd.write( Data )

	if nbytes == len( Data ):
		print( "[+] File <%s> is saved!" % Filename )

	fd.close()

def ReadFile( Filename ):
	if not os.path.isfile( Filename ):
		print( "[-] File is not exist!" )
		sys.exit( ERR.FILE_IS_NOT_EXIST )

	fd = None

	try:
		fd = open( Filename, 'rb' )
	except:
		print( "[-] Error in file <%s> open!" )
		sys.exit( ERR.CANNOT_FILE_OPEN )

	data = fd.read()

	if len( data ) <= 0:
		print( "[-] File is empty!" )
		sys.exit( ERR.FILE_IS_EMPTY )
	
	return bytes( data )

def argparse_init():
	parser = argparse.ArgumentParser()
	
	parser.add_argument( "-i", "--input",
	 	metavar = 'inputfile', 
		type = str, 
		nargs = 1,
		required = True,
		help = 'input file' )
	parser.add_argument( "-k", "--key", 
		metavar = 'keyfile', 
		type = str, 
		nargs = 1,
		required = True,
		help = 'key file' )
	parser.add_argument( "-o", "--output", 
		metavar = 'outfile', 
		type = str, 
		nargs = 1,
		required = True,
		help = 'output file' )

	return parser 

if __name__ == "__main__":

	parser = argparse_init()
	args = parser.parse_args()

	inp_file = None
	out_file = None
	key_file = None

	try:
		inp_file = args.input[ 0 ]
		out_file = args.output[ 0 ]
		key_file = args.key[ 0 ]
	except:
		print( "[-] Error in argument parsgin!" )
		sys.exit( ERR.ARG_PARSE_ERR )

	InputFileData = ReadFile( inp_file )
	KeyFileData   = ReadFile( key_file  )

	key = Key( KeyFileData )
	encryptor = Encryptor( key )
	enc_data = encryptor.encrypt( InputFileData )

	SaveData( enc_data, out_file )
