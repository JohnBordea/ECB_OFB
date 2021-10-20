struct A {
    unsigned char* K3;
    unsigned char* iv;
    unsigned char* K;
    unsigned char* encryptedK;
    int encryptionType;
    uint8_t* message;
    uint8_t* cryptoText;
};

void initA(struct A * self) {
    self->K3 = "YolRAJT50okZYKId";
    self->iv = "QIsnOcovu2fFCcmO";
}

unsigned char* getIvA(struct A * self) {
    return self->iv;
}

void setEncryptionType(struct A * self, int type) {
    self->encryptionType = type;
}

int getEncryptionType(struct A* self) {
    return self->encryptionType;
}

void setMessage(struct A * self, uint8_t *message) {
    self->message = (uint8_t*) malloc(strlen(message) + 1);
    strcpy(self->message, message);
}

uint8_t* getMessageA(struct A * self) {
    return self->message;
}

void setCryptoTextA(struct A * self, unsigned char *cryptoText) {
    self->cryptoText = cryptoText;
}

unsigned char* getCriptoTextA(struct A * self) {
    return self->cryptoText;
}

void setKeyA(struct A* self, unsigned char* key) {
    self->K = (unsigned char*) malloc(strlen(key) + 1);
    strcpy(self->K, key);
}

unsigned char* getKeyToDecodeA(struct A* self) {
    return self->K3;
}

unsigned char* getKeyA(struct A* self) {
    return self->K;
}