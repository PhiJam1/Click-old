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
        User(std::string firstName, std::string getLastName, std::string email, std::string password);

        std::string getFirstName();

        std::string getLastName();

        std::string getEmail();

        std::string xorEncryptPassword(std::string plaintext, std::string key);

        bool xorAdvEncrptPassword(std::string plaintext, std::string key);
};

#endif