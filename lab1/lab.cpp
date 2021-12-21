#include <iostream>
#include <cmath>
#include <utility>

#define EPSILON 1E-5
using namespace std;

double	my_func(double x)
{
	return (pow(x, 2) + 4 * sin(x) - 1);
}

double	my_func_derivative(double x)
{
	return (2 * x + 4 * cos(x));
}

//	returned value - <root, iterations> 
pair<double, int>	dihotomy(double left, double right, double (*func)(double), double eps=EPSILON)
{
	int iter = 0;
	double mean = (left + right) / 2;
	while (abs(left - right) >= eps)
	{
		mean = (left + right) / 2;
		iter++;
		if (my_func(left) * my_func(mean) < 0)
			right = mean;
		else
			left = mean;
	}
	return (make_pair(mean, iter));
}

pair<double, int>	iterations(double left, double right, double (*func)(double), double eps=EPSILON)
{
	int iter = 0;
	double t = 2.0 / abs(my_func_derivative(left) + my_func_derivative(right));
	double x = right;
	int sign = 1;
	if (my_func_derivative(left) < 0)
		sign = -1;
	while (abs(my_func(x)) > EPSILON)
	{
		x = x - sign * t * my_func(x);
		++iter;
	}

	return (make_pair(x, iter));
}



int	main()
{

	double first_left = -3.0;
	double first_right = -2.0;

	double second_left = 0.0;
	double second_right = 0.5;


	cout << "	МЕТОД ДИХОТОМИИ : " << endl;
	cout << "первый корень и количество итераций : " << endl;
	auto ans = dihotomy(second_left, second_right, my_func);
	cout << ans.first << " : " << ans.second << endl;
	cout << "Проверка: значение функции в найденном корне = " << my_func(ans.first) << endl;  
	cout << endl;



	cout << "второй корень и количество итераций : " << endl;
	ans = dihotomy(first_left, first_right, my_func);
	cout << ans.first << " : " << ans.second << endl;
	cout << "Проверка: значение функции в найденном корне = " << my_func(ans.first) << endl;  
	cout << endl << endl;


	cout << "	МЕТОД ПРОСТЫХ ИТЕРАЦИЙ : " << endl;
	cout << "первый корень и количество итераций : " << endl;
	ans = iterations(second_left, second_right, my_func);
	cout << ans.first << " : " << ans.second << endl;
	cout << "Проверка: значение функции в найденном корне = " << my_func(ans.first) << endl;  
	cout << endl;

	cout << "второй корень и количество итераций : " << endl;
	ans = iterations(first_left, first_right, my_func);
	cout << ans.first << " : " << ans.second << endl;
	cout << "Проверка: значение функции в найденном корне = " << my_func(ans.first) << endl;  
}

