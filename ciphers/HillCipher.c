#include "ciphers.h"

VECT assignVector(MATRIX ARR,SIZE R, SIZE C){
    ARR = (MATRIX)malloc(sizeof(PTR_I)*R);
    if(ARR==NULL)
        FatalError("Out of Memory");
    for(int i=0;i<R;i++){
        ARR[i] = (PTR_I)malloc(sizeof(int)*C);
        if(ARR[i]==NULL)
            FatalError("Out of Memory Space");
    }
    return ARR;
}

HILL_CIPHER init_h(STRING P){
    HILL_CIPHER H = NULL;
    H = (HILL_CIPHER)malloc(sizeof(struct HillCipher));
    if(H==NULL)
        FatalError("Out of Memory");
    H->plain = (STRING)malloc(sizeof(char)*strlen(P));
    strncpy(H->plain, P, strlen(P));
    H->plain[strlen(P)] = '\0';
    H->row_size_ = strlen(P);
    H->col_size_ = strlen(P);
    H->v_len_ = 1;
    initKeyMatrix(H);
    initPTM(H);
}

void initKeyMatrix(HILL_CIPHER H){
    H->keyMatrix = (MATRIX)malloc(sizeof(PTR_I)*H->row_size_);
    Print("Key Matrix Initialisation");
    for(int i = 0; i<H->row_size_;i++){
        H->keyMatrix[i] = (PTR_I)malloc(sizeof(int)*H->col_size_);
        for(int j=0;j<H->col_size_;j++){
            H->keyMatrix[i][j] = 65 + (random()%26);
            printf("%d\t", H->keyMatrix[i][j]);
        }   
        printf("\n");
    }
}

void initPTM(HILL_CIPHER H){
    H->PTM = assignVector(H->PTM,1,H->col_size_);
    H->ENC = assignVector(H->ENC,1,H->col_size_);
    H->DEC = assignVector(H->DEC,1,H->col_size_);
    for(int i=0;i<H->col_size_;i++){
        H->PTM[0][i] = ((int)H->plain[i])-65;
        H->ENC[0][i] = 0;
        H->DEC[0][i] = 0;
    }
}

void EncryptHill(HILL_CIPHER H){
    for(int i=0;i<H->v_len_;i++){
        for(int j=0;H->col_size_;j++){
            for(int k=0;k<H->row_size_;k++){
                H->ENC[i][j] += H->PTM[i][k] * H->keyMatrix[k][j];
                printf("%d\t", H->ENC[i][j]);
            }
            printf("\n");
                
        }
    }
    for(int i=0;i<H->col_size_;i++)
        printf("%d\t", H->ENC[0][i]);
}
int main(){
    HILL_CIPHER  H = init_h("ABC");
    EncryptHill(H);
    return 0;
}