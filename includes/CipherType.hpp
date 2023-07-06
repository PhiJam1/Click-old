#ifndef CIPHERTYPE_HPP
#define CIPHERTYPE_HPP
typedef enum {
    XOR,
    AES,
    BLOWFISH,
} CipherType_t;

typedef struct {
    CipherType_t type;
    std::string ciphertext;
    std::string key;
    std::string loginName;
} CipherInfo;

#endif
