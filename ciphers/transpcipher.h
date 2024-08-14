#include "err.h"
typedef struct TCipher* TR_CIPHER;
typedef struct TCipher* TPTR;

struct TCipher{
    STRING plain_text;
    KEY_TYPE depth;
    MATRIX encrypted;
    STRING decrypted;
    SIZE col_size;
};


#ifndef __TRANS_CIPHER_H
#define __TRANS_CIPHER_H
TR_CIPHER createTCipher(KEY_TYPE,STRING);
BOOL isNull_t(TR_CIPHER);
void talloc(TR_CIPHER);
void editKey_t(TR_CIPHER);
void encrypt_t(TR_CIPHER);
#endif 


TR_CIPHER createTCipher(KEY_TYPE depth, STRING str){
    TR_CIPHER T = NULL;
    T = (TR_CIPHER)malloc(sizeof(struct TCipher));
    if(isNull_t(T))
        FatalError("Out of Memory");
    T->plain_text = (STRING)malloc(sizeof(char)*strlen(str));
    strncpy(T->plain_text, str, strlen(str));
    T->plain_text[strlen(str)] = '\0';
    T->depth = depth;
    T->col_size = strlen(str);
    talloc(T);
    editKey_t(T);
}

BOOL isNull_t(TR_CIPHER T){
    return T==NULL;
}

void talloc(TR_CIPHER T){
    T->encrypted = alloc_v(NULL, T->encrypted, T->depth);
    for(int i=0;i<T->depth;i++){
            T->encrypted[i] = alloc_r(T->encrypted[i],T->col_size);
            if(!T->encrypted[i])
                FatalError("Out of Memory");
    }
}

void editKey_t(TR_CIPHER T){
    for(int i=0;i<T->depth;i++){
        for(int j=0;j<T->col_size;j++){
            T->encrypted[i][j] = -1;
        }
    }
}


void encrypt_t(TR_CIPHER T){
    if(isNull_t(T))
        FatalError("Uninitialised Cipher");
    printf("%d",T->encrypted[0][0]);    

}


void prints_t(TR_CIPHER T){
    if(isNull_t(T))
        FatalError("Uninitialised Cipher");
    for(int i=0;i<T->depth;i++){
        for(int j=0;j<T->col_size;j++){
            printf("%d\t",T->encrypted[i][j]);
        }
        printf("\n");
    }
}
