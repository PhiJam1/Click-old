#include <iostream>
#include <vector>
#include <exception>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <sqlite3.h>

#include "User.hpp"
#include "XOR.hpp"
#include "blowfish.hpp"

int User::SetCiphers(char ** argv) {
  this->ciphers.push_back((CipherInfo) {(CipherType_t) std::stoi(argv[0]), argv[1], argv[2], argv[3]});
  return 0;

}
int SetCiphersCallBack(void* data, int argc, char** argv, char** /* azColName */) {  
  User * obj = static_cast<User *>(data);
  return obj->SetCiphers(argv);
}

// This constructor is used for new users
User::User(std::string firstName, std::string lastName, std::string email, std::string password, std::string salt) {
  this->firstName = firstName;
  this->lastName = lastName;
  this->email = email;
  this->password = password;
  this->salt = salt;

  // get ciphers (if any) from the database
  sqlite3 * db;
  int rc = sqlite3_open("ciphers.db", &db);
  if (rc) {
    std::cout << "Error opening up user database\n";
    return;
  }
  std::string query = "SELECT type, service, username, ciphertext from " + this->email + ";";
  rc = sqlite3_exec(db, query.c_str(), SetCiphersCallBack, this, 0);
  sqlite3_close(db);
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

// this will overwrite everything alr there
void User::SaveUserData() {
  // open the database
  sqlite3 * db;
  int rc = sqlite3_open("USERDATA/ciphers.db", &db);
  if (rc) {
      std::cout << "Error opening the ciphers database\n";
      return;
  }
  // delete everything in this user's table so we can overwrite all the data
  
  std::string dropTableQuery = "DROP TABLE IF EXISTS " + this->email + ";";
  rc = sqlite3_exec(db, dropTableQuery.c_str(), 0, 0, 0);

  // recreate the table
  std::string create_table = "CREATE TABLE IF NOT EXISTS " + this->email + " (type TEXT, service_name TEXT, username TEXT, ciphertext TEXT);";
  rc = sqlite3_exec(db, create_table.c_str(), 0, 0, 0);
  if (rc != SQLITE_OK) {
    std::cout << "Error creating creds table\n";
    sqlite3_close(db);
    return;
  }

  for (int i = 0; i < ciphers.size(); i++) {
    std::string insert = "INSERT INTO " + this->email + " (type, service_name, username, ciphertext) VALUES (" +
                        "'" + std::to_string(ciphers.at(i).type) + "', " +
                        "'" + ciphers.at(i).service_name + "', " +
                        "'" + ciphers.at(i).username + "', " +
                        "'" + ciphers.at(i).ciphertext + "');";
    rc = sqlite3_exec(db, insert.c_str(), 0, 0, 0);
    std::cout << insert << std::endl;
    if (rc != SQLITE_OK) std::cout << sqlite3_errmsg(db) << std::endl;
  }
  sqlite3_close(db);
}

void User::CreateCipher() {
  CipherType_t type;
  std::cout << "Let's create a new cipher\n";
  std::string login_name;
  std::cout << "For what service is this for: ";
  std::cin >> login_name;
  int selection = -1;
  while (selection != 1 && selection != 2) {
    std::cout << "What type of encryption do you want\n";
    std::cout << "XOR (1)\nBlowfish (2)\nSelection: ";
    std::cin >> selection;
  }
  if (selection == 1) {
    type = XOR;
  } else {
    type = BLOWFISH;
  }
  std::string user_name = "";
  std::cout << "Enter user name: ";
  std::cin >> user_name;
  std::string plaintext;
  std::cout << "Enter password: ";
  std::cin >> plaintext;
  std::string ciphertext = "";
  if (type == XOR) {
    ciphertext = advancedXorEncryptionPassword(plaintext, password.substr(0,5));
  } else if (type == BLOWFISH) {
    ciphertext = EncryptDriverPassword(plaintext, password.substr(0, 4)); // should rename that function
  } 
  ciphers.push_back((CipherInfo) {type, login_name, user_name, ciphertext});
  SaveUserData();
}

void User::RetrievePassword() {
  if (ciphers.size() == 0) {
    std::cout << "You have no saved ciphers\n";
    return;
  }
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
  std::string plaintext = "it didn't work";
  if (ciphers.at(selection).type == XOR) {
    std::vector<int> ciphertext;
    std::stringstream iss(ciphers.at(selection).ciphertext);
    int num = -1;
    while (iss >> num) {
      ciphertext.push_back(num);
    }
    plaintext = advancedXorDecryptionPassword(ciphertext, password.substr(0, 5));
  } else if (ciphers.at(selection).type == BLOWFISH) {
    plaintext = DecryptDriverPassword(ciphers.at(selection).ciphertext, password.substr(0, 4));
  }
  std::cout << "Username: " << ciphers.at(selection).username << std::endl;
  std::cout << "Password: " << plaintext << std::endl;
}

void User::DeleteData() {
  if (ciphers.size() == 0) {
    std::cout << "You have no saved ciphers" << std::endl;
    return;
  }
  std::cout << "Which account information do you want removed\n";
  for (int i = 0; i < ciphers.size(); i++) {
    std::cout << ciphers.at(i).service_name << " (" << i + 1 << ")\n";
  }
  int selection = 0;
  std::cin >> selection;
  ciphers.erase(ciphers.begin() + --selection);
}



void User::EncryptFile() {
  std::string plaintext_filename;
  std::string key;
  // get the file with the plain text
  std::cout << "File name/path: ";
  std::cin >> plaintext_filename;
  std::cout << "Key: ";
  std::cin >> key;
  advancedXorEncryptionFile(plaintext_filename, key);
  std::cout << "Ciphertext written to 'ciphertext.txt'\n";
}

void User::DecryptFile() {
  std::string ciphertext_filename;
  std::string key;
  // get the file with the plain text
  std::cout << "File name/path: ";
  std::cin >> ciphertext_filename;
  std::cout << "Key: ";
  std::cin >> key;
  advancedXorDecryptionFile(ciphertext_filename, key);
  std::cout << "plaintext written to 'plaintext.txt'\n";
}

