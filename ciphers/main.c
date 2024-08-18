#include "caesercipher.h"
#include "hillcipher.h"
#include "transpcipher.h"
#include "affine.h"

int main(int argc, char**argv){
    STRING name = (STRING)malloc(sizeof(char)*20);
    scanf("%s",name);
    CAESER_CIPHER C = createCipher(name);
    encrypt(C);
   printf("%s\n", retrieveCipherText(C));
   decrypt(C);
     printf("%s\n", retrieveDecrypt(C));
     freeCipher(C);
    HILL_CIPHER H = createHCipher("XYZ");
    encrypt_h(H);
    prints(NULL,H->cipher_text_v,H->col_size);
    TR_CIPHER T = createTCipher(3, "SHRUTHI");
    encrypt_t(T);
    getEncryption_t(T);
    decrypt_t(T);
    Print(getDecrypted_t(T));
    AF_CIPHER A = createACipher("SHRUTHI", 3,5);
    encrypt_a(A);
    getEncrypted_a(A);
    decrypt_a(A);
    getDecrypted_a(A);
}