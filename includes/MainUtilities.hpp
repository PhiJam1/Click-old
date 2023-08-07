#ifndef MAINUTILITIES_HPP
#define MAINUTILITIES_HPP

#define APPLICATION_DIR     "/home/philip/click/Documents/Click/" // some thing to set in installation
#define CRED_FILENAME       APPLICATION_DIR + "USERDATA/CREDS.txt"

bool Login();
bool NewAccount();
bool EmailInUse(std::string email);
std::string GenSalt();


#endif
