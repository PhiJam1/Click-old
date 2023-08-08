#ifndef MAINUTILITIES_HPP
#define MAINUTILITIES_HPP

#define APPLICATION_DIR     "/home/philip/click/Documents/Click/"
#define CRED_FILENAME       "USERDATA/CREDS.txt"

bool Login();
bool NewAccount();
bool EmailInUse(std::string email);
std::string GenSalt();
bool ValidPassword(std::string password);

#endif
