import socket
import random
import struct
import zlib
import sys

from time import sleep

p_8  = lambda val : struct.pack( "!B", val )
p_16 = lambda val : struct.pack( "!H", val )
p32 = lambda val : struct.pack( "!L", val )

u_8  = lambda val : struct.unpack( "!B", val )[ 0 ]
u_16 = lambda val : struct.unpack( "!H", val )[ 0 ]
u_32 = lambda val : struct.unpack( "!L", val )[ 0 ]

# Aero{00283f897b86f877f1fb738eeb2d0465c28fc495cad200c755f985b832912a59}
buf = open( sys.argv[ 1 ], 'rb' ).read() 

msgFromClient       = "Hello UDP Server"
bytesToSend         = str.encode(msgFromClient)
serverAddressPort   = ( "192.168.1.107", 24 )
bufferSize          = 1024

file_map = {}
idx = 0

while idx < len( buf ):
	start = idx
	end = random.randint( idx+1, idx+bufferSize )

	transmit_part = buf[ start:end ]

	indexes = [start,end]
	file_map[ transmit_part ] = indexes
	idx = end

#print file_map

# # Create a UDP socket at client side
UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

# start session
to_send = p32( 0x213791DE )
to_send += p32( 0x1789ABC0 )
to_send += p32( 0x08C9FFD2 )
to_send += p32( 0xFEDA0102 )

UDPClientSocket.sendto( to_send, serverAddressPort )
msgFromServer = UDPClientSocket.recvfrom( bufferSize )
answer = msgFromServer[ 0 ]

# print type( msgFromServer )
# print msgFromServer[0].encode('hex')
# print len( msgFromServer[ 0 ] )
# print msgFromServer[ 1 ]
# print "recvmsg: ", answer

if answer == '\xC0\xC0\xC0\xC0':
	print "init sess "
	# main 
	for i in file_map.keys():
		sleep( 0.1 )
		to_send = p32( zlib.crc32( i ) % (1<<32) )
		to_send += p32( len( i ) )
		to_send += p32( file_map[ i ][ 0 ] ) # start offset 
		to_send += p32( file_map[ i ][ 1 ] ) # end offset
		to_send += i

		UDPClientSocket.sendto( to_send, serverAddressPort )

print "cancel transmition"

UDPClientSocket.sendto( "\xDE\xAD\xDE\xAD\xDE\xAD\xDE\xAD", serverAddressPort )

#msgFromServer = UDPClientSocket.recvfrom(bufferSize)

# msg = "Message from Server {}".format(msgFromServer[0])
# print(msg)