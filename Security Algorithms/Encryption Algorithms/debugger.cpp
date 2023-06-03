#include <iostream>
#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include <stdint.h>

#include "sha.h"
using namespace std;

int main() {
    int x = 0b0000011111111111111;
    int rotr17 = ROTRIGHT(x, 7);
    int rotr19 = ROTRIGHT(x, 19);
    int shr10 = x >> 10;
    int sig1 = rotr17 ^ rotr19 ^ shr10;
    int sigreal1 = SIG1(x);

    cout << bitset<8 * sizeof(int)>(x) << endl;
    cout << bitset<8 * sizeof(int)>(rotr17) << endl;
    cout << bitset<8 * sizeof(int)>(rotr19) << endl;
    cout << bitset<8 * sizeof(int)>(shr10) << endl;
    cout << bitset<8 * sizeof(int)>(sig1) << endl;
    cout << bitset<8 * sizeof(int)>(sigreal1) << endl;
}