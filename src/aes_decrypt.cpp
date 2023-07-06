#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>
#include "aes_structures.hpp"
//lol
using namespace std;

/* Used in Round() and serves as the final round during decryption
 * SubRoundKey is simply an XOR of a 128-bit block with the 128-bit key.
 * So basically does the same as AddRoundKey in the encryption
 */
void SubRoundKey(unsigned char * state, unsigned char * roundKey) {
	for (int i = 0; i < 16; i++) {
		state[i] ^= roundKey[i];
	}
}

/* InverseMixColumns uses mul9, mul11, mul13, mul14 look-up tables
 * Unmixes the columns by reversing the effect of MixColumns in encryption
 */
void InverseMixColumns(unsigned char * state) {
	unsigned char tmp[16];

	tmp[0] = (unsigned char)mul14[state[0]] ^ mul11[state[1]] ^ mul13[state[2]] ^ mul9[state[3]];
	tmp[1] = (unsigned char)mul9[state[0]] ^ mul14[state[1]] ^ mul11[state[2]] ^ mul13[state[3]];
	tmp[2] = (unsigned char)mul13[state[0]] ^ mul9[state[1]] ^ mul14[state[2]] ^ mul11[state[3]];
	tmp[3] = (unsigned char)mul11[state[0]] ^ mul13[state[1]] ^ mul9[state[2]] ^ mul14[state[3]];

	tmp[4] = (unsigned char)mul14[state[4]] ^ mul11[state[5]] ^ mul13[state[6]] ^ mul9[state[7]];
	tmp[5] = (unsigned char)mul9[state[4]] ^ mul14[state[5]] ^ mul11[state[6]] ^ mul13[state[7]];
	tmp[6] = (unsigned char)mul13[state[4]] ^ mul9[state[5]] ^ mul14[state[6]] ^ mul11[state[7]];
	tmp[7] = (unsigned char)mul11[state[4]] ^ mul13[state[5]] ^ mul9[state[6]] ^ mul14[state[7]];

	tmp[8] = (unsigned char)mul14[state[8]] ^ mul11[state[9]] ^ mul13[state[10]] ^ mul9[state[11]];
	tmp[9] = (unsigned char)mul9[state[8]] ^ mul14[state[9]] ^ mul11[state[10]] ^ mul13[state[11]];
	tmp[10] = (unsigned char)mul13[state[8]] ^ mul9[state[9]] ^ mul14[state[10]] ^ mul11[state[11]];
	tmp[11] = (unsigned char)mul11[state[8]] ^ mul13[state[9]] ^ mul9[state[10]] ^ mul14[state[11]];

	tmp[12] = (unsigned char)mul14[state[12]] ^ mul11[state[13]] ^ mul13[state[14]] ^ mul9[state[15]];
	tmp[13] = (unsigned char)mul9[state[12]] ^ mul14[state[13]] ^ mul11[state[14]] ^ mul13[state[15]];
	tmp[14] = (unsigned char)mul13[state[12]] ^ mul9[state[13]] ^ mul14[state[14]] ^ mul11[state[15]];
	tmp[15] = (unsigned char)mul11[state[12]] ^ mul13[state[13]] ^ mul9[state[14]] ^ mul14[state[15]];

	for (int i = 0; i < 16; i++) {
		state[i] = tmp[i];
	}
}

// Shifts rows right (rather than left) for decryption
void ShiftRows(unsigned char * state) {
	unsigned char tmp[16];

	/* Column 1 */
	tmp[0] = state[0];
	tmp[1] = state[13];
	tmp[2] = state[10];
	tmp[3] = state[7];

	/* Column 2 */
	tmp[4] = state[4];
	tmp[5] = state[1];
	tmp[6] = state[14];
	tmp[7] = state[11];

	/* Column 3 */
	tmp[8] = state[8];
	tmp[9] = state[5];
	tmp[10] = state[2];
	tmp[11] = state[15];

	/* Column 4 */
	tmp[12] = state[12];
	tmp[13] = state[9];
	tmp[14] = state[6];
	tmp[15] = state[3];

	for (int i = 0; i < 16; i++) {
		state[i] = tmp[i];
	}
}

/* Perform substitution to each of the 16 bytes
 * Uses inverse S-box as lookup table
 */
void SubBytes(unsigned char * state) {
	for (int i = 0; i < 16; i++) { // Perform substitution to each of the 16 bytes
		state[i] = inv_s[state[i]];
	}
}

