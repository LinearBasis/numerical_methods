from math import *

def function(x):
	return cos(x**2 / 4)


def simpsonMethod(f, a, b, n):
	h = (b - a) / n
	k1, k2 = 0, 0
	for i in range(1, n, 2):
		k1 += f(a + i * h)
		k2 += f(a + (i + 1) * h)

	return h / 3 * (f(a) + 4 * k1 + 2 * k2)


def trapezeMethod(f, a, b, n):
	if n == 0:
		return 0.0

	sum = 0.0
	step = (b - a) / (1.0 * n)
	for i in range(1, n):
		sum += f(a + i * step)

	sum += (f(a) + f(b)) / 2
	sum *= step
	return sum


def main():
	eps = 1e-5
	a, b = 0, 0.5

	n = 2
	prev = trapezeMethod(function, a, b, n)
	while True:
		n *= 2
		trapezoidRes = trapezeMethod(function, a, b, n)
		if fabs(trapezoidRes - prev) <= eps / 2:
			break
		prev = trapezoidRes
	trapezoidRichardson = (2**2 * trapezeMethod(function, a, b, n * 2)
											- trapezoidRes) / (2**2 - 1)
	trapezoidRichardson = round(trapezoidRichardson, 6)
	trapezoidRes = round(trapezoidRes, 6)
	print('Метод Трапеций')
	print('Значение интеграла = {} (число разбиений = {})'.format(trapezoidRes, n))
	print('Значение интеграла после уточнения методом Ричардсона = {}'.format(trapezoidRichardson))

	n = 2
	while True:
		prev = simpsonMethod(function, a, b, n)
		n *= 2
		simpsonRes = simpsonMethod(function, a, b, n)
		if fabs(simpsonRes - prev) <= eps:
			break
	simpsonRichardson = (2**4 * simpsonMethod(function, a, b, n * 2) - simpsonRes) / (2**4 -1)
	simpsonRichardson = round(simpsonRichardson, 6)
	simpsonRes = round(simpsonRes, 6)
	print('Метод Симпсона:')
	print('\nЗначение интеграла = {} (число разбиений = {})'.format(simpsonRes, n))
	print('Значение интеграла после уточнения методом Ричардсона = {}'.format(simpsonRichardson))


if __name__ == '__main__':
	main()	