#include "caesercipher.h"
#include "hillcipher.h"
#include "affinecipher.h"
#include "transpcipher.h"


int main(int argc, char**argv){
    CAESER_CIPHER C = createCipher("SHRUTHI");
    encrypt(C);
   printf("%s\n", retrieveCipherText(C));
   decrypt(C);
     printf("%s\n", retrieveDecrypt(C));
}