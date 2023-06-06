#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>


// Subkeys initialisation with digits of pi.
int P[18][4] = { {0x24, 0x3f, 0x6a, 0x88}, {0x85, 0xa3, 0x08, 0xd3}, {0x13, 0x19, 0x8a, 0x2e}, 
            {0x03, 0x70, 0x73, 0x44}, {0xa4, 0x09, 0x38, 0x22}, {0x29, 0x9f, 0x31, 0xd0}, 
            {0x08, 0x2e, 0xfa, 0x98}, {0xec, 0x4e, 0x6c, 0x89}, {0x45, 0x28, 0x21, 0xe6}, 
            {0x38, 0xd0, 0x13, 0x77}, {0xbe, 0x54, 0x66, 0xcf}, {0x34, 0xe9, 0x0c, 0x6c}, 
            {0xc0, 0xac, 0x29, 0xb7}, {0xc9, 0x7c, 0x50, 0xdd}, {0x3f, 0x84, 0xd5, 0xb5}, 
            {0xb5, 0x47, 0x09, 0x17}, {0x92, 0x16, 0xd5, 0xd9}, {0x89, 0x79, 0xfb, 0x1b} }; 


//This will take in a user's key and append '!'s until
//it's size is a multiple of 32 bits.
// This is some 1 am type scary code. A likely source for bugs. 
void getKey(char *key) {
    for (int i = 0; i < 18; i++) {
        int j = i % 2 == 0 ? 0 : 4;
        P[i][0] ^= key[j++];
        P[i][1] ^= key[j++];
        P[i][2] ^= key[j++];
        P[i][3] ^= key[j++];
    }
}

/*
    This function will read in data in 64 bit
    chuncks and return true while there is more
    data to be read. When padding is needed, it will
    set the number of padded values to the padding variable.
*/

//does not pad yet


bool getPlaintextBlock(unsigned char *blockPtr, int blockNumber, int padding) {
    std::ifstream inFile;
    inFile.open("plaintext.txt");


    if (!inFile.is_open()) {
        std::cout << "Error on open...Data retention may be incomplete or empty\n";
        return false;
    }

    //Move to the next block, 8 chars = 64 bits.
    inFile.seekg(8 * blockNumber, std::ios::cur);

    char c = 'a';
    int i;
    for (i = 0; i < 8; i++) {

        // If this is the last block and not a multiple of 512
        if (inFile.eof()) {
            break;
        }

        inFile.get(c);
        blockPtr[i] = c;
    }
    return false;
}



void encrypt(unsigned char *block) {
    for (int i = 0; i < 16; i++) {
        //create a left and right
        unsigned char left[] = {block[0], block[1], block[2], block[3]};
        unsigned char right[] = {block[4], block[5], block[6], block[7]};
         
        //left = left ^ P[i];
        for (int j = 0; j < 4; j++) {
            left[j] ^= P[i][j];
        }

        //temp = function(left)



        //right  = temp ^ right
        for (int j = 0; j < 4; j++) {
            //right[j] ^= temp[j];
        }

        
        //swap
        unsigned char mid[4];
        for (int j = 0; j < 4; j++) {
            mid[j] = left[j];
            left[j] = right[j];
            right[j] = mid[j];
        }
    }

}

void f(std::string plaintext) {
    
}

//currently only works for 64 bits (8 char)
int main() {
    char key[8]; //8 char = 8 bytes = 64 bits
    std::cout << "Key must be between 8 char long\n";
    std::cout << "Enter key: \n";
    std::cin >> key;
    getKey(key);

    unsigned char block[8];
    int padding = 0;
    getPlaintextBlock(block, 0, padding);

    encrypt(block);


}