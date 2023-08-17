#ifndef BLOWFISH_H
#define BLOWFISH_H

#include <string>


std::string f(std::string plaintext);

void generateSubKeys(int *pBoxes);

void encrypt(std::string plaintext);

std::string EncryptDriverPassword(std::string plaintext, std::string key);

std::string DecryptDriverPassword(std::string ciphertext, std::string key);

std::string GetHexString(std::string str);

std::string GetStrFromHex(std::string str);

void KeyCleanUp();

void mainT();

#endif