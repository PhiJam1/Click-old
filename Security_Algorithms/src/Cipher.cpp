#include <iostream>
#include <vector>

#define MAX_LOGIN_NAME_SIZE 50
#define NUM_CIPHERS 4
enum CipherTypes {
  XOR,
  BLOWFISH,
  AES,
  SHA
};

class Ciphers {   

  private:
    std::string loginName; //Like a company name
    CipherTypes cipherName; // Maybe we change this to an enum?
    std::string key;
    int numPaddedZeros; //Just put in -1 if not applicable for this cipher

  public:
    std::string getLoginName() {
      return this->loginName;
    }

    CipherTypes getCipherName() {
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

    bool setCipherName(CipherTypes newCipherName) {
      if (newCipherName < 0 || newCipherName >= NUM_CIPHERS) {
        return false;
      }

      this->cipherName = newCipherName;
    }

    bool setKey(std::string newKey) {
      //TODO: INPUT VALIDATION BASED OFF OF ALGO TYPE

      this->key = newKey;
      return true;
    }







};