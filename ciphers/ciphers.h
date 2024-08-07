#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FatalError(str)  fprintf(stderr, "%s\n", str), exit(1)
#define Warning(str)    fprintf(stderr, "%s\n", str), exit(0)
#define Print(str)		fprintf(stdout, "%s\n", str)
typedef int KEY;
typedef char* STRING;
typedef int BOOL;


/*
CAESER CIPHER FUNCTION PROTOTYPES AND STRUCTURE DEFINITIONS
 */
typedef struct CaeserCipher* CAESER_CIPHER;
typedef struct CaeserCipher* PTR;

#ifndef __CIPHER_H__
#define __CIPHER_H__
STRING initString(STRING,int);
void PlainText(CAESER_CIPHER, STRING);
BOOL isEmpty(STRING);
///@brief - initialises the caeser ipher structure
///@return - returns the newly initialised structure
CAESER_CIPHER init();
///@brief - encrypts the plain text message
///@param - string that is to be encrypted
///@param - structure containing the key
void Encrypt(CAESER_CIPHER);
///@brief - decrypts the cipher text message and returns it 
///@param - the structure containing key and cipher text

void Decrypt(CAESER_CIPHER);
#endif

struct CaeserCipher{
	KEY k;
	int size;
	STRING plain;
	STRING encrypted; //ciphertext
	STRING decrypted; // decrypted plain text
};

/*
    HILL CIPHER FUNCTION PROTOTYPES AND STRUCTURE DEFINITIONS 
	assuming 2x2
*/
typedef struct HillCipher* HILL_CIPHER;
typedef struct HillCipher* HPTR;
typedef int** MATRIX;
typedef int** VECT;
typedef int*PTR_I;
typedef int SIZE;

#ifndef __HILL_CIPHER_
#define __HILL_CIPHER_
HILL_CIPHER init_h(STRING);
VECT assignVector(MATRIX,SIZE,SIZE);
void initKeyMatrix(HILL_CIPHER);
void initPTM(HILL_CIPHER);
void EncryptHill(HILL_CIPHER);
void DecryptHill(HILL_CIPHER);
void findInverse(HILL_CIPHER);
#endif 

struct HillCipher{
    MATRIX keyMatrix;
    MATRIX PTM; // plain text matrix
	SIZE row_size_;
	SIZE col_size_;
	SIZE v_len_;
	STRING plain;
	MATRIX ENC;
	MATRIX DEC;
};