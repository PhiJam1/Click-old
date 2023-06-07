#include <iostream>
#include <vector>

#include "Encryptors.cpp"

class User {   

  private:
    std::string firstName;
    std::string lastName;
    std::string email;
    std::string password;
    std::vector<Encryptors> encryptions;

};