#include <iostream>
#include <vector>
#include <exception>
#include <fstream>
#include "User.hpp"
#include "XOR.hpp"
/*
TODO

Make a function to get saved data on log in for a user
Make checks with saved data when making new passwords

Throw in more error checking to verify things like name or passwords don't have werid stuff in them.

*/
//Set the cipher list later
User::User(std::string firstName, std::string lastName, std::string email, std::string password std::string salt) {
  this->firstName = firstName;
  this->lastName = lastName;
  this->email = email;
  this->password = password;
  this->salt = salt;
}

User::User(std::string filename, std::string password) {
  std::ifstream ifs("USERDATA/" + filename + "cli");
  if (!ifs.is_open()) {
    throw USER_NOT_FOUND;
  }
  
  std::string delm;
  ifs >> delm;
  if (delm != PERSONAL_INFO_START_DELIMITER) {
    throw CURRUPT_FILE;
  }
  ifs >> this-> firstName;
  ifs >> this-> lastName;
  ifs >> this-> email;
  ifs >> delm;
  if (delm != PERSONAL_INFO_END_DELIMITER) {
    throw CURRUPT_FILE;
  }
  while (delm != FILE_ENDING_DELIMITER) {
    int type = 0;
    std::string ciphertextTemp;
    std::string keyTemp;
    std::string loginNameTemp;

    ifs >> type;
    ifs >> ciphertextTemp;
    ifs >> keyTemp;
    ifs >> loginNameTemp;
    ifs >> delm;
    if (delm != CIPHER_STRUCT_ENDING_DELIMITER) {
      throw CURRUPT_FILE;
    }
    ciphers.push_back((CipherInfo) {(CipherType_t) type, ciphertextTemp, keyTemp, loginNameTemp});
    ifs >> delm;
  }

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

std::string User::xorEncryptPasswordDriver(std::string loginName, std::string plaintext, std::string key) {
  //go through this users ciphers list and see if there is alr one for this
  for (int i = 0; i < ciphers.size(); i++) {
    if (ciphers.at(i).loginName == loginName) {
      throw REPEATED_LOGIN_CREATION;
    }
  }


  //get cipher text
  std::string ciphertext = xorEncryptPassword(plaintext, key);

  //return with success message
  ciphers.push_back((CipherInfo) {XOR, ciphertext, key, loginName});
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

  //get plaintext text
  std::string plaintext = xorDecryptPassword(cipherVect, key);

  //malloc a ciphers object. Save that POINTER in the cipher list for this user

  //return with success message
  return plaintext;
}


std::string User::xorAdvEncryptPasswordDriver(std::string loginName, std::string plaintext, std::string key) {
  //go through this users ciphers list and see if there is alr one for this
  for (int i = 0; i < ciphers.size(); i++) {
    if (ciphers.at(i).loginName == loginName) {
      throw REPEATED_LOGIN_CREATION;
    }
  }

  //get cipher text
  std::string ciphertext = advancedXorEncryptionPassword(plaintext, key);

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

  //get plaintext text
  std::string plaintext = advancedXorDecryptionPassword(cipherVect, key);


  //return with success message
  return plaintext;
}

void User::SaveUserData() {
  std::string output_filename = "USERDATA/" + email + ".cli";
  std::ofstream ofs(output_filename);
  if (!ofs.is_open()) {
    throw DATA_NOT_SAVED;
  }
  ofs << PERSONAL_INFO_START_DELIMITER;
  ofs << firstName << " " << lastName << " " << email << "\n";
  ofs << PERSONAL_INFO_END_DELIMITER;
  for (int i = 0; i < ciphers.size(); i++) {
    ofs << ciphers.at(i).type << "\n";
    ofs << ciphers.at(i).ciphertext << "\n";
    ofs << ciphers.at(i).key << "\n";
    ofs << ciphers.at(i).loginName << "\n";
    ofs << CIPHER_STRUCT_ENDING_DELIMITER;
  }
  ofs << FILE_ENDING_DELIMITER;


}