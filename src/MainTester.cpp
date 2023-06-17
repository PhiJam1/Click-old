#include <iostream>
#include <fstream>

#include "User.hpp"

/*
    Run this program while in the 'click' directory.
*/
int main() {
    std::ofstream outFile{"DebugLogs/MainTesterDebugLog.txt"};
    if (!outFile.is_open()) {
        std::cout << "MainTester debug log cannot be opened...ABORTING...\n";
        return 0;
    }
    outFile << "In MainTester.cpp\n";

    outFile << "Creating a User object\n";
    User p1("Philip", "James", "PhiJam1", "password");
    outFile << "User was create\n";
    outFile << p1.getEmail << " " << p1.getFirstName << " " << p1.getLastName << "\n";
    

    outFile.close();
    return 0;

}
