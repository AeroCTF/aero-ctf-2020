import SocketServer

import struct
import zlib
from time import sleep

p_8  = lambda val : struct.pack( "!B", val )
p_16 = lambda val : struct.pack( "!H", val )
p_32 = lambda val : struct.pack( "!L", val )


u_32 = lambda val : struct.unpack( "!L", val )[ 0 ]

class MyUDPHandler(SocketServer.BaseRequestHandler):
    """
    This class works similar to the TCP handler class, except that
    self.request consists of a pair of data and client socket, and since
    there is no connection the client address must be given explicitly
    when sending data back via sendto().
    """

    def handle(self):
        data = self.request[0].strip()
        socket = self.request[1]
        
        print "connection, data = %s" % data.encode('hex')

        if data == "\x21\x37\x91\xDE\x17\x89\xAB\xC0\x08\xC9\xFF\xD2\xFE\xDA\x01\x02":
            print "send to client"
            socket.sendto( "\xC0\xC0\xC0\xC0", self.client_address )

            file_map = {}

            while 1:
                sleep( 0.1 )
                data = self.request[0].strip()
                socket = self.request[1]

                if data == "\xDE\xAD\xDE\xAD\xDE\xAD\xDE\xAD":
                    break

                size  = u_32( data[ 4:8 ] )
                start = u_32( data[ 8:12 ] )
                end   = u_32( data[ 12:16 ] )
                data = data[16:16+size]

                indexes = [start,end]
                file_map[ data ] = indexes

            print file_map

if __name__ == "__main__":
    HOST, PORT = "0.0.0.0", 24
    server = SocketServer.UDPServer((HOST, PORT), MyUDPHandler)
    server.serve_forever()