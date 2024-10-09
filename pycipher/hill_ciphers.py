from __matrix_operations import find_inverse,get_key,matrix_multiplication
import math
def init_matrix(**kwargs)->list[list[int]]:
    x = kwargs['word_length']
    y = kwargs['row']
    z = kwargs['col']
    
    return [[0]*z for _ in range(math.ceil(x/y))]
    
class HillCiphers:
    K:list[list[int]] #key matrix 
    P:list[list[int]] #plain text matrix 
    C:list[list[int]] #cipher text matrix 
    K_inverse:list[list[int]] #key inverse for decryption in hill ciphers
    P_split:list[list[int]] #splitting the plain text into groups of 3.
    C_total:list[list[int]] #produced cipher text will be of dimension 1x3. this matrix stores all of them
    D:list[list[int]] #matrix to store decrypted values 
    D_total:list[list[int]]
    row:int
    col:int
    plain_text:str
    cipher_text:str= ""
    decrypted_text:str=""
    def __init__(self,*args):
        self.plain_text = args[0]
        self.row = self.col = args[1]
        self.K = get_key(key_length=self.row)
        self.K_inverse = find_inverse(key_matrix=self.K)
        self.P_split = [[0]*3 for _ in range(math.ceil(len(args[0])/self.row))]
        self.P = [[]*self.col]
        self.C_total = init_matrix(word_length=len(args[0]), row=self.row, col=self.col)
        self.D_total = init_matrix(word_length=len(args[0]), row=self.row, col=self.col)
    
    def __split_plain_text(self)->None:
        while True:
            if len(self.plain_text)%3 != 0:
                self.plain_text += "X"
            else:
                break
        tmp:list[str] = [self.plain_text[i:i+3] for i in range(0,len(self.plain_text),3)]
        for i in range(len(tmp)):
            self.P_split[i] = [ord(i) for i in tmp[i]]
    
    def __get_encrypted(self)->str:
        return self.cipher_text
    def __get_decrypted(self)->str:
        return self.decrypted_text
    def encrypt(self)->None:
        self.__split_plain_text()
        for index,splits in enumerate(self.P_split):
            self.P[0] = [(i-65)%26 for i in splits]
            self.C = matrix_multiplication(key_matrix=self.K,pc_matrix=self.P)
            if not self.C:
                print('Error in Multiplication')
                break
            self.C_total[index] = [i for i in self.C[0]]
            self.C = [[i+65 for i in self.C[0]]]
            self.cipher_text += "".join([chr(i) for i in self.C[0]])
    def decrypt(self)->None:
        try:
            for index,cipher_splits in enumerate(self.C_total):
                self.C = [cipher_splits]
                self.D = matrix_multiplication(key_matrix=self.K_inverse, pc_matrix=self.C)
                if not self.D:
                    print('Error in Multiplcation')
                self.D_total[index] = [i for i in self.D[0]]
                self.D = [[i+65 for i in self.D[0]]]
                self.decrypted_text += "".join([chr(i) for i in self.D[0]])
        except:
            print('Index Errors')
    
    def cipher_results(self)->None:
        print(f'The encrypted Message is:{self.__get_encrypted()}')
        print(f'The Decrypted Message is:{self.__get_decrypted()}')      

def main():
    hc = HillCiphers(input('Enter Message to Be Encrypted: '), 3)
    hc.encrypt()
    hc.decrypt()
    hc.cipher_results()
    
if __name__ == '__main__':
    main()