#ifndef USER_HPP
#define USER_HPP
#include <iostream>
#include <vector>

#include "CipherType.hpp"

#define PERSONAL_INFO_START_DELIMITER "++\n"
#define PERSONAL_INFO_END_DELIMITER "##\n"
#define CIPHER_STRUCT_ENDING_DELIMITER  "@@\n"
#define FILE_ENDING_DELIMITER "--"

typedef enum errors_t {
    REPEATED_LOGIN_CREATION,
    DATA_NOT_SAVED,
} errors_t;

class User {

    private:
        std::string firstName;
        std::string lastName;
        std::string email;
        std::string password;
        std::vector<CipherInfo> ciphers;

    public:
        User(std::string firstName, std::string getLastName, std::string email, std::string password);

        User(std::string filename, std::string password);

        std::string getFirstName();

        std::string getLastName();

        std::string getEmail();

        std::string xorEncryptPasswordDriver(std::string loginName, std::string plaintext, std::string key);

        std::string xorDecryptPasswordDriver(std::string ciphertext, std::string key);

        std::string xorAdvEncryptPasswordDriver(std::string loginName, std::string plaintext, std::string key);
        
        std::string xorAdvDecryptPasswordDriver(std::string ciphertext, std::string key);

        void SaveUserData();
};

#endif