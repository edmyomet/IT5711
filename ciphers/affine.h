#include "err.h"
#define __MODULAR_INVERSE_CONSTANT  (1)

typedef struct ACipher* AF_CIPHER;
typedef struct ACipher* APTR;


struct ACipher{
    KEY_TYPE a;
    KEY_TYPE b;
    KEY_TYPE inv_a;
    SIZE str_size;
    STRING plain_text;
    STRING cipher_text;
    STRING decrypted_text;
};

#ifndef __ACIPHER_H
#define __CIPHER_H
AF_CIPHER createACipher(STRING,KEY_TYPE, KEY_TYPE);
BOOL isVoid_a(AF_CIPHER);
void stralloc(AF_CIPHER);
void editKey_a(AF_CIPHER,KEY_TYPE);
void encrypt_a(AF_CIPHER);
void decrypt_a(AF_CIPHER);
void getEncrypted_a(AF_CIPHER);
void getDecrypted_a(AF_CIPHER);
#endif


AF_CIPHER createACipher(STRING str,KEY_TYPE a, KEY_TYPE b){
    AF_CIPHER A = NULL;
    A = (AF_CIPHER)malloc(sizeof(struct ACipher));
    if(isVoid_a(A))
        FatalError("Out of Memory");
    A-> a = a;
    A->b = b;
    A->str_size = strlen(str);
    A->plain_text = (STRING)malloc(sizeof(char)*A->str_size);
    strncpy(A->plain_text, str, A->str_size);
    A->plain_text[strlen(str)] = '\0';
    stralloc(A);
}

BOOL isVoid_a(AF_CIPHER A){
    return A == NULL;
}

void stralloc(AF_CIPHER A){
    A->cipher_text = (STRING)malloc(sizeof(char)*A->str_size);
    A->decrypted_text = (STRING)malloc(sizeof(char)*A->str_size);
}

void encrypt_a(AF_CIPHER A){
    int placeHolder;
    for(int i=0;i<A->str_size;i++){
        placeHolder = (int)A->plain_text[i]-65;
        placeHolder = (placeHolder*A->a) + A->b;
        placeHolder = (placeHolder%26);
        A->cipher_text[i] = 65+placeHolder;
        printf("%c\n", A->cipher_text[i]);
    }
}

KEY_TYPE findInverse(KEY_TYPE a){
    int tmp,i,check; //placeholder for A*B values
    for(i=0;i<=26;i++){
        if((a*i)%26 == __MODULAR_INVERSE_CONSTANT)
            check = i;
    }
    PrintInteger(check);
    return check;
}

void decrypt_a(AF_CIPHER A){
    A->inv_a = findInverse(A->a);
    int placeHolder;
    for(int i=0;i<A->str_size;i++){
        placeHolder = (A->cipher_text[i]-65+26);
        placeHolder = ((placeHolder-A->b) * A->inv_a +26)%26%26;
        A->decrypted_text[i] = 65 + placeHolder;
    }
}
void editKey_a(AF_CIPHER A, KEY_TYPE b){

}

void getEncrypted_a(AF_CIPHER A){
    Print(A->cipher_text);
}

void getDecrypted_a(AF_CIPHER A){
    Print(A->decrypted_text);
}