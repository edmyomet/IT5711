def get_key(**kwargs)->list[list[int]]: 
    x:list[list[int]] = [[0]*kwargs['key_length'] for i in range(kwargs['key_length'])]
    for i in range(kwargs['key_length']):
        for j in range(kwargs['key_length']):
            x[i][j] = int(input(f'enter key element {i+1},{j+1}: '))
    return x


def find_determinant(**kwargs)->int:
    #determinant expansion by column 1
    a:list[list[int]] = kwargs['key_matrix'] #key matrix stored as a temp variable
    #finding the determinant without mod26
    d:float = (a[0][0]*((a[1][1]*a[2][2])-(a[1][2]*a[2][1]))) - (a[1][0]*((a[0][1]*a[2][2])-(a[2][1]*a[0][2]))) + (a[2][0]*((a[0][1]*a[1][2])-(a[0][2]*a[1][1])))
    #finding d mod 26
    #determinant:int = d%26
    return d



def find_cofactor(**kwargs)->list[list[int]]:
    x:list[list[int]] = kwargs['key_matrix']
    if len(x) != 3:
        print(f'Find inverse using a simpler method')
    cofactor:list[list[int]] = [[0]*len(x) for _ in range(len(x))]
    #finding the cofactor for every element in the key matrix to form the cofactor matrix 
    #row - 1
    cofactor[0][0] = (x[1][1]*x[2][2]) - (x[2][1]*x[1][2])
    cofactor[0][1] = -((x[1][0]*x[2][2])-(x[2][0]*x[1][2]))
    cofactor[0][2] = (x[1][0]*x[2][1]) - (x[1][1]*x[2][0])
    
    #row - 2
    cofactor[1][0] = -((x[0][1]*x[2][2])-(x[0][2]*x[2][1]))
    cofactor[1][1] = (x[0][0]*x[2][2]) - (x[0][2]*x[2][0])
    cofactor[1][2] = -((x[0][0]*x[2][1])-(x[0][1]*x[2][0]))

    #row - 3
    cofactor[2][0] = (x[0][1]*x[1][2])-(x[0][2]*x[1][1])
    cofactor[2][1] = -((x[0][0]*x[1][2])-(x[1][0]*x[0][2]))
    cofactor[2][2] = (x[0][0]*x[1][1])-(x[0][1]*x[1][0])
    
    return cofactor


def transpose(**kwargs)->list[list[int]]:
    #function to find the transpose of a given matrix, in this case the cofactor matrix
    x = kwargs['cofactor_matrix']
    trans:list[list[int]] = [[0]*len(x) for _ in range(len(x))]
    #performing transpose = inverting rows and columns 
    for i in range(len(x)):
        for j in range(len(x[0])):
            trans[i][j] = x[j][i]
    return trans


def find_modulo_inverse(**kwargs)->int:
    '''
    function to find modulo inverse of a number with 26.
    for example, 9^-1mod26 = 3 as 9*3mod26=1
    '''
    x:int = kwargs['key']
    reduced_mod:int=26
    #even numbers cannot have an inverse with 26, therefore reducing the equation to x//2mod13
    if x%2==0:
        print('cannot find modulo inverse')
        return 0
    for i in range(reduced_mod):
        if (x*i)%reduced_mod == 1:
            return i
        

def find_inverse(**kwargs)->list[list[int]]:
    '''
    1. find cofactor, then transpose of cofactor
    2. find determinant inverse mod 26
    3. multiply adjoint elements by determinant inverse
    4. mod 26
    '''
    key:list[list[int]] = kwargs['key_matrix']
    determinant:int = find_determinant(key_matrix=key)
    if determinant == 0:
        print('Matrix with determinant 0 cannot have an inverse')
        return None
    adjoint:list[list[int]] = transpose(cofactor_matrix=find_cofactor(key_matrix=key))
    determinant_inverse = find_modulo_inverse(key=determinant)
    if determinant_inverse==0:
        print('Matrix Not invertible')
        return None
    key_inverse:list[list[int]] = [[0]*len(key) for _ in range(len(key))]
    for i in range(len(key)):
        for j in range(len(key[0])):
            key_inverse[i][j] = ((determinant_inverse%26)*(adjoint[i][j]%26))%26
    return key_inverse


def matrix_multiplication(**kwargs)->list[list[int]]:
    x = kwargs['key_matrix'] #key matrix, of dimensions 3x3 for the given problem. any other dimension will be handled
    y = kwargs['pc_matrix']   #matrix of plain texts, 1x3 for the given problem , or cipher text for decryption problem
    if len(y[0]) != len(x) or not x or not y:
        print(f'Matrix Dimensions incompatible for multiplication/Empty MAtrices')
        return None
    z = [[0]*len(y[0]) for _ in range(len(y))]
    for i in range(len(y)):
        for j in range(len(x)):
            for k in range(len(y[0])):
                z[i][j] += y[i][k]*x[k][j]
            z[i][j] %= 26
    return z
    
    
def main():
    pass

if __name__ == '__main__':
    main()
