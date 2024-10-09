#include "caesercipher.h"
#include "hillcipher.h"
#include "transpcipher.h"
#include "affine.h"

int main(int argc, char**argv){
    /*STRING name = (STRING)malloc(sizeof(char)*20);
    scanf("%s",name);
    CAESER_CIPHER C = createCipher(name);
    encrypt(C);
   printf("%s\n", retrieveCipherText(C));
   decrypt(C);
     printf("%s\n", retrieveDecrypt(C));
     freeCipher(C);*/
   HILL_CIPHER H = createHCipher("XYZ");
    encrypt_h(H);
    prints(NULL,H->cipher_text_v,H->col_size);
    
    // STRING word=(STRING)malloc(sizeof(char)*100);
    // scanf("%s",word);
    // Print("Transposition Cipher");
    // TR_CIPHER T = createTCipher(3, word);
    // encrypt_t(T);
    // getEncryption_t(T);
    // decrypt_t(T);
    // Print(getDecrypted_t(T));
    
    // Print("Affine Cipher");
    // AF_CIPHER A = createACipher(word, 3,5);
    // encrypt_a(A);
    // getEncrypted_a(A);
    // decrypt_a(A);
    // getDecrypted_a(A);
}