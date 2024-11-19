"""
        choosing a prime number 
        a base or generater where g < p and is a primitive 
        root of p
        each party can select a private key of their own - 
        a. b
        
        each party computes a public key using the formula:
        A = g^a mod p
        B = g^b mod p
        
        two parties exchange public keys
        
        shared key computation 
        S = B^a mod P
        S = A^b mod P
"""
import random 
def modular_exponentiation(**kwargs)->int:
    A:int = kwargs['base']
    P:int = kwargs['exponent']
    M:int = kwargs['moduli']
    A = A % M
    P = P % (M-1)
    result:int = 1
    while P > 0:
        
        if P % 2 == 1:
            result = (result * A) % M
        
        P = P // 2
        A = (A * A) % M
    
    return result 
    
    
def get_prime_generator():
    p:int = int(input('Enter a Prime Number: '))
    g:int = int(input('Enter a generator/Primitive root of said prime number: '))
    return p,g

def get_private_key()->int:
    return int(input('Enter your private Key (Alice/Bob): '))

def elgamaal_get_private_key(*args)->int:
    return random.randint(1,args[0])

class KeyExchange:
    P:int
    G:int
    X_a:int
    X_b:int 
    A:int 
    B:int
    S_a:int
    S_b:int
    
    algorithm:str=""
    
    def __init__(self,**kwargs):
        self.P = kwargs['p']
        self.G = kwargs['g']
        match(kwargs['algorithm']):
            case "DH":
                self.X_a = get_private_key()
                self.X_b = get_private_key()
            case 'EG':
                self.X_a = elgamaal_get_private_key(self.P)
                self.X_b = elgamaal_get_private_key(self.P)
            
            case _:
                print('Choose either DH or EG.')
        
        
    def __calc_public_key(self)->None:
        self.A = modular_exponentiation(base=self.G, exponent=self.X_a, moduli=self.P)
        self.B = modular_exponentiation(base=self.G, exponent=self.X_b, moduli=self.P)
    
    def __calc_shared_key(self)->None:
        self.S_a = modular_exponentiation(base=self.B, exponent=self.X_a, moduli=self.P)
        self.S_b = modular_exponentiation(base=self.A, exponent=self.X_b, moduli=self.P)
        
    
    def check_correctness(self)->None:
        if self.S_a == self.S_b:
            print(f'Shared Key Calculation successful. The shared key to access is:{self.S_a} ')
        else:
            print(f'Shared key calculation unsuccessfull. A\'s shared key: {self.S_a}, B\'s shared key: {self.S_b}')
    
    def calculate(self)->None:
        self.__calc_public_key()
        self.__calc_shared_key()
        
        
    
def main():
    prime, generator = get_prime_generator()
    while True:
        algo = input('Enter choice: Diffie Hellman (DH) / Elgamaal (EG) / Exit(X): ')
        if algo == "X":
            break
        ke = KeyExchange(p=prime, g=generator, algorithm=algo)
        ke.calculate()
        ke.check_correctness()

if __name__ == '__main__':
    main()