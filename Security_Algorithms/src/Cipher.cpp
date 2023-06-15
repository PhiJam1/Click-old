#include <iostream>
#include <vector>

#define MAX_LOGIN_NAME_SIZE 50

enum CipherTypes {
  XOR,
  BLOWFISH,
  AES,
  SHA
};

class Ciphers {   

  private:
    std::string loginName; //Like a company name
    std::string cipherName; //Maybe we change this to an enum?
    std::string key;
    int numPaddedZeros; //Just put in -1 if not applicable for this cipher

  public:
    std::string getLoginName() {
      return this->loginName;
    }

    std::string getCipherName() {
      return this->cipherName;
    }
    std::string getKey() {
      return this->key;
    }

    int getNumPaddedZeros() {
      return this->numPaddedZeros;
    }

    //Setters
    bool setLoginName(std::string newLoginName) {
      if (newLoginName.size() > MAX_LOGIN_NAME_SIZE) {
        return false;
      }
      this->loginName = newLoginName;
      return true;
    }

    bool setCipherName(std::string newCipherName) {
      //def make this into an enum


    }

    bool setKey(std::string newKey) {
      //TODO: INPUT VALIDATION BASED OFF OF ALGO TYPE

      this->key = newKey;
      return true;
    }







};