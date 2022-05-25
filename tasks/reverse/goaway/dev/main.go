package main

import(
	"bufio"
	"fmt"
	"os"
	"crypto/md5"
	"crypto/aes"
	"crypto/cipher"
	"encoding/hex"
	"strings"
)

// key = secretkeykeklol1
// Aero{3475964bdbfe31fbb40d812fa2f88114765baf72fd7ef0a912c746312bbdc07b}
// 7365637265746b65796b656b6c6f6c31

func ExampleNewCBCDecrypter( inp_key string ) {
	key, _ := hex.DecodeString( inp_key )
	ciphertext, _ := hex.DecodeString( "ca9e121f2b32d53b40345ded5093f977a4a6247b82b609e1f0ed0bc6f075f7b383301c9b24e5de429cd0063bcfd3366ac5890101c2f57d0abb8663009b3c8ae779dc0c4b634077d16210f96983b57e8a")
	block, _ := aes.NewCipher( key )

	iv := key
	mode := cipher.NewCBCDecrypter( block, iv )

	mode.CryptBlocks( ciphertext, ciphertext )
	fmt.Printf( "%s\n", ciphertext )
}

// secretkeykeklol1
// key = s e c r e t k e y k e  k  l  o  l  1
//       0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15

// s == b16046de4218897866255f7155926640 0
// e == 1ab40ef4c2aff666c576cc11304a6247 1 
// c == a71b1d3a54581249403bb9ed4ebe3e7e 2 
// r == b2ec463456bd0afcc476c992415f6689 3 
// t == 8064fb6f3aeddccf1e650d59646145c9 4 
// k == 05dfe37ba7a71994c218d76b6828199d 5 
// y == a6d750196f7bbb8348ca6dec0f4422a6 6 
// l == 73c5e9ead981ae0515aa914fd301b3b5 7 
// o == 9071bf3e8f7f90653c1fcda9c90bf4a4 8 
// 1 == 55e296307c2d80c3ab90eddf2ee3311c 9

func main() {
	reader := bufio.NewReader( os.Stdin )

	fmt.Println( "Go away I will not give you a flag!" )
	fmt.Println( "But if you guess the key I'll print you a flag...." )
	fmt.Print( "guess: " )

	text, _ := reader.ReadString( '\n' )
	text = strings.Replace( text, "\n", "", -1 )

	idxs := map[int]int{ 0:0, 1:1, 2:2, 3:3, 4:1, 5:4, 6:5, 7:1, 8:6, 9:5, 10:1, 11:5, 12:7, 13:8, 14:7, 15:9 }

	hash_map := make( [][]byte, 10 )

	hash_map[ 0 ] = []byte( "\xb1\x60\x46\xde\x42\x18\x89\x78\x66\x25\x5f\x71\x55\x92\x66\x40" )
	hash_map[ 1 ] = []byte( "\x1a\xb4\x0e\xf4\xc2\xaf\xf6\x66\xc5\x76\xcc\x11\x30\x4a\x62\x47" )
	hash_map[ 2 ] = []byte( "\xa7\x1b\x1d\x3a\x54\x58\x12\x49\x40\x3b\xb9\xed\x4e\xbe\x3e\x7e" )
	hash_map[ 3 ] = []byte( "\xb2\xec\x46\x34\x56\xbd\x0a\xfc\xc4\x76\xc9\x92\x41\x5f\x66\x89" )
	hash_map[ 4 ] = []byte( "\x80\x64\xfb\x6f\x3a\xed\xdc\xcf\x1e\x65\x0d\x59\x64\x61\x45\xc9" )
	hash_map[ 5 ] = []byte( "\x05\xdf\xe3\x7b\xa7\xa7\x19\x94\xc2\x18\xd7\x6b\x68\x28\x19\x9d" )
	hash_map[ 6 ] = []byte( "\xa6\xd7\x50\x19\x6f\x7b\xbb\x83\x48\xca\x6d\xec\x0f\x44\x22\xa6" )
	hash_map[ 7 ] = []byte( "\x73\xc5\xe9\xea\xd9\x81\xae\x05\x15\xaa\x91\x4f\xd3\x01\xb3\xb5" )
	hash_map[ 8 ] = []byte( "\x90\x71\xbf\x3e\x8f\x7f\x90\x65\x3c\x1f\xcd\xa9\xc9\x0b\xf4\xa4" )
	hash_map[ 9 ] = []byte( "\x55\xe2\x96\x30\x7c\x2d\x80\xc3\xab\x90\xed\xdf\x2e\xe3\x31\x1c" )

	if len( text ) != 16 {
		fmt.Println( "{-} Incorrect key!" )
		return
	}

	for i := 0; i < len( text ); i += 1 {
		sl := byte( text[ i ] )
		data := make([]byte,1)
		data[ 0 ] = sl

		for j, v := range md5.Sum( data ) {
			if v != hash_map[ idxs[i] ][ j ] {
				fmt.Println( "{-} Incorrect key!" )
				return
			}
		}
	}

	fmt.Println( "hmmmm...... key is correct! But I changed my mind about printing you a flag" )
	fmt.Println( "....." )
	fmt.Println( "Instead, I will display you a flag for the key 'testtesttesttest'" )
	fmt.Print( "flag: " )
	
	ExampleNewCBCDecrypter("74657374746573747465737474657374")
}