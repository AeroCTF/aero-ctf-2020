import socket
import random
import struct
import zlib
import sys

from time import sleep

# udp stream 28 

p_8  = lambda val : struct.pack( "!B", val )
p_16 = lambda val : struct.pack( "!H", val )
p32 = lambda val : struct.pack( "!L", val )

u_8  = lambda val : struct.unpack( "!B", val )[ 0 ]
u_16 = lambda val : struct.unpack( "!H", val )[ 0 ]
u32 = lambda val : struct.unpack( "!L", val )[ 0 ]

buf = open( sys.argv[ 1 ], 'rb' ).read()

file_size = len( buf )

idx = 0
data = bytearray( file_size )

while idx < file_size:

	crc    = u32( buf[ idx : idx + 4 ] )
	b_size = u32( buf[ idx + 4 : idx + 8 ] )
	start  = u32( buf[ idx + 8 : idx + 12 ] )
	end    = u32( buf[ idx + 12 : idx + 16 ] )

	_buf = buf[ idx + 16:  idx + 16 + b_size ]

	data[ start:end ] = _buf

	idx += 16 + b_size

fd = open( "test_decoded.hex", 'wb' )
fd.write( data )
fd.close()