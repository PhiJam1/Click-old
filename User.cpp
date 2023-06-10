#include <iostream>
#include <vector>

#include "Security_Algorithms/Encryption_Algorithms/XOR.cpp";
#include "Security_Algorithms/Cipher.cpp";


class User {   

  private:
    std::string firstName;
    std::string lastName;
    std::string email;
    std::string password;
    std::vector<Ciphers> encryptions;
};