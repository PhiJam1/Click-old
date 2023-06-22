#ifndef XOR_H
#define XOR_H

#include <iostream>
#include <string>

std::string xorEncryptPassword(std::string plaintext, std::string key);
std::string xorDecryptPassword(std::vector<int> ciphertext, std::string key);
std::string advancedXorDecryptionPassword(std::vector<int> ciphertext, std::string key);
std::string advancedXorEncryptionPassword(std::string plaintext, std::string key);


#endif /* XOR_H */
