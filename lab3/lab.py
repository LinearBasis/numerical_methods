# пересел на язык python, потому что не видел смысла продолжать писать функции типа "реверс матрицы", если это уже есть готовое


import numpy as np

# Именование идет из стандартного: Ax = b
def solveGauss(A, b):
	if (A.shape[0] != A.shape[1]):
		return []
	n = A.shape[0] # A is matrix with size N x N
	x = np.zeros(n)
	for i in range(0, n):
		for j in range(i + 1, n):
			k = A[j][i] / A[i][i]
			A[j] -= k * A[i]
			b[j] -= k * b[i]
	for i in range(0, n):
		b[i] /= A[i][i]
		A[i] /= A[i][i]
	for i in range(n - 1, -1, -1):
		x[i] = b[i]
		for j in range(i + 1, n):
			x[i] -= A[i][j] * x[j]
	return (x)

def solveStepestDescent(A, b, eps=10**-2):
	if (A.shape[0] != A.shape[1]):
		return []
	n = A.shape[0]
	i = 0

	g = np.dot(A.T, b)
	B = np.dot(A.T, A)
	x = [np.zeros(B.shape[0])]
	r = [np.dot(B, x[0]) - g]
	while not np.dot(r[-1], r[-1]) < eps ** 2:
		tau = np.dot(r[-1], r[-1]) / np.dot(np.dot(B, r[-1]), r[-1])
		x.append(x[-1] - tau * r[-1])
		r.append(np.dot(B, x[-1]) - g)
		i += 1
	return x[-1], i

def solveConjugateGradient(A, b, eps=10**-2):
    g = np.dot(A.transpose(), b)
    A = np.dot(A.transpose(), A)
    x = [np.zeros(A.shape[0])]
    r = [g - np.dot(A, x[0])]
    z = [r[0]]
    i = 0
    while np.dot(r[-1], r[-1]) / np.dot(g, g) > eps ** 2:
        alpha = np.dot(r[-1], r[-1]) / np.dot(np.dot(A, z[-1]), z[-1])
        x.append(x[-1] + alpha * z[-1])
        r.append(r[-1] - alpha * np.dot(A, z[-1]))
        beta = np.dot(r[-1], r[-1]) / np.dot(r[-2], r[-2])
        z.append(r[-1] + beta * z[-1])
        i += 1
    return x[-1], i



def main():
	A = np.array([	[7.4, 2.2, -3.1, -0.7],
					[1.6, 4.8, -8.5, 4.5],
					[4.7, 7.0, -6.0, 6.6],
					[5.9, 2.7, 4.9, -6.3]])
	b = np.array([2.0, 4.0, 6.0, 8.0])
	
	gauss_x = solveGauss(np.copy(A), np.copy(b))

	gradient_x_list = []
	steps_x_list = []

	for i in range(2, 8):
		x, iters = solveStepestDescent(np.copy(A), np.copy(b), eps=10**-i)
		steps_x_list.append((x, iters))
		x, iters = solveConjugateGradient(np.copy(A), np.copy(b), eps=10**-i)
		gradient_x_list.append((x, iters))
	print("Корень, полученный методом Гаусса - ", gauss_x)

	print("\nКорни, полученные методом наискорейшего спуска:")
	for i in range(2, 8):
		print("eps = {},\t x = {},\t количество итераций = {}".format(10**-i, steps_x_list[i - 2][0],steps_x_list[i - 2][1]))
	
	print("\nКорни, полученные методом сопряженных градиентов:")
	for i in range(2, 8):
		print("eps = {},\t x = {},\t количество итераций = {}".format(10**-i, gradient_x_list[i - 2][0],gradient_x_list[i - 2][1]))
	


if __name__ == "__main__":
	main()