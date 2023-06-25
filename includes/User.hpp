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

        std::string xorEncryptPasswordDriver(std::string plaintext, std::string key);

        std::string xorDecryptPasswordDriver(std::string ciphertext, std::string key);

        std::string xorAdvEncryptPasswordDriver(std::string plaintext, std::string key);
        
        std::string xorAdvDecryptPasswordDriver(std::string ciphertext, std::string key);
};

#endif