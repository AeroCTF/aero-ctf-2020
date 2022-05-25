import random
import string
import sys
import os

from hashlib import md5

template_name = 'template.c'
valid_tokens = {}
alph = string.ascii_lowercase + string.ascii_uppercase + string.digits

def get_random_string( size=8 ):
	return ''.join( [ random.choice( alph ) for i in range( 0, size ) ] )

def parse_token( token ):
	syms = [ ord(i) for i in token ]
	res = []
	code = []
	
	xor_const = random.randint( 10, 37 )
	sum_const = random.randint( 5, 10 )
	sub_const = random.randint( 7, 15 )

	for i in range( len( syms ) ):
		res.append( ( ( syms[ i ] + sum_const ) ^ xor_const ) - sub_const )

	code.append( "unsigned char valids[%d] = {%s};" % ( len( res ), str( res )[1:-1] ) )
	code.append( "for (int i = 0; i < %d; i++) { buf[i] = ((buf[i]+%d)^%d)-%d; }" 
		% ( len( res ), sum_const, xor_const, sub_const ) )
	code.append( "if ( memcmp(buf,valids,%d)){ return 0;}" % len( res ) )

	return code

def generate( number ):
	global valid_tokens

	out_name = md5( str( number ) ).hexdigest()
	valid_token = md5( get_random_string() ).hexdigest()

	if out_name not in valid_tokens.keys():
		valid_tokens[ out_name ] = valid_token

	code = parse_token( valid_token )
	res = '\n'.join( code )

	return res, out_name

if __name__ == "__main__":

	buf = open( template_name, 'rb' ).read()
	
	for i in range( 0, 1001 ):
		code, name = generate( i )
		res = buf % code

		fd = open( name + ".c", 'wb' )
		fd.write( res )
		fd.close()

		os.system( "gcc %s -o %s" % ( name + ".c" , name ) )
		os.system( "rm %s" % ( name  + ".c" ) )
		os.system( "mv %s binarys/%s" % ( name, name ) )

	print valid_tokens