import itertools as it
import re

plain1 = "test_test_test_test_test"
enc1 = "7685737a9f7895737a9f84857b769f7a657b769f78898378".decode( 'hex' )

plain2 = "qwertyuiopasdfgh"
enc2 = "717785747885858d6f7e917364686776".decode( 'hex' )

plain3 = "skIllaoInasJjklqo19akq9k13k45k69alq1"
enc3 = "7393a992708d8fad708d83aa7273707d6f3939856b7d398bb53b8b34b573b6c5618e7135".decode( 'hex' )

orig_flag = "Aero{"
flag = "8185748f7b3b3a3565454584b8babbb8b441323ebc8b3a86b5899283b9c2c56d64388889b781".decode( 'hex' )
# orig key = abcdefg023156789

alph = 'abcdefgh0123456789'

if __name__ == "__main__":
	
	key1 = {}
	key2 = {}
	key3 = {}
	key4 = {}

	for j in range( 0, len( plain1 ) ):
		key1[j] = []

		for i in alph:
			try:
				if chr( ( ord( enc1[ j ] ) - ord(i) ) ^ ord(i) ) == plain1[ j ]:
					key1[j].append( i )
			except:
				continue
				

	for j in range( 0, len( plain2 ) ):
		key2[j] = []

		for i in alph:
			try:
				if chr( ( ord( enc2[ j ] ) - ord(i) ) ^ ord(i) ) == plain2[ j ]:
					key2[j].append( i )
			except:
				continue

	for j in range( 0, len( plain3 ) ):
		key3[j] = []

		for i in alph:
			try:
				if chr( ( ord( enc3[ j ] ) - ord(i) ) ^ ord(i) ) == plain3[ j ]:
					key3[j].append( i )
			except:
				continue

	for j in range( 0, 5 ):
		key4[j] = []

		for i in alph:
			try:
				if chr( ( ord( flag[ j ] ) - ord(i) ) ^ ord(i) ) == orig_flag[ j ]:
					key4[j].append( i )
			except:
				continue

	res = {}

	for i in range( 0, 16 ):
		res[i] = []

		for j in alph:
			if i <= 4:
				if j in key1[i] and j in key2[i] and j in key3[i] and j in key4[i]:
					res[i].append( j )
			else:
				if j in key1[i] and j in key2[i] and j in key3[i]:
					res[i].append( j )

	key_chars = []

	for i in range( 0, 16 ):
		if len( res[ i ] ) == 1:
			key_chars.append( res[i][0] )
		else:
			key_chars.append( res[i] )

	#print key_chars
	# ['a', ['4', '5'], '1', '3', 'b', '6', ['8', '9'], ['2', '3'], ['c', 'g'], '7', '8', '0', 'd', 'e', ['b', 'f'], 'g']

	for i in key_chars[1]:
		for j in key_chars[6]:
			for k in key_chars[7]:
				for l in key_chars[8]:
					for m in key_chars[14]:
						key  = key_chars[0]
						key += i
						key += key_chars[2]
						key += key_chars[3]
						key += key_chars[4]
						key += key_chars[5]+j+k+l+key_chars[9]+key_chars[10]+key_chars[11]+key_chars[12]+key_chars[13]+m+key_chars[15]

						res = ''

						for p in range( len( flag ) ):
							try:
								res += chr( (ord( flag[ p ] ) - ord( key[ p % len( key ) ] ) ) ^ ord( key[ p % len( key ) ] ) )
							except:
								res += 'X'

						res = re.findall( "Aero\{[0-9a-f]{32}\}", res )

						if len( res ) == 1:
							print res[ 0 ]