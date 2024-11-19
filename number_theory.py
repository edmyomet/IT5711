import math 

def get_equation_values()->list[list[int]]:
    mat:list[list[int]] = [[0]*4 for _ in range(3)]
    for i in range(3):
        print(f'Please enter values for a{i+1}, and m{i+1} in the equation X = a{i+1} mod m{i+1}')
        a:int = int(input(f'Enter a{i+1}: '))
        m:int = int(input(f'Enter m{i+1}: '))
        mat[i][0] = a
        mat[i][1] = m
    return mat

def find_modulo_inverse(**kwargs)->int:
    x = kwargs['num']
    y = kwargs['mod']
    for i in range(y):
        if (x*i)%y == 1:
            return i
    return 0
def extended_euclidean_algorithm(**kwargs)->dict:
    A:int = kwargs['dividend']
    B:int = kwargs['divisor']
    Q:int
    R:int 
    T1:int = 0
    T2:int = 1
    T:int = 0
    while B:
        Q = A//B
        R = A%B
        T = T1 - (T2*Q)
        A = B
        B = R
        T1 = T2
        T2 = T
    return {'Quotient':Q, 'T1':T1,'T2':T2,'GCD':A}

def chinese_remainder_theorem()->None:
    """
        X = a1 mod m1
        X = a2 mod m2
        X = a3 mod m3
        
        M1 = m2 * m3
        M2 = m1 * m3
        M3 = m1 * m2
        
        X = summation ai * Mi * Mi_inverse
    """
    
    x:int = 0
    prod:int = 1
    value_matrix:list[list[int]] = [[0]*4 for _ in range(3)]
    value_matrix = get_equation_values()
    
    value_matrix[0][2] = value_matrix[1][1] * value_matrix[2][1]
    value_matrix[1][2] = value_matrix[0][1] * value_matrix[2][1]
    value_matrix[2][2] = value_matrix[0][1] * value_matrix[1][1]
    
    for i in range(3):
        prod *= value_matrix[i][1]
    
    for i in range(3):
        #value_matrix[i][3] = extended_euclidean_algorithm(dividend=value_matrix[i][2],divisor=value_matrix[i][1])['T1']
        value_matrix[i][3] = find_modulo_inverse(num=value_matrix[i][2], mod=value_matrix[i][1])
    
    for i in range(3):
        tmp:int=1
        x += value_matrix[i][0] * value_matrix[i][2] * value_matrix[i][3]
    
    x = x % prod
    
    print(f'The value of X  satisfying the congruences is: {x}')
    

def fermat_little_theorem()->None:
    print('Please enter values of base, exponent and modulus in the form: base ^ exponent - 1 = 1 mod exponent')
    
    A:int = int(input('Enter the base (a): '))
    P:int = int(input('Enter the exponent (p): '))
    M:int = int(input('Enter the modulus (m): '))
    result:int = 1
    A %= M
    P = P % (M-1)
    while P > 0:
        
        if P % 2 == 1:
            result = (result * A) % M
        
        P = P // 2
        A = (A*A) % M
    
    print(f'The result after modulo exponentiation operation is: {result}')       
    

def euler_totient_function()->None:
    pass

def main()->None:
    
    #for key,value in extended_euclidean_algorithm(dividend=26, divisor=6).items():
       # print(key,value)
    
    #chinese_remainder_theorem()
    fermat_little_theorem()
    

if __name__ == '__main__':
    main()
        