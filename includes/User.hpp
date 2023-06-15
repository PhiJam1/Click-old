#ifndef USER_HPP
#define USER_HPP
#include <iostream>
#include <vector>

#include "Cipher.hpp"

class User {

    private:
        std::string firstName;
        std::string lastName;
        std::string email;
        std::string password;
        std::vector<Cipher> encryptions;

    public:
        std::string getFirstName();

        std::string getLastName();

        std::string getEmail();

        bool xorEncryptPassword(std::string plaintext, std::string key);

        bool xorAdvEncrptPassword(std::string plaintext, std::string key);
};

#endif