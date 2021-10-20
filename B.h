struct B {
    unsigned char* K3;
    unsigned char* iv;
    unsigned char* K;
    unsigned char* encryptedK;
    int dencryptionType;
    uint8_t* cryptoText;
    uint8_t* message;
};

void initB(struct B * self) {
    self->K3 = "YolRAJT50okZYKId";
    self->iv = "QIsnOcovu2fFCcmO";
}

unsigned char* getIvB(struct B * self) {
    return self->iv;
}

void setDecryptionType(struct B * self, int type) {
    self->dencryptionType = type;
}

int getDecryptionType(struct B * self) {
    return self->dencryptionType;
}

void setCryptoTextB(struct B * self, char *cryptoText) {
    self->cryptoText = cryptoText;
}

unsigned char* getCryptoTextB(struct B * self) {
    return self->cryptoText;
}

void setMessageB(struct B * self, char *message) {
    self->message = message;
}

unsigned char* getMessageB(struct B * self) {
    return self->message;
}

void setKeyB(struct B* self, unsigned char* key){
    self->K = (unsigned char*) malloc(strlen(key) + 1);
    strcpy(self->K, key);
}

unsigned char* getKeyToDecodeB(struct B* self) {
    return self->K3;
}

unsigned char* getKeyB(struct B* self) {
    return self->K;
}