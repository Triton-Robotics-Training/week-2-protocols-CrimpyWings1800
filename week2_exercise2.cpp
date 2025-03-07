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
void putc(char c) {
    printf("%c", c);
}

//puts a character into the output buffer as hexadecimal
//remember that nothing will show until you print a newline.
void putc_hex(char c) {
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
    char zeroth_bit = c & 0b00000001; //isolating the 0 bit
    char shifted_bits = zeroth_bit << 3; // shifting by 3
    return 0b00001000 & shifted_bits;
}

char move_21(char c) {
    char inverted_bits = ~c & 0b00000110; //inverting and isolating
    char shifted_bits = inverted_bits << 5; // shifting by 6
    //char cleared_c = c & 0b00111111;
    return 0b11000000 & shifted_bits;
}

char move_3(char c) {
    char inverted_bit = ~c &0b00001000; // invertign and isolating
    char shifted_bit = inverted_bit << 1; //shifting by 1
    return 0b00010000 & shifted_bit;
}

char move_4(char c) {
    char fourth_bit = c & 0b00010000; //isolating fourth bit
    char shifted_bit = fourth_bit << 1; // shifting by 1
    return 0b00100000 & shifted_bit;
}

char move_765(char c) {
    char seventh_sixth_fifth_bits = c & 0b11100000; //isolating front three
    char shifted_bits = seventh_sixth_fifth_bits >> 5; //shifting to the back

    char cleared_bits = shifted_bits & 0b00000111; //"saving" the last three

    return cleared_bits;
}

int main(void) {
    int size = sizeof(inputString) / sizeof(inputString[0]);
    char outputString[size]; // creating array to store charcters
    char bit0; //holds decrypted 0th bit
    char bits21; // holds decrypted 1st and 2nd bits
    char bit3; // holds decrypted 3rd bit
    char bit4; // holds decrypted 4th bit
    char bits765; //holds decrypted front bits
    
    for (int i = 0; i < size; i++) {
        bit0 = move_0(inputString[i]); //decrypting each character
        bits21 = move_21(inputString[i]);
        bit3 = move_3(inputString[i]);
        bit4 = move_4(inputString[i]);
        bits765 = move_765(inputString[i]);
        outputString[i] = bit0 | bits21 | bit3 | bit4 | bits765; //combining all of them together
        putc(outputString[i]); // printing result
    }
    putc('\n');
}
