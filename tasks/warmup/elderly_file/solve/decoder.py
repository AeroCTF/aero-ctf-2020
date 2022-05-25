import lzss
import sys


if __name__ == "__main__":

	if len( sys.argv ) > 1:
		file_path = sys.argv[ 1 ]
	else:
		print "Usage: " + sys.argv[ 0 ] + " <file-path>"
		sys.exit( -1 )

	lzss.decode_file( file_path, file_path + ".dec" ) 