/* Each round operates on 128 bits at a time
 * The number of rounds is defined in AESDecrypt()
 * Not surprisingly, the steps are the encryption steps but reversed
 */
void Round(unsigned char * state, unsigned char * key) {
	SubRoundKey(state, key);
	InverseMixColumns(state);
	ShiftRows(state);
	SubBytes(state);
}

// Same as Round() but no InverseMixColumns
void InitialRound(unsigned char * state, unsigned char * key) {
	SubRoundKey(state, key);
	ShiftRows(state);
	SubBytes(state);
}

/* The AES decryption function
 * Organizes all the decryption steps into one function
 */
void AESDecrypt(unsigned char * encryptedMessage, unsigned char * expandedKey, unsigned char * decryptedMessage)
{
	unsigned char state[16]; // Stores the first 16 bytes of encrypted message

	for (int i = 0; i < 16; i++) {
		state[i] = encryptedMessage[i];
	}

	InitialRound(state, expandedKey + 160);

	int numberOfRounds = 9;

	for (int i = 8; i >= 0; i--) {
		Round(state, expandedKey + (16 * (i + 1)));
	}

	SubRoundKey(state, expandedKey); // Final round

	// Copy decrypted state to buffer
	for (int i = 0; i < 16; i++) {
		decryptedMessage[i] = state[i];
	}
}



int main() {
    cout << "---------------------------------------------------" << endl;
    cout << "              128-bit AES Decryption" << endl;
	cout << " (Make sure that you encrypt and decrypt properly) " << endl;
    cout << "---------------------------------------------------" << endl;
	/*
    // Prompt user for ciphertext file name
    string ciphertextFileName;
    cout << "Enter the name of the ciphertext file: ";
    getline(cin, ciphertextFileName);

    // Read encrypted message from ciphertext file
    ifstream file(ciphertextFileName, ios::binary | ios::ate);
    if (!file.is_open()) {
        cout << "Unable to open the ciphertext file. (It doesn't exist)" << endl;
        return 1;
    }

    // Get the file size
    streampos fileSize = file.tellg();
    file.seekg(0, ios::beg);

    // Read the encrypted message into a vector
    //vector<unsigned char> encryptedMessage(fileSize);
    //if (!file.read(reinterpret_cast<char*>(encryptedMessage.data()), fileSize)) {
      //  cout << "Error reading the ciphertext file." << endl;
        //return 1;
    //}
	*/

	std::ifstream ifs("ciphertext.txt");
	std::vector<unsigned char> encryptedMessage;
	int j = 0;
	while (ifs.good()) {
		int val = 0;
		ifs >> val;
		encryptedMessage.push_back((unsigned char)  val);
		std::cout << encryptedMessage.at(j++) << " ";
	}


    //file.close();
    //cout << "Read encrypted message from " << ciphertextFileName << endl;

    // Read in the key from aes_keyfile
    string keystr;
    ifstream aes_keyfile("src/aes_keyfile"); // Open the aes_keyfile

    if (aes_keyfile.is_open()) {
        getline(aes_keyfile, keystr); // The first line of the file should be the key, or change this to change line number
        cout << "Read in the 128-bit key from aes_keyfile." << endl;
        aes_keyfile.close();
    } else {
        cout << "Unable to open aes_keyfile. (It doesn't exist)" << endl;
        return 1;
    }

    istringstream hex_chars_stream(keystr);
    unsigned char key[16];
    int i = 0;
    unsigned int c;
    while (hex_chars_stream >> hex >> c) {
        key[i] = c;
        i++;
    }


    unsigned char expandedKey[176];
    KeyExpansion(key, expandedKey);

    int messageLen = encryptedMessage.size();

    // Pad the message if its length is not a multiple of 16
    int paddingLength = 16 - (messageLen % 16);
    if (paddingLength != 16) {
        encryptedMessage.resize(messageLen + paddingLength, 0);
    }

    vector<unsigned char> decryptedMessage(messageLen + paddingLength);

    for (int i = 0; i < messageLen; i += 16) {
        AESDecrypt(encryptedMessage.data() + i, expandedKey, decryptedMessage.data() + i);
    }

    // Write decrypted message to plaintext.txt or the file specified
    ofstream outputFile("plaintext.txt", ios::binary);
    if (!outputFile.is_open()) {
        cout << "There was an error creating a file to decrypt to." << endl;
        return 1;
    }

    
	outputFile.write(reinterpret_cast<const char*>(decryptedMessage.data()), decryptedMessage.size());
    outputFile.close();

    cout << "Decrypted message was written to the file that was specified." << endl;

    return 0;
}
