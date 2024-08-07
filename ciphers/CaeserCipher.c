#include "ciphers.h"
STRING initString(STRING S, int size){
	S = (STRING)malloc(sizeof(char)*size);
	if(isEmpty(S))
		FatalError("Out of Memory");
	return S;
}

BOOL isEmpty(STRING str){
	return str == NULL;
}

CAESER_CIPHER init(){
	CAESER_CIPHER C = NULL;
	C = (PTR)malloc(sizeof(struct CaeserCipher));
	if(C==NULL)
		FatalError("Out of Memory Space");
	C->k = 3;
	C->size = 0;
	return C;
	
}

void PlainText(CAESER_CIPHER C, STRING plainText){
	if(!C)
		Warning("initialise structure first");
	C->size = strlen(plainText);
	C->plain = initString(C->plain,C->size);
	C->encrypted = initString(C->encrypted,C->size);
	C->decrypted = initString(C->decrypted, C->size);
	strncpy(C->plain, plainText,strlen(plainText));
	C->plain[C->size] = '\0';
	
}
void Encrypt(CAESER_CIPHER C){
	int placeHolder;
	for(int i=0;i<C->size;i++){
		placeHolder = ((int)C->plain[i])-97;
		placeHolder = (placeHolder +C->k)%26;
		C->encrypted[i] = placeHolder+97;
	}
}

void Decrypt(CAESER_CIPHER C){
	int placeHolder;
	for(int i=0;i<C->size;i++){
		placeHolder = ((int)C->encrypted[i])-97;
		placeHolder = ((placeHolder-C->k)+26)%26;
		C->decrypted[i] = placeHolder + 97;
	}

}

int main(int argc, char**argv){
	CAESER_CIPHER C = init();
	PlainText(C,"abcd");
	Encrypt(C);
	Decrypt(C);
	printf("%s\n",C->plain);
	printf("%s\n",C->encrypted);
	printf("%s\n",C->decrypted);
}