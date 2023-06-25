#include <iostream>
#include <vector>

#include "User.hpp"
#include "XOR.hpp"

  //Set the cipher list later
  User::User(std::string firstName, std::string lastName, std::string email, std::string password) {
    this->firstName = firstName;
    this->lastName = lastName;
    this->email = email;
    this->password = password;
  }

  std::string User::getFirstName() {
    return this->firstName;
  }

  std::string User::getLastName() {
    return this->lastName;
  }

  std::string User::getEmail() {
    return this->email;
  }

  std::string User::xorEncryptPasswordDriver(std::string plaintext, std::string key) {
    //go through this users ciphers list and see if there is alr one for this
    //company/website/login. If there is, tell the user that it is about to be overwritten

    //get cipher text
    std::string ciphertext = xorEncryptPassword(plaintext, key);
    //std::cout << "\n\n" << ciphertext << "\n\n" << std::endl;

    //malloc a ciphers object. Save that POINTER in the cipher list for this user

    //return with success message
    return ciphertext;
  }

  
  std::string User::xorDecryptPasswordDriver(std::string ciphertext, std::string key) {

    //turn the cipher text to vector of ints
    std::string num;
    std::vector<int> cipherVect;
    for (int i = 0; i < ciphertext.size(); i++) {
      if (ciphertext.at(i) != ' ') {
        num += ciphertext.at(i);
      } else {
        cipherVect.push_back(stoi(num));
        num = "";
      }
    }

    std::cout << "cipher vect: \n";
    for (int i = 0; i < cipherVect.size(); i++) {
      std::cout << cipherVect.at(i) << " ";
    } 
    //get plaintext text
    std::string plaintext = xorDecryptPassword(cipherVect, key);

    //malloc a ciphers object. Save that POINTER in the cipher list for this user

    //return with success message
    return plaintext;
  }


  std::string User::xorAdvEncryptPasswordDriver(std::string plaintext, std::string key) {
    //go through this users ciphers list and see if there is alr one for this
    //company/website/login. If there is, tell the user that it is about to be overwritten

    //get cipher text
    std::string ciphertext = advancedXorEncryptionPassword(plaintext, key);
    //std::cout << "\n\n" << ciphertext << "\n\n" << std::endl;

    //malloc a ciphers object. Save that POINTER in the cipher list for this user

    //return with success message
    return ciphertext;
  }

  std::string User::xorAdvDecryptPasswordDriver(std::string ciphertext, std::string key) {
    //turn the cipher text to vector of ints
    std::string num;
    std::vector<int> cipherVect;
    for (int i = 0; i < ciphertext.size(); i++) {
      if (ciphertext.at(i) != ' ') {
        num += ciphertext.at(i);
      } else {
        cipherVect.push_back(stoi(num));
        num = "";
      }
    }

    std::cout << "cipher vectf: \n";
    for (int i = 0; i < cipherVect.size(); i++) {
      std::cout << cipherVect.at(i) << " ";
    }
    std::cout << "hereeree\n\n"; 
    //get plaintext text
    std::string plaintext = advancedXorDecryptionPassword(cipherVect, key);

    //malloc a ciphers object. Save that POINTER in the cipher list for this user

    //return with success message
    return plaintext;
  }