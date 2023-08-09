#ifndef MAINUTILITIES_HPP
#define MAINUTILITIES_HPP

#include "User.hpp"

#define APPLICATION_DIR     "/home/philip/click/Documents/Click/"
#define CRED_FILENAME       "USERDATA/CREDS.txt"

// function to create accounts and log users in
User* Login(bool new_user);
User* NewAccount();
bool EmailInUse(std::string email);
std::string GenSalt();
bool ValidPassword(std::string password);


#endif
