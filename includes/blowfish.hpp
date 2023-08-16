#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>


void f(std::string plaintext);

void generateSubKeys(int *pBoxes);

void encrypt(std::string plaintext);

void f(unsigned char *);

std::string EncryptDriverPassword(std::string plaintext, std::string key);

std::string GetHexString(std::string str);

#endif