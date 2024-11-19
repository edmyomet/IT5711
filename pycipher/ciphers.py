import math
from math_ops import get_key, find_modulo_inverse, matrix_multiplication, find_inverse

def init_matrix(**kwargs)->list[list[int]]:
	x = kwargs['word_length']
	y = kwargs['row']
	z = kwargs['col']
	
	return [[0]*z for _ in range(math.ceil(x/y))]
class text:
	plain_text:str=""
	cipher_text:str=""
	decrypted_text:str=""
	
	def __init__(self,*args):
		self.plain_text = args[0]
	
	
	def __get_encrypted(self)->str:
		return self.cipher_text
	
	def __get_decrypted(self)->str:
		return self.decrypted_text
	def results(self)->None:
		print(f'The plain text is: {self.plain_text}')
		print(f'The encrypted text is: {self.__get_encrypted()}')
		print(f'The decrypted text is: {self.__get_decrypted()}')
		
class HillCipher(text):
	P:list[list[int]]
	K:list[list[int]]
	C:list[list[int]]
	D:list[list[int]]
	
	K_inverse:list[list[int]]
	
	P_split:list[list[int]]
	C_total:list[list[int]]
	D_total:list[list[int]]
	
	row:int
	col:int
	
	def __init__(self,*args):
		self.row = args[0]
		self.col = args[1]
		
		super().__init__(args[2])
		
		self.P = [[]*self.col]
		self.K = get_key(key_length=self.row)
		self.K_inverse = find_inverse(matrix=self.K)
		
		self.P_split = init_matrix(word_length=len(self.plain_text),row=self.row, col=self.col)
		self.C_total = init_matrix(word_length=len(self.plain_text),row=self.row, col=self.col)
		self.D_total = init_matrix(word_length=len(self.plain_text),row=self.row, col=self.col)
		
	def __split(self)->None:
		
		while True:
			if len(self.plain_text) % 3 != 0:
				self.plain_text += "X"
			else:
				break
		tmp:list[str] = [self.plain_text[i:i+3] for i in range(0,len(self.plain_text), 3)]
		
		for i in range(len(tmp)):
			self.P_split[i] = [ord(j) for j in tmp[i]]
	
	def encrypt(self)->None:
		self.__split()
		
		for index, splits in enumerate(self.P_split):
			self.P[0] = [(i-65)%26 for i in splits]
			self.C = matrix_multiplication(A=self.P, B=self.K)
			if not self.C:
				print('Error in Encryption')
				break
			self.C_total[index] = self.C[0]
			
			self.C = [[i+65 for i in self.C[0]]]
			
			self.cipher_text += "".join([chr(i) for i in self.C[0]])
		
	def decrypt(self)->None:
		for index,csplits in enumerate(self.C_total):
			self.C = [csplits]
			self.D = matrix_multiplication(A=self.C, B=self.K_inverse)
			if not self.D:
				print('Decryption error')
			
			self.D_total[index] = self.D
			
			self.D = [[i+65 for i in self.D[0]]]
			
			self.decrypted_text += "".join([chr(i) for i in self.D[0]])
	
	
	
			
		

class CaeserCipher(text):
	key:int = 0
	def __init__(self, *args):
		super().__init__(args[0])
		self.key = args[1]
	
	def encrypt(self)->None:
		tmp:list[int] = [((ord(c)-65 + self.key + 26)%26) for c in self.plain_text]
		
		self.cipher_text = "".join([chr(i+65) for i in tmp])
	
	def decrypt(self)->None:
		tmp:list[int] = [((ord(c)-65 - self.key + 26)%26) for c in self.cipher_text]
		
		self.decrypted_text = "".join([chr(i+65) for i in tmp])
	
		
		

class AffineCipher(text):
	A:int = 0 
	B:int = 0
	A_inverse:int = 0
	def __change(self):
		self.A = int(input('Enter another \'A\' Value: '))
		self.A_inverse = find_modulo_inverse(num=self.A)
	def __init__(self, *args):
		super().__init__(args[0])
		self.A = args[1]
		self.B = args[2]
		self.A_inverse = find_modulo_inverse(num=self.A)
		
		if self.A_inverse == 0:
			print(f'Modulo inverse of entered A value is 0. resetting...')
			self.__change()
	
	
	def encrypt(self)->None:
		tmp:list[int] = [(ord(i)-65)%26 for i in self.plain_text] 
		
		tmp = [(self.A*x + self.B)%26 for x in tmp]
		
		self.cipher_text = "".join([chr(i+65) for i in tmp])
	
	def decrypt(self)->None:
		tmp:list[int] = [(ord(i)-65)%26 for i in self.cipher_text]
		
		tmp = [(self.A_inverse * (x - self.B))%26 for x in tmp]
		
		self.decrypted_text = "".join([chr(i+65) for i in tmp])
	

class RailFenceCipher(text):
	C:list[list[str]]
	depth:int
	T:list[list[str]]
	def __init__(self, *args):
		super().__init__(args[0])
		self.depth = args[1]
		
		self.C = [[""]*len(self.plain_text) for _ in range(self.depth)]
		self.T = [[""]*self.depth for _ in range(len(self.plain_text))]
	
				
	def encrypt(self)->None:
		count:int = 0
		i:int = 0
		j:int = 0
		
		while count < len(self.plain_text):
			if (i < self.depth):
				self.C[i][j] = self.plain_text[count]
				i+=1
				count += 1
			else:
				i, j = 0, j+1
		
		
		self.cipher_text = "".join(["".join(item) for item in self.C])
	
	def decrypt(self)->None:
		for i in range(len(self.C)):
			for j in range(len(self.C[0])):
				self.T[j][i] = self.C[i][j]
		
		self.decrypted_text = "".join(["".join(c) for c in self.T])
			


                
                
class RowTransCipher:
	pass

def main():
	while True:
		print(f'Choose a Cipher Technique')
		print('1. Caeser Cipher (1)')
		print('2. Hill Cipher (2)')
		print('3. Affine Cipher (3)')
		print('4. Rail Fence Cipher (4)')
		print('5. Row Transposition Cipher (5)')
		print('6. Playfair Cipher (6)')
		print('7. Exit (999)')
		
		choice = int(input('Enter choice (1/2/3/4/5/6/999) : '))
		
		match(choice):
			case 2:
				hc = HillCipher(3,3,input('Enter Message to be Encrypted: '))
				hc.encrypt()
				hc.decrypt()
				hc.results()
	
			case 1:
				cc = CaeserCipher(input('Enter Message to be Encrypted: '), 3)
				cc.encrypt()
				cc.decrypt()
				cc.results()
			
			case 3:
				ac = AffineCipher(input('Enter Message to be Encrypted: '), 3, 9)
				ac.encrypt()
				ac.decrypt()
				ac.results()
			
			case 4:
				rc = RailFenceCipher(input('Enter Message to be Encrypted: '), 3)
				rc.encrypt()
				rc.decrypt()
				rc.results()
            
			case 999:
				break

			case _:
				print('Chosen option does not exist')
    
				
	


if __name__ == '__main__':
	main()