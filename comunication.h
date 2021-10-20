#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/aes.h>
#include <string.h>
#include <stdio.h>
#include "aes.c"
#include "A.h"
#include "B.h"
#include "KM.h"

void setKey(struct KM* self, int type) {
    struct AES_ctx ctx;
    if(type == 1) {
        AES_init_ctx(&ctx, self->K3);
        self->encryptedKey = (unsigned char*) malloc(strlen(self->K1) + 1);
        strcpy(self->encryptedKey, self->K1);
        AES_ECB_encrypt(&ctx, self->encryptedKey);
    } else if (type == 2) {
        AES_init_ctx(&ctx, self->K3);
        self->encryptedKey = (unsigned char*) malloc(strlen(self->K2) + 1);
        strcpy(self->encryptedKey, self->K2);
        AES_ECB_encrypt(&ctx, self->encryptedKey);
    }
}

void decodeKey(unsigned char* key, unsigned char* encodedKey) {
    struct AES_ctx ctx;
    AES_init_ctx(&ctx, key);
    AES_ECB_decrypt(&ctx, encodedKey);
}

uint8_t * ecbEncryption(uint8_t* message, unsigned char* key) {
    uint8_t * resizedMessage;
    unsigned int newSize = strlen(message) + ((strlen(message) % 16 == 0) ? (0) : (16 - strlen(message) % 16));
    resizedMessage = malloc(newSize + 1);
    resizedMessage[newSize] = 0;
    unsigned int newVal;

    for(int i = 0; i < newSize / 16; i++)
        for(int j = 0; j < 16; j++) {
            newVal = ((((i * 16 + j) > strlen(message)) ? (0) : (message[i * 16 + j])) + key[j]) % 256;
            resizedMessage[i * 16 + j] = (uint8_t) newVal;
        }

    return resizedMessage;
}

uint8_t * ecbDecryption(uint8_t* message, unsigned char* key) {
    uint8_t * resizedMessage;
    unsigned int newSize = strlen(message) + ((strlen(message) % 16 == 0) ? (0) : (16 - strlen(message) % 16));
    resizedMessage = malloc(newSize + 1);
    resizedMessage[newSize] = 0;
    unsigned int newVal;

    for(int i = 0; i < newSize / 16; i++)
        for(int j = 0; j < 16; j++) {
            newVal = message[i * 16 + j] - key[j];
            newVal = (newVal < 0) ? (newVal + 256) : (newVal);
            resizedMessage[i * 16 + j] = (uint8_t) newVal;
        }

    return resizedMessage;
}

uint8_t * ofbCryption(uint8_t* message, unsigned char* key, unsigned char* iv) {
    uint8_t * resizedMessage, *newIv;
    unsigned int newSize = strlen(message) + ((strlen(message) % 16 == 0) ? (0) : (16 - strlen(message) % 16));
    resizedMessage = malloc(newSize + 1);
    strcpy(resizedMessage, message);
    resizedMessage[newSize] = 0;
    unsigned int newVal;
    newIv = malloc(16);
    for(int i = 0; i < 16; i++)
        newIv[i] = iv[i];

    for(int i = 0; i < newSize / 16; i++) {
        for(int j = 0; j < 16; j++){
            newVal = (newIv[j] + key[j]) % 256;
            newIv[j] = (uint8_t) newVal;
        }
        for(int j = 0; j < 16; j++)
            resizedMessage[i * 16 + j] = newIv[j] ^ resizedMessage[i * 16 + j];
    }

    return resizedMessage;
}

void setType(struct A* a, struct B* b, struct KM* km, int type) {
    setEncryptionType(a, type);
    setKey(km, getEncryptionType(a));
    setKeyA(a, getKey(km));
    decodeKey(getKeyToDecodeA(a), getKeyA(a));

    setDecryptionType(b, getEncryptionType(a));
    setKeyB(b, getKey(km));
    decodeKey(getKeyToDecodeB(b), getKeyB(b));
}

void getMessage(struct A* a, const char* fimeName) {
    FILE *f = fopen(fimeName, "r");

    fseek(f, 0L, SEEK_END);
    unsigned int size = ftell(f);

    rewind(f);

    uint8_t * message;
    message = malloc(size + 1);
    message[size] = 0;

    for(int i = 0; i < size; i++)
        message[i] = (uint8_t) fgetc(f);

    fclose(f);

    setMessage(a, message);

    switch (getEncryptionType(a)) {
    case 1:
        setCryptoTextA(a, ecbEncryption( getMessageA(a), getKeyA(a) ) );
        break;
    case 2:
        setCryptoTextA(a, ofbCryption( getMessageA(a), getKeyA(a), getIvA(a) ) );
        break;
    }
}

void decryptMessage(struct A * a, struct B * b) {
    setCryptoTextB(b, getCriptoTextA(a));

    switch (getDecryptionType(b)) {
    case 1:
        setMessageB(b, ecbDecryption( getCryptoTextB(b), getKeyB(b) ) );
        break;
    case 2:
        setMessageB(b, ofbCryption( getCryptoTextB(b), getKeyB(b), getIvB(b) ) );
        break;
    }
}