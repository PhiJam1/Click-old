#ifndef CIPHERTYPE_HPP
#define CIPHERTYPE_HPP


typedef enum {
    XOR,
    BLOWFISH,
    AES
} CipherType_t;

typedef struct {
    CipherType_t type;
    std::string service_name;
    std::string username;
    std::string ciphertext;
} CipherInfo;

#endif
