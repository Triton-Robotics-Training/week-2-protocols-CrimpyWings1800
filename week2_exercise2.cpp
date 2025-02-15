//STARTER 
//THIS EXERCISE IS TO BE DONE IN A GENERIC C++ COMPILER
//https://www.programiz.com/cpp-programming/online-compiler/
//IF YOU HAVE ISSUES WITH THE COMPILER, CONTACT EMBEDDED LEAD
const int BUFFER_SIZE = 98;
const int offset = 1;
#include <iostream>

static unsigned char inputString[] = 
{0x84,0x1d,0x3d,0x74,0x1e,0x3d,0x74,0x1e,
0x3c,0x1e,0xbd,0xb4,0x7c,0x1d,0x1e,0xbd,
0xfd,0x54,0xbc,0x1e,0x7c,0xfd,0xbd,0x14,
0x9d,0xbc,0x15,0x1e,0x7c,0x3d,0x14,0x1d,
0xbc,0x54,0x9f,0x1e,0x3d,0x74,0xdd,0x94,
0x1e,0x3d,0x94,0xdf,0x1e,0xad,0xb4,0x7c,
0x1d,0x1e,0xbd,0xfd,0x54,0xbc,0x1e,0xdc,
0xb4,0xdd,0x1e,0x94,0xfd,0x1e,0x9c,0xbc,
0x7c,0xfd,0x9c,0xbc,0x3e,0x1e,0x1d,0x94,
0x94,0x14,0x74,0x57,0xff,0xff,0x14,0x7d,
0xdd,0xbc,0x74,0x74,0xdd,0xbc,0x74,0x74,
0xdf,0xfc,0x3d,0x94,0x1d,0xb4,0x5c,0xdf,
0x3d,0xfd}; //this test string should output something readable

//puts a character into the output buffer
//remember that nothing will show until you print a newline.
void putc(char c){
    printf("%c", c);
}

//puts a character into the output buffer as hexadecimal
//remember that nothing will show until you print a newline.
void putc_hex(char c){
    printf("0x%2x", (unsigned char)c);
}

//puts a character into the output buffer as binary
//remember that nothing will show until you print a newline.
void putc_bin(char c) {
    for(int i = 0; i < 8; i ++){
        printf("%c", (c>>(7-i) & 1) ? '1' : '0');
    }
}

char move_0(char c) {
    char zeroth_bit = c & 0x01; //isolating the 0 bit
    zeroth_bit = zeroth_bit << 3; // shifting by 3
    return c | zeroth_bit;
}

char move_21(char c) {
    char second_first_bits = ~c;
    second_first_bits = second_first_bits & 0x06;
    second_first_bits = second_first_bits << 5;
    return c | second_first_bits;
}

char move_3(char c) {
    char third_bit = ~c;
    third_bit = third_bit & 0x08;
    third_bit = third_bit << 1;
    return c | third_bit;
}

int main(void) {
    
    char x = 0x01;
    putc_bin(x);
    putc('\n');
    
    //char moved_zeroth = move_0(x);
    //putc_bin(moved_zeroth);
    //putc('\n');
    
    //char moved_second_first = move_21(x);
    
    //char moved_third = move_3(x);
    //putc_bin(moved_third);
    //putc('\n');
    
    //putc_bin(moved_second_first | moved_third | moved_zeroth);
    //putc('\n');

    //CODE GOES HERE 

    putc('\n');
}
