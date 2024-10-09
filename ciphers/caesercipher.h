/*
    Header file for the implementation of a caeser cipher
 */

#include "err.h"

typedef struct CCipher* CAESER_CIPHER;
typedef struct CCipher* CPTR;


struct CCipher{
    KEY_TYPE key;
    SIZE str_size;
    STRING plain_text;
    STRING cipher_text;
    STRING decrypted_text;
};

/*
    IMPLEMENTATION FUNCTIONS
*/

#ifndef __CCIPHER_H
#define __CCIPHER_H
CAESER_CIPHER createCipher(STRING);
KEY_TYPE retrieveKey(CAESER_CIPHER);
void editKey(KEY_TYPE,CAESER_CIPHER);
void editPlainText(STRING,CAESER_CIPHER);
void salloc(CAESER_CIPHER);
void encrypt(CAESER_CIPHER);
void decrypt(CAESER_CIPHER);
void cryptanalysis(CAESER_CIPHER);
void freeCipher(CAESER_CIPHER);
BOOL isEmpty(CAESER_CIPHER);
BOOL isNull(STRING);
STRING retrieveCipherText(CAESER_CIPHER);
STRING retrieveDecrypt(CAESER_CIPHER);
#endif

/// @brief - Initialises the Caeser Cipher structure, the key and accepts the plain text string to be encoded 
/// @param str - plain text that is to be encoded is stored within the structure
/// @return - returns the newly initialised structure
CAESER_CIPHER createCipher(STRING s){
    CAESER_CIPHER C = NULL;
    C = (CAESER_CIPHER)malloc(sizeof(struct CCipher));
    if(isEmpty(C))
        FatalError("Out of Memory Space");
    scanf("%d", &C->key);
    C->plain_text = (STRING)malloc(sizeof(char)*strlen(s));
    strncpy(C->plain_text, s, strlen(s));
    C->plain_text[strlen(s)] = '\0';
    C->str_size = strlen(s);
    salloc(C);
    return C;
}
/// @brief - checks if the structure is empty, if so, returns a 1
/// @param C - structure to be checked
/// @return - 1 if the structure is empty, 0 otherwise
BOOL isEmpty(CAESER_CIPHER C){
    return C == NULL;
}
/// @brief - checks if a string is null
/// @param str - string to be checked 
/// @return - returns 1 if the string is null, 0 otherwise
BOOL isNull(STRING str){
    return str == NULL;
}
/// @brief - returns the key for the specific cipher
/// @param C - the cipher whose key is to be returned on call
/// @return - return type int,
KEY_TYPE retrieveKey(CAESER_CIPHER C){
    return C->key;
}
/// @brief - if the key has been exposed, it can be changed using this function
/// @param key - the new key that replaces the previous key in the cipher
/// @param C - the cipher whose key is to be changed
void editKey(KEY_TYPE key, CAESER_CIPHER C){
    if(isEmpty(C))
        Warning("Initialise Cipher first.");
    C->key = key;
}

void editPlainText(STRING str, CAESER_CIPHER C){
    if(isEmpty(C))
        Warning("Initialise Cipher first.");
    strncpy(C->plain_text, str, strlen(str));
    C->plain_text[strlen(str)] = '\0';
    C->str_size = strlen(str);
    salloc(C);
}

void freeCipher(CAESER_CIPHER C){
    if(isEmpty(C))
        Warning("Cannot free an empty cipher");
    free(C->cipher_text);
    free(C->decrypted_text);
    free(C->plain_text);
    free(C);
}

void encrypt(CAESER_CIPHER C){
    int placeHolder;
    for(int i=0; i<C->str_size;i++){
       placeHolder = ((int)C->plain_text[i])-65;
       placeHolder += C->key, placeHolder %= 26, placeHolder += 65;
       C->cipher_text[i] = placeHolder;
    }
}

void decrypt(CAESER_CIPHER C){
    int placeHolder;
    for(int i=0;i<C->str_size;i++){
        placeHolder = ((int)C->cipher_text[i])-65;
        placeHolder -= C->key, placeHolder += 26,placeHolder %= 26, placeHolder += 65;
        C->decrypted_text[i] = placeHolder;
    }
}

void salloc(CAESER_CIPHER C){
    if(!isNull(C->decrypted_text))
        free(C->decrypted_text);
    if(!isNull(C->cipher_text))
        free(C->cipher_text);
    C->cipher_text = (STRING)malloc(sizeof(char)*C->str_size);
    C->decrypted_text = (STRING)malloc(sizeof(char)*C->str_size);
    
}
STRING retrieveCipherText(CAESER_CIPHER C){
    return C->cipher_text;
}

STRING retrieveDecrypt(CAESER_CIPHER C){
    return C->decrypted_text;
}
