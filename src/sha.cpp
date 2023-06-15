#include <iostream>
#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include <stdint.h>
#if 0
#include "sha.h"

//Inital register values
unsigned int h0 = 0x6a09e667;
unsigned int h1 = 0xbb67ae85;
unsigned int h2 = 0x3c6ef372;
unsigned int h3 = 0xa54ff53a;
unsigned int h4 = 0x510e527f;
unsigned int h5 = 0x9b05688c;
unsigned int h6 = 0x1f83d9ab;
unsigned int h7 = 0x5be0cd19;



/*
    Function that will grab 512 bit chuncks from a file.
    It will return false when the file has been fully parsed.
    
    blockPtr is a pointer to a char array that will hold the raw
    message data and padding.

    blockNumber is a counter of how many 512 bit blocks have been parsed.
    It is used to move the file pointer to the correct location and to
    determine the length of the total message.

*/
bool get512Block(unsigned char *blockPtr, int blockNumber, std::ofstream& debugF) {
    std::ifstream inFile;
    inFile.open("plaintext.txt");


    if (!inFile.is_open()) {
        std::cout << "Error on open...Data retention may be incomplete or empty\n";
        return false;
    }

    //Move to the next block, 64 chars = 512 bits.
    inFile.seekg(64 * blockNumber, std::ios::cur);

    char c = 'a';
    int i;
    for (i = 0; i < 64; i++) {

        // If this is the last block and not a multiple of 512
        if (inFile.eof()) {
            break;
        }

        inFile.get(c);
        blockPtr[i] = c;
    }

    //This block is full. No padding needed
    if (i == 64) {
        return true;
    }

    i -= 1; //it grabs the last char twice for some reason
    unsigned long length = (unsigned long) (i) * (sizeof(char) * 8) * (blockNumber + 1); //in bits
    //unsinged long is 4 bytes its max value can support files up to 5mb I THINK.

    //append the 1
    blockPtr[i++] = (char) 0x80;

    //at this point, we will have a max of 448 bits

    //if we are not at the max, add enough bits, that we get to 448 bits.
    //remember, bits stored will always be a multipe of 8.

    //pad, I'm adding 0s as chars, so each should be 0000 0000
    while (i < 56) { //don't do <= bc i starts at 0
        blockPtr[i] = (char) 0;
        i++;
    }
    
    //now the message should have 448 bits... append the length (of bits)


    while (i < 60) {
        blockPtr[i++] = (char) 0;
    }

    //massive chance that this does some nonsense 
    blockPtr[60] = length >> 24;
    blockPtr[61] = (length << 8) >> 24;;
    blockPtr[62] = (length << 16) >> 24;
    blockPtr[63] = (length << 24) >> 24;

    //debug code
    debugF << "512 bit block with '1' appended, padding, and 64 bit length value\n";
    for (int j = 0; j < 64; j++) {
        debugF << std::bitset<8 * sizeof(char)>(blockPtr[j]) << "";
        if ((j + 1) % 4 == 0) {
            debugF << "\n";
        }
    }


    inFile.close();
    return true;
}

/*
    This function will take the padded raw data array and create the 32 bit
    message schedule.
    msgSchdule is a pointer to the int array that will hold each 32 bit word.
    msgBlock is the original raw/padded data.
*/

void createSchedule (unsigned int *msgSchedule, unsigned char *msgBlock, std::ofstream& debugF) {
    //sizeof(int) = 4, so that is 32 bits.
    /*
        We need to create 32 bit 'words' to fill up the first 16 indexes of the message
        schedule. For that, we just take the message block in 32 bit chuncks. Each index
        in the block array is a char. The schedule is an int array because an int = 32 bits.
        That means we need to append the bits of 4 indexes of the block array for one of the
        schedule array.
        For example, if the first four indexes of the block array is:
        block[0] = 01010100
        block[1] = 01101000
        block[2] = 01101001
        block[3] = 01110011
        We need append these together for a 32 bit word. Too do that, I use a couple
        bitwise operations. Here is a visual:
          01010100 00000000 00000000 00000000 24 bit left shift
        + 00000000 01101000 00000000 00000000 16 bit left shift
        + 00000000 00000000 01101001 00000000 8 bit left shift
        + 00000000 00000000 00000000 01110011 add up all these values

        = schedule[0] = 01010100011010000110100101110011

    */

    int i = 0;
    int a = 0;
    while (i < 64) {
        msgSchedule[a++] = (msgBlock[i++] << (8 * 3)) + (msgBlock[i++] << (8 * 2)) +
                            (msgBlock[i++] << (8 * 1)) +  msgBlock[i++];
    }

    /*  first 16 indexes of messageBlock are full
        The remain 16-63 indexes are fill according 
        to the following algorithm:
        T[i] = T[i - 16] + SIG0(T[i - 15]) + T[i - 7] + SIG1(T[i - 2])
        SIG0 and SIG1 are #defined macros found in sha.h
    */
    for (i = 16; i < 64; i++) {
        msgSchedule[i] = msgSchedule[i - 16] +
                         SIG0(msgSchedule[i - 15]) +
                         msgSchedule[i - 7] +
                         SIG1(msgSchedule[i - 2]);
        
        //debug info
        if (i == 16) {
            // #define SIG0(x) (ROTRIGHT(x, 7) ^ ROTRIGHT(x, 18) ^ ((x) >> 3))

            debugF << "ROTRIGHT(messageBlock[i - 15], 7): " << std::bitset<8 * sizeof(int)>(ROTRIGHT(msgSchedule[i - 15], 7)) << "\n";
            debugF << "ROTRIGHT(messageBlock[i - 15], 18): " << std::bitset<8 * sizeof(int)>(ROTRIGHT(msgSchedule[i - 15], 18)) << "\n";
            debugF << "Right shift(messageBlock[i - 15], 3): " << std::bitset<8 * sizeof(int)>(msgSchedule[i - 15] >> 3) << "\n";

            debugF << "SIG0 on i = 16:  ";
            debugF << std::bitset<8 * sizeof(int)>(SIG0(msgSchedule[i - 15])) << "\n\n";
           
        }
    }

    // debug info
    debugF << "\nmessage schedule\n";
    for (int j = 0; j < 64; j++)
    {
        debugF << "W[" << j << "] = ";
        debugF << std::bitset<8 * sizeof(int)>(msgSchedule[j]) << "\n";
    }
}


/*
    This function will take a given message schedule
    and preform the compression operation and update the
    registers.
    msgSchedule is the message schedule developed in createSchedule()

*/
void shaTransform(unsigned int * msgSchedule) {
    
    //Set up the working variables
    unsigned int t1;
    unsigned int t2;

    unsigned int a = h0;
    unsigned int b = h1;
    unsigned int c = h2;
    unsigned int d = h3;
    unsigned int e = h4;
    unsigned int f = h5;
    unsigned int g = h6;
    unsigned int h = h7;

    /*
        This is the main compression function. It feeds in input
        from the round contants (k, found in sha.h), the regesiters,
        and the data from the schedule. It is manipulated according as
        shown.
        EP0, EP1, CH, and MAJ are #defined macros that preform bitwise operations.
    */
    for (int i = 0; i < 64; ++i)
    {
        t1 = h + EP1(e) + CH(e, f, g) + k[i] + msgSchedule[i];
        t2 = EP0(a) + MAJ(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
    }

    //Update the shift registers
    h0 += a;
    h1 += b;
    h2 += c;
    h3 += d;
    h4 += e;
    h5 += f;
    h6 += g;
    h7 += h;
    

}


int main() {
    //64 chars = 512 bits
    //This is the size of one sha256 message block
    unsigned char block[64];
    std::ofstream debugLogFP;
    debugLogFP.open("debug.txt");

    //get512block returns true while there is more data in the file
    get512Block(block, 0, debugLogFP);

    //This is the message schedule array that will hold the 32 bit words.
    // sizeof(int) = 4 bytes = 32 bits
    unsigned int msgSchedule[64];
    createSchedule(msgSchedule, block, debugLogFP);
    shaTransform(msgSchedule);

    //The final hash is the concatenation of the final values of the register variables
    printf("%02x%02x%02x%02x%02x%02x%02x%02x\n", h0, h1, h2, h3, h4, h5, h6, h7);


    debugLogFP.close();
    return 0;
}

#endif