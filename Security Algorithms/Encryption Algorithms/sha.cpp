#include <iostream>
#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include <stdint.h>

#include "sha.h"

//Inital hash values
unsigned int h0 = 0x6a09e66;
unsigned int h1 = 0xbb67ae85;
unsigned int h2 = 0x3c6ef372;
unsigned int h3 = 0xa54ff53a;
unsigned int h4 = 0x510e527f;
unsigned int h5 = 0x9b05688c;
unsigned int h6 = 0x1f83d9ab;
unsigned int h7 = 0x5be0cd19;



// This only works for one block rn (that is 55 characters)
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

void createSchedule (unsigned int *messageBlock, unsigned char *block, std::ofstream& debugF) {
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
        messageBlock[a++] = (block[i++] << (8 * 3)) +
                            (block[i++] << (8 * 2)) +
                            (block[i++] << (8 * 1)) +  
                            block[i++];
    }

    //first 16 indexes of messageBlock are fill. Now fill up the rest
    for (i = 16; i < 64; i++) {
        unsigned int s0 = ROTRIGHT(messageBlock[i - 15], 7) ^ ROTRIGHT(messageBlock[i - 15], 18) ^ (messageBlock[i - 15] >> 3);
        unsigned int s1 = ROTRIGHT(messageBlock[i - 2], 17) ^ ROTRIGHT(messageBlock[i - 2], 19) ^ (messageBlock[i - 2] >> 10);
        messageBlock[i] = messageBlock[i - 16] + s0 + messageBlock[i - 7] + s1;
    }

    // debug code
    debugF << "\nmessage schedule\n";
    for (int j = 0; j < 64; j++)
    {
        debugF << std::bitset<8 * sizeof(int)>(messageBlock[j]) << " ";
        if ((j + 1) % 4 == 0)
        {
            debugF << "\n";
        }
    }
}

void shaTransform(unsigned int * msgSch) {
    unsigned int a = h0;
    unsigned int b = h1;
    unsigned int c = h2;
    unsigned int d = h0;
    unsigned int e = h4;
    unsigned int f = h5;
    unsigned int g = h6;
    unsigned int h = h7;

    for (int i = 0; i < 64; i++) {
        unsigned int s1 = ROTRIGHT(e, 6) ^ ROTRIGHT(e, 11) ^ ROTRIGHT(e, 25);
        unsigned int ch = (e & f) ^ ((~e) & g);
        unsigned int temp1 = h + s1 + ch + k[i] + msgSch[i];
        unsigned int s0 = ROTRIGHT(a, 2) ^ ROTRIGHT(a, 13) ^ ROTRIGHT(a, 22);
        unsigned int maj = (a & b) ^ (a & c) ^ (b & c);
        unsigned int temp2 = s0 + maj;
        h = g;
        g = f;
        f = e;
        e = d + temp1;
        d = c;
        c = b;
        b = a;
        a = temp1 + temp2;

        h0 = h0 + a;
        h1 = h1 + b;
        h2 = h2 + c;
        h3 = h3 + d;
        h4 = h4 + e;
        h5 = h5 + f;
        h6 = h6 + g;
        h7 = h7 + h;


    }
    std::cout << h0 << h1 << h2 << h3 << h4 << h5 << h6 << h7 << std::endl;

}


int main() {
    unsigned char block[64]; //64 chars = 512 bits
    std::ofstream debugLogFP;
    debugLogFP.open("debug.txt");

    //get512block returns true while there are more block to get
    get512Block(block, 0, debugLogFP);


    unsigned int messageSch[64];
    createSchedule(messageSch, block, debugLogFP);
    shaTransform(messageSch);

    //so there three function would be called until we run out of data. then print out the inital h values
    debugLogFP.close();
    return 0;
}