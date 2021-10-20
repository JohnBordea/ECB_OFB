struct KM {
    unsigned char* K1, *K2, *K3;
    unsigned char* K;
    unsigned char* encryptedKey;
};

void initKM(struct KM * self) {
    self->K1 = "zLglVej6LmdrxFHE";
    self->K2 = "b0P5ghSMskF5ZeRP";
    self->K3 = "YolRAJT50okZYKId";
}

unsigned char* getKey(struct KM* self) {
    return self->encryptedKey;
}