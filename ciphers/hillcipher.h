#include "err.h"

typedef struct HCipher* HILL_CIPHER;
typedef struct HCipher* HPTR;
struct HCipher{
    STRING plain_text_s;
    MATRIX key;
    VECTOR plain_text_v;
    VECTOR cipher_text_v;
    VECTOR decrypt_text_v;
    SIZE row_size;
    SIZE col_size;
    SIZE v_len;
};

#ifndef __HILL_CIPHER_H
#define __HILL_CIPHER_H
HILL_CIPHER createHCipher(STRING);
void halloc(HILL_CIPHER, BOOL);
void editKey_m(HILL_CIPHER);
void editVect_m(HILL_CIPHER);
BOOL isVoid(HILL_CIPHER);
BOOL isNull_v(VECTOR,MATRIX);
MATRIX retrieveKey(HILL_CIPHER);
void encrypt_h(HILL_CIPHER);
void decrypt_h(HILL_CIPHER);
void alloc_v(VECTOR,MATRIX,SIZE);
void alloc_r(PTR_I_, SIZE);
void prints(MATRIX,VECTOR);
#endif



HILL_CIPHER createCipher(STRING str){
    HILL_CIPHER H = NULL;
    H = (HPTR)malloc(sizeof(struct HCipher));
    if(isVoid(H))
        FatalError("Out of Memory.");
    H->v_len = 1;
    H->row_size = strlen(str), H->col_size = strlen(str);
    H->plain_text_s = (STRING)malloc(sizeof(char)*strlen(str));
    strncpy(H->plain_text_s, str, strlen(str));
    H->plain_text_s[strlen(str)] = '\0';
    halloc(H,0);
    halloc(H,1);
    editKey_m(H);
    editVector_m(H);
    return H;
}

void halloc(HILL_CIPHER H, BOOL isVect){
    if(!isVect){
        alloc_v(NULL, H->key, H->row_size);

    }
    else{
        H->cipher_text_v = (VECTOR)malloc(sizeof(PTR_I_)*H->v_len);
        H->decrypt_text_v = (VECTOR)malloc(sizeof(PTR_I_)*H->v_len);
        H->plain_text_v = (VECTOR)malloc(sizeof(PTR_I_)*H->v_len);
        if(isNull_v(H->cipher_text_v,NULL) ||isNull_v(H->cipher_text_v,NULL) || 
            isNull_v(H->decrypt_text_v,NULL))
            FatalError("Out of Memory");
        for(int i=0;i<H->v_len;i++){
            H->cipher_text_v[i] = (PTR_I_)malloc(sizeof(int)*H->col_size);
            H->decrypt_text_v[i] = (PTR_I_)malloc(sizeof(int)*H->col_size);
            H->plain_text_v[i] = (PTR_I_)malloc(sizeof(int)*H->col_size);
        }
        
    }
}


