#include <iostream>
#include <vector>

#include "Cipher.hpp"

Cipher::Cipher (std::string loginName, CipherTypes cipherName, std::string key, int zeros) {
  //call out setters rather than manually assigning these values
  //because the setters should conduct data validation.
}

std::string Cipher::getLoginName() {
  return this->loginName;
}

CipherTypes Cipher::getCipherName() {
  return this->cipherName;
}

std::string Cipher::getKey() {
  return this->key;
}

int Cipher::getNumPaddedZeros() {
  return this->numPaddedZeros;
}

//Setters
bool Cipher::setLoginName(std::string newLoginName) {
  if (newLoginName.size() > MAX_LOGIN_NAME_SIZE) {
    return false;
  }

  this->loginName = newLoginName;
  return true;
}

bool Cipher::setCipherName(CipherTypes newCipherName) {
  if (newCipherName < 0 || newCipherName >= NUM_CIPHERS) {
    return false;
  }

  this->cipherName = newCipherName;
  return true;
}

bool Cipher::setKey(std::string newKey) {
  //TODO: INPUT VALIDATION BASED OFF OF ALGO TYPE, some encryption
  //type will only allow certain size key. 

  this->key = newKey;
  return true;
}
