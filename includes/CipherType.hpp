#ifndef CIPHERTYPE_HPP
#define CIPHERTYPE_HPP


typedef enum {
    XOR,
    AES,
    BLOWFISH,
} CipherType_t;

typedef struct {
    CipherType_t type;
    std::string service_name;
    std::string username;
    std::string ciphertext;
} CipherInfo;

#endif
