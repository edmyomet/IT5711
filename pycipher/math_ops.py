def get_key(**kwargs)->list[list[int]]:
	n = kwargs['key_length']
	x:list[list[int]] = [[0]*n for _ in range(n)]
	
	for i in range(n):
		for j in range(n):
			x[i][j] = int(input(f'Enter Key Element ({i+1}, {j+1}): '))
	
	return x

def find_modulo_inverse(**kwargs)->int:
	x:int = kwargs['num']
	
	if x%2 == 0:
		print(f'modulo inverse of {x}, 26 is not possible, choose another matrix with compatible determinant')
		return 0
	
	for i in range(26):
		if (x*i) % 26 == 1:
			return i


def find_determinant(**kwargs)->int:
	a:list[list[int]] = kwargs['matrix']
	
	d:float = a[0][0] * ( (a[1][1]*a[2][2]) - (a[2][1]*a[1][2]) ) - a[1][0] * ( (a[0][1]*a[2][2]) - (a[0][2]*a[2][1]) ) + a[2][0] * ( (a[0][1]*a[1][2]) - (a[1][1]*a[0][2]) )
	
	return d

def find_cofactor(**kwargs)->list[list[int]]:
	x:list[list[int]] = kwargs['matrix']
	
	cofactor:list[list[int]] = [[0]*len(x) for _ in range(len(x))]
	
	cofactor[0][0] = ((x[1][1]*x[2][2]) - (x[2][1]*x[1][2]))
	cofactor[0][1] = -((x[1][0]*x[2][2]) - (x[2][0]*x[1][2]))
	cofactor[0][2] = ((x[1][0]*x[2][1]) - (x[2][0]*x[1][1]))

	
	cofactor[1][0] = -((x[0][1]*x[2][2]) - (x[2][1]*x[0][2]))
	cofactor[1][1] = ((x[0][0]*x[2][2]) - (x[2][0]*x[0][2]))
	cofactor[1][2] = -((x[0][0]*x[2][1]) - (x[2][0]*x[0][1]))
	
	
	cofactor[2][0] = ((x[0][1]*x[1][2]) - (x[1][1]*x[0][2]))
	cofactor[2][1] = -((x[0][0]*x[1][2]) - (x[1][0]*x[0][2]))
	cofactor[2][2] = ((x[0][0]*x[1][1]) - (x[1][0]*x[0][1]))

	return cofactor
	

def find_transpose(**kwargs)->list[list[int]]:
	x = kwargs['matrix']
	trans:list[list[x]] = [[0]*len(x) for _ in range(len(x))]
		
	for i in range(len(x)):
		for j in range(len(x)):
			trans[i][j] = x[j][i]
	
	return trans 


def find_inverse(**kwargs)->list[list[int]]:
	x:list[list[int]] = kwargs['matrix']
	
	determinant:int = find_determinant(matrix=x)
	determinant_inverse:int = find_modulo_inverse(num=determinant)
	if not determinant:
		print('Matrix with determinant 0 cannot have an inverse')
		return None 
		
	if not determinant_inverse:
		print('Determinant must not be even')
		return None
	
	adjoint = find_transpose(matrix=find_cofactor(matrix=x))
	
	inverse:list[list[int]] = [[0]*len(x) for _ in range(len(x))]

	for i in range(len(x)):
		for j in range(len(x)):
			inverse[i][j] = ((determinant_inverse % 26) * (adjoint[i][j]%26)) % 26
	
	return inverse

def matrix_multiplication(**kwargs)->list[list[int]]:
	P:list[list[int]] = kwargs['A']
	K:list[list[int]] = kwargs['B']
	
	if len(P[0]) != len(K) or not P  or not K:
		print('Matrix dimensions incompatible for multiplication')
		return None
	
	prod:list[list[int]] = [[0]*len(P[0]) for _ in range(len(P))]
	
	for i in range(len(P)):
		for j in range(len(K)):
			for k in range(len(P[0])):
				prod[i][j] += P[i][k] * K[k][j]
			
			prod[i][j] %= 26
	
	return prod 


def main():
	matrix = get_key(key_length=3)
	inverse = find_inverse(matrix=matrix)
	
	print(inverse)
	
if __name__ == '__main__':
	main()
				
	
			
	
	 
	
	
	