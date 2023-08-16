#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include "blowfish.hpp"
/*
    Run this program while in the 'click' directory.
*/
int main() {
    std::string plaintext = "password";
    std::string key = "keyy"; // must be 4 char, 32 bits

    std::string ciphertext = EncryptDriverPassword(plaintext, key);
    std::cout << "Cipher text: " << ciphertext << std::endl;
    return 0;

}
