#ifndef MAINUTILITIES_HPP
#define MAINUTILITIES_HPP

#include "User.hpp"

#define APPLICATION_DIR     "/home/philip/click/Documents/Click/"
#define CRED_FILENAME       "USERDATA/CREDS.txt"

// function to create accounts and log users in
User* Login(bool new_user);
User* NewAccount();

// callback functions
int EmailInUse(void* data, int argc, char** argv, char** /* azColName */);
int GetSalt(void* data, int argc, char** argv, char** /* azColName */);
int CheckPassword(void* data, int argc, char** argv, char** /* azColName */);

// helper function
std::string GenSalt();
bool ValidPassword(std::string password);


#endif
