#include <iostream>
#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include <stdint.h>

#include "sha.h"

int a = 9;

//Inital hash values
unsigned int h0 = 0x6a09e66;
unsigned int h1 = 0xbb67ae85;
unsigned int h2 = 0x3c6ef372;
unsigned int h3 = 0xa54ff53a;
unsigned int h4 = 0x510e527f;
unsigned int h5 = 0x9b05688c;
unsigned int h6 = 0x1f83d9ab;
unsigned int h7 = 0x5be0cd19;


//Initialize array of round constants:
unsigned int k[] = { 0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 
            0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 
            0x9bdc06a7, 0xc19bf174,0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 
            0x4a7484aa, 0x5cb0a9dc, 0x76f988da,0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
            0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,0x27b70a85, 0x2e1b2138, 0x4d2c6dfc,
            0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
            0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,0x19a4c116, 
            0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
            0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7,
            0xc67178f2};

/*
    This function grab a 512 bit (64 char) block of the message
    and a index for the block number. It will place that block
    to where the first arg points to. It will return true as long
    as there is more data to grab. It will pad data if needed.

    Note, blockPtr must point to a char array of length = 64

    ok so what I wrote above is wrong. Every block will get
    atleast 7 bits of padding

    this is getting very complicated. I'm going to do an inital
    draft of this for the case that we are inputing just one block
*/
bool get512Block(char *blockPtr, int blockNumber) {
    std::ifstream inFile;
    inFile.open("plaintext.txt");


    if (!inFile.is_open()) {
        std::cout << "Error on open...Data retention may be incomplete or empty\n";
        return false;
    }

    //Move to the next block, 64 chars = 512 bits. 
    inFile.seekg(64 * blockNumber, std::ios::cur);

    /*
        512 = msg + L + 8 + padding
        L is a 64 bit int that represents the length of the msg
        8 is for appending a 0x80 (this is 10000000) - appending the 1 bit
        pad to get it the rest of the way
        So that means a max msg size of 440 bits which is 55 chars (440 / 8, 8 bits in one char).

        pretty good: https://www.rfc-editor.org/rfc/rfc6234#page-8
        Equation:
        ( L + 1 + K ) mod 512 = 448.
        Then add in the 64 bit integer representing the length of L
        Also, that 1 bit will be added in as an 8 bit number (10000000, 0x80). So that is why
        L + k = 440 for small messages. 
    */
    char c = 'a';
    int i;
    for (i = 0; i < (440 / (sizeof(char) * 8)); i++) {
        // to get the number of chars we can read in for 440 bits
        //(440 / (sizeof(char) * 8)) should almost always equal 55, but just to be safe.

        // If this is the last block and not a multiple of 512
        if (inFile.eof()) {
            i++;
            break;
        }

        inFile.get(c);
        blockPtr[i] = c;
    }
    unsigned short length =(unsigned short) i * sizeof(char) * 8; //in bits

    //append the 1
    blockPtr[i++] = (char) 0x80;

    //at this point, we will have a max of 448 bits

    //if we are not at the max, add enough bits, that we get to 448 bits.
    //remember, bits stored will always be a multipe of 8.

    //pad, I'm adding 0s are chars, so each should be 0000 0000
    while (i < 56) { //don't do <= bc i starts at 0
        blockPtr[i] = (char) 0;
        i++;
    }
    
    //now the message should have 448 bits... append the length (of bits)
    //there are 64 bits to fill. length is a short and only needs 2. so that's
    //6 bytes = 48 bits to fill with 0s.

    while (i < 62) {
        blockPtr[i++] = (char) 0;
    }


    blockPtr[62] = length >> 8;
    blockPtr[63] = length << 8 >> 8;



    inFile.close();
    return inFile.eof();
}


int main() {
    char block[64]; //64 chars = 512 bits
    for (int i = 0; get512Block(block, i); i++) {
        std::cout << "Block " << (i + 1) << std::endl;
        for (int i = 0; i < 64; i++) {
            std::cout << block[i];
        }
        std::cout << "\n";
    }

    std::cout << a;
    return 0;
}