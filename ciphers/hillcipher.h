#include "err.h"

typedef struct HCipher* HILL_CIPHER;
typedef struct HCipher* HPTR;
struct HCipher{
    STRING plain_text_s;
    MATRIX key;
    MATRIX key_inverse;
    MATRIX adj;
    float determinant;
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
MATRIX getKey(HILL_CIPHER);
void encrypt_h(HILL_CIPHER);
void decrypt_h(HILL_CIPHER);
VECTOR alloc_v(VECTOR,MATRIX,SIZE);
PTR_I_ alloc_r(PTR_I_, SIZE);
void prints(MATRIX,VECTOR,SIZE);
void get_encrypted(HILL_CIPHER);
#endif



HILL_CIPHER createHCipher(STRING str){
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
    editVect_m(H);
    return H;
}

void halloc(HILL_CIPHER H, BOOL isVect){
    if(!isVect){
        H->key = alloc_v(NULL, H->key, H->row_size);
        for(int i=0;i<H->row_size;i++){
            H->key[i]=alloc_r(H->key[i], H->col_size);
            if(!H->key[i])
                FatalError("Out of Memory");
        }
    }
    else{
        H->cipher_text_v = alloc_v(H->cipher_text_v,NULL, H->v_len);
        H->decrypt_text_v = alloc_v(H->decrypt_text_v,NULL, H->v_len);
        H->plain_text_v =   alloc_v(H->plain_text_v, NULL, H->v_len);

        for(int i=0;i<H->v_len;i++){
            H->cipher_text_v[i] = alloc_r(H->cipher_text_v[i],H->col_size);
            H->decrypt_text_v[i] =  alloc_r(H->decrypt_text_v[i], H->col_size);
            H->plain_text_v[i] =  alloc_r(H->plain_text_v[i], H->col_size);
        }
        
    }
}

VECTOR alloc_v(VECTOR V, MATRIX M, SIZE n){
    if(isNull_v(NULL, M)){
        V = (VECTOR)malloc(sizeof(PTR_I_)*n);
        if(isNull_v(V,NULL))
            FatalError("Out of Memory");
        return V;
    }
    else{
        M = (MATRIX)malloc(sizeof(PTR_I_)*n);
        if(isNull_v(NULL,M))
            FatalError("Out of Memory");
        return M;
    }
}

PTR_I_ alloc_r(PTR_I_ R, SIZE n){
    R = (PTR_I_)malloc(sizeof(int)*n);
    return R;
}


void editKey_m(HILL_CIPHER H){
    int value;
    for(int i=0;i<H->row_size;i++){
        //printf("Enter %dth row of key matrix",i);
        for(int j=0;j<H->col_size;j++){
            //scanf("%d",&value);
            H->key[i][j] = (rand()%26) + 65;
            printf("%d\t", H->key[i][i]);
        }
        printf("\n");
    }
}

void editVect_m(HILL_CIPHER H){
    for(int i=0;i<H->v_len;i++){
        for(int j=0;j<H->col_size;j++){
            H->plain_text_v[i][j] = (int)H->plain_text_s[i];
            H->cipher_text_v[i][j] = 0;
        }
    }
}

BOOL isNull_v(VECTOR V, MATRIX M){
    return (V==NULL) && (M==NULL);
}

BOOL isVoid(HILL_CIPHER H){
    return H == NULL;
}

void encrypt_h(HILL_CIPHER H){
    for(int i=0;i<H->v_len;i++){
        for(int j=0;j<H->col_size;j++){
            for(int k=0;k<H->row_size;k++){
                H->cipher_text_v[i][j] += H->plain_text_v[i][k] * H->key[k][j];
            }
        }
    }
}
void get_encrypted(HILL_CIPHER H){
    
}
void prints(MATRIX M, VECTOR V,SIZE K){
    char placeHolder;
    if(isNull_v(NULL, M)){
        for(int i=0;i<K;i++){
            //placeHolder = '0' + (V[0][i] % 26);
            printf("%c\t",'0' +V[0][i]%26 + 65);
        }
        printf("\n");
    }
}


float findDeterminant(MATRIX M,SIZE row, SIZE col){
    //finding the determinant of a 3x3 matrix 
    float det = 0.0;
    det = M[0][0] *(M[1][1]*M[2][2] - M[1][2]*M[2][1]) - M[0][1]*(M[1][0]*M[2][2]-M[1][2]*M[2][0]) + M[0][2] * (M[0][1]*M[2][1]-M[2][0]*M[1][1]);
    return det;
}

MATRIX findAdjoint(MATRIX M, SIZE row, SIZE col){
    MATRIX cofactor;
    cofactor = alloc_v(NULL,cofactor,row);
    for(int i=0;i<row;i++){
        cofactor[i] = alloc_r(cofactor[i], col);
    }
}



