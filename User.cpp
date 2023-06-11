#include <iostream>
#include <vector>

#include "Security_Algorithms/Encryption_Algorithms/XOR.cpp"
#include "Security_Algorithms/Cipher.cpp"


class User {   

  private:
    std::string firstName;
    std::string lastName;
    std::string email;
    std::string password;
    std::vector<Ciphers> encryptions;

  public:

    std::string getFirstName() {
      return this->firstName;
    }

    std::string getLastName() {
      return this->lastName;
    }

    std::string getEmail() {
      return this->email;
    }

    bool xorEncryptPassword(std::string plaintext, std::string key) {
      //go through this users ciphers list and see if there is alr one for this
      //company/website/login. If there is, tell the user that it is about to be overwritten

      //get cipher text
      std::string ciphertext = xorManager(plaintext, key, false, true);

      //create a ciphers object. Save that POINTER in the cipher list for this user

      //return with success message
    }

    bool xorAdvEncrptPassword(std::string plaintext, std::string key) {
      std::string ciphertext = xorManager(plaintext, key, true, true);
    }


};