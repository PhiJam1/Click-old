#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include "blowfish.hpp"
/*
    Run this program while in the 'click' directory.
*/
int main() {
    // mainT();
    // return 0;
    std::string plaintext = "wepassworddddd";
    std::string key = "keyy"; // must be 4 char, 32 bits

    std::string ciphertext = EncryptDriverPassword(plaintext, key);
    std::cout << "Cipher text: " << ciphertext << std::endl;
    std::string plain = DecryptDriverPassword(ciphertext, key);
    std::cout << "Plain: " << plain << std::endl;
    return 0;

}
