package main

import(
	"bufio"
	"fmt"
	"strings"
	"os"
)

// Aero{bef92fde1a5040fd5c9cbba17e1fa179afd29bf0afd9f05fe150eafb2398de4f}
var rnd_val uint32 

func set_seed( seed uint32 ) {
	rnd_val = seed 
}
func get_byte() uint8 {
	rnd_val = ((0x1282 * rnd_val) + 0x1634) % 0xfefefefe
	return uint8( rnd_val & 0xff )
}

func main() {
	reader := bufio.NewReader( os.Stdin )

	fmt.Println( "--------- ReWarmup ---------" )
	fmt.Print( "Flag: " )

	text, _ := reader.ReadString( '\n' )
	text = strings.Replace( text, "\n", "", -1 )

	if len( text ) != 70 {
		fmt.Println( "{-} Incorrect key!" )
		return
	}

	flag_hash := []int{ 147,189,150,147,87,238,41,170,245,254,170,168,169,253,173,249,252,248,252,170,168,249,175,245,175,174,174,173,253,251,169,253,170,173,253,251,245,173,170,168,254,245,174,170,252,173,170,168,245,170,252,249,170,169,253,249,252,169,173,170,174,254,255,245,244,168,169,248,170,177 }

	var orig_seed uint32
	orig_seed = 0

	for i := 0; i < len( text ); i += 1 {
		orig_seed += uint32( text[ i ] )
	}

	// fmt.Println( "seed= ", orig_seed )
	set_seed( orig_seed )

	for i := 0; i < len( text ); i += 1 {
		byte := int(get_byte())
		value := int( text[ i ] )

		//fmt.Printf( "%d,", byte^value )

		if (byte^value) != flag_hash[ i ] {
			fmt.Println( "{-} Incorrect flag!" )
			return 
		}
	}

	fmt.Println( "{+} Correct flag" )
}