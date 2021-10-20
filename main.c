#include "comunication.h"

///gcc -o main main.c -lcrypto

int main(int argc, char **argv) {
    
    struct A a;
    struct B b;
    struct KM km;

    initA(&a);
    initB(&b);
    initKM(&km);

    printf("Alegeti Criptosistemul:\n[1] ECB\n[2] OFB\n");

    unsigned int type;

    do{
        printf(">");
        scanf("%d", &type);
    }while(type != 1 && type != 2);

    setType(&a, &b, &km, 1);
    
    getMessage(&a, "message.txt");

    printf("Criptotextul:\n%s\n", getCriptoTextA(&a));

    decryptMessage(&a, &b);

    printf("Mesajul Primit:\n%s\n", getMessageB(&b));

    return 0;
}