#include <iostream>
#include <vector>
#include <exception>
#include <sstream>
#include <fstream>
#include <cstdio>

#include "User.hpp"
#include "XOR.hpp"
/*
TODO

Make a function call to get saved data on log in for a user
Make checks with saved data when making new passwords
Call save data whenever the a user goes out of scope

Throw in more error checking to verify things like name or passwords don't have werid stuff in them.

*/
//Set the cipher list later
User::User(std::string firstName, std::string lastName, std::string email, std::string password, std::string salt) {
  this->firstName = firstName;
  this->lastName = lastName;
  this->email = email;
  this->password = password;
  this->salt = salt;
}

User::User(std::string filename, std::string password) {
  std::ifstream ifs("USERDATA/" + filename + ".cli");
  if (!ifs.is_open()) {
    std::cout << "User not found\n";
    throw USER_NOT_FOUND;
  }
  
  // data safe to be stored as plaintext
  ifs >> firstName;
  ifs >> lastName;
  ifs >> email;
  ifs >> salt;

  // Get ciphers
  std::string buff = "";
  while (ifs.good()) {
    CipherType_t type = XOR;
    std::string loginName = "";
    std::string user_name = "";
    std::string ciphertext = "";
    ifs >> buff;
    type = (CipherType_t) stoi(buff);
    ifs >> loginName;
    ifs >> user_name;

    ifs >> buff;
    while (1) {
      ciphertext += buff + " ";
      ifs >> buff;
      if (buff == "@") {
        break;
      }
    }
    ciphers.push_back({type, loginName, user_name, ciphertext});
    //std::cout << type << "   " << loginName << "     " << ciphertext << std::endl;
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
// this function is not being used
std::string User::xorEncryptPasswordDriver(std::string service_name, std::string plaintext, std::string key) {
  //go through this users ciphers list and see if there is alr one for this
  for (int i = 0; i < ciphers.size(); i++) {
    if (ciphers.at(i).service_name == service_name) {
      throw REPEATED_LOGIN_CREATION;
    }
  }


  //get cipher text
  std::string ciphertext = xorEncryptPassword(plaintext, key);

  //return with success message
  // ciphers.push_back((CipherInfo) {XOR, ciphertext, loginName});
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


std::string User::xorAdvEncryptPasswordDriver(std::string service_name, std::string plaintext, std::string key) {
  //go through this users ciphers list and see if there is alr one for this
  for (int i = 0; i < ciphers.size(); i++) {
    if (ciphers.at(i).service_name == service_name) {
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
// this will overwrite everything alr there
void User::SaveUserData() {
  const char* output_filename = "USERDATA/phijam.cli";
  std::ofstream ofs(output_filename);
  if (!ofs.is_open()) {
    throw DATA_NOT_SAVED;
  }
  ofs << firstName << " " << lastName << " " << email << " " << salt;
  for (int i = 0; i < ciphers.size(); i++) {
    ofs << "\n" << ciphers.at(i).type << " ";
    ofs << ciphers.at(i).service_name << " ";
    ofs << ciphers.at(i).username << "\n";
    ofs << ciphers.at(i).ciphertext << "@";
  }
}

void User::CreateCipher() {
  CipherType_t type;
  std::cout << "Let's create a new cipher\n";
  std::string login_name;
  std::cout << "For what service is this for: ";
  std::cin >> login_name;
  int selection = -1;
  while (selection != 1 && selection != 2 && selection != 3) {
    std::cout << "What type of encryption do you want\n";
    std::cout << "XOR (1)\nAES (2)\nBlowfish (3)\nSelection: ";
    std::cin >> selection;
  }
  if (selection == 1) {
    type = XOR;
  } else if (selection = 2) {
    type = AES;
  } else {
    type = BLOWFISH;
  }
  std::string user_name = "";
  std::cout << "Enter user name: ";
  std::cin >> user_name;
  std::string plaintext;
  std::cout << "Enter password: ";
  std::cin >> plaintext;
  std::string ciphertext = advancedXorEncryptionPassword(plaintext, password.substr(0,5));
  ciphers.push_back((CipherInfo) {type, login_name, user_name, ciphertext});
  SaveUserData();
}

void User::RetrievePassword() {
  std::cout << "Here's a list of saved logins.\n";
  int selection = -1;
  while (selection < 0 || selection > ciphers.size()) {
    for (int i = 0; i < ciphers.size(); i++) {
      std::cout << ciphers.at(i).service_name << " (" << i + 1 << ")\n";
    }
    std::cout << "Selection: ";
    std::cin >> selection;
  }
  selection--; // to make it work like an index
  std::string plaintext = "it didnt work";
  if (ciphers.at(selection).type == XOR) {
    std::cout << "CIPHER TEXT: " << ciphers.at(selection).ciphertext << std::endl;
    std::vector<int> ciphertext;
    std::stringstream iss(ciphers.at(selection).ciphertext);
    int num = -1;
    while (iss >> num) {
      ciphertext.push_back(num);
    }
    plaintext = advancedXorDecryptionPassword(ciphertext, password.substr(0, 5));
  } else {
    std::cout << "That is not yet supported";
  }
  std::cout << "Username: " << ciphers.at(selection).username << std::endl;
  std::cout << "Password: " << plaintext << std::endl;

}

void User::DeleteData() {
  std::cout << "Which account information do you want removed\n";
  for (int i = 0; i < ciphers.size(); i++) {
    std::cout << ciphers.at(i).service_name << " (" << i + 1 << ")\n";
  }
  int selection = 0;
  std::cin >> selection;
  ciphers.erase(ciphers.begin() + --selection);
}
