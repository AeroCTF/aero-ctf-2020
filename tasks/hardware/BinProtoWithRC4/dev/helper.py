import random
import time

random.seed( time.time() )

_head = 'unsigned char lcg%d(void) {\n\tseed%d=((%d  * seed%d) + %d)' 
_tail = '%d;\n\treturn seed%d & 0xff;\n}\n'


# for i in range( 0, 15 ):
#     print "unsigned int seed%d=%d;" % ( i, random.randint( 0xff, 0x10ff ) ) 

# for i in range( 0, 15 ):
#     arg1 = random.randint( 0x0101, 0x1a1a )
#     arg2 = random.randint( 0xff, 0x10ff )
#     arg3 = random.randint( 0x01ff, 0xf0ff )
    
#     _string = _head % ( i, i, arg1, i, arg2 )
#     _string += ' % '
#     _string += _tail % ( arg3, i ) 

#     print _string

for i in range( 0, 15 ):
    print "lcg%d();" % i 