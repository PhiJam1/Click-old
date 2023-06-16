#include <iostream>
#include <vector>

#include "User.hpp"

  //Set the cipher list later
  User::User(std::string firstName, std::string LastName, std::string email, std::string password) {
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

  bool xorEncryptPassword(std::string plaintext, std::string key) {
    //go through this users ciphers list and see if there is alr one for this
    //company/website/login. If there is, tell the user that it is about to be overwritten

    //get cipher text
    //std::string ciphertext = xorManager(plaintext, key, false, true);

    //create a ciphers object. Save that POINTER in the cipher list for this user

    //return with success message
    return true;
  }

  bool xorAdvEncrptPassword(std::string plaintext, std::string key) {
    ///std::string ciphertext = xorManager(plaintext, key, true, true);
    return true;
  }