#include <iostream>
#include <cmath>
#include <iomanip>
double eps = 1E-5;



double	f1(double x, double y)
{
	return (5 * x - 6 * y + 28 * log10(x) + 16);
}

double	f2(double x, double y)
{
	return (2 * x + y - 10 * log10(y) - 4);
}

double	f1_dx(double x, double y)
{
	return (5 + 28 / (x * log(10)));
}

double	f2_dx(double x, double y)
{
	return (2);
}


double	f1_dy(double x, double y)
{
	return (-6);
}

double	f2_dy(double x, double y)
{
	return (1 - 10 / (y * log(10)));
}

double	dx(double (*f)(double, double), double x, double y)
{
	return ( (f(x + eps/2, y) - f(x - eps/2, y)) / eps );
}

double	dy(double (*f)(double, double), double x, double y)
{
	return ( (f(x, y + eps/2) - f(x, y - eps/2)) / eps );
}

void	invert_yakobian(double yakobian[2][2])
{
		double	det = yakobian[0][0] * yakobian[1][1] - yakobian[0][1] * yakobian[1][0];
		double	invert_yakobian[2][2];

		invert_yakobian[0][0] = yakobian[1][1] / det;
		invert_yakobian[1][1] = yakobian[0][0] / det;
		invert_yakobian[0][1] = -yakobian[0][1] / det;
		invert_yakobian[1][0] = -yakobian[1][0] / det;

		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				yakobian[i][j] = invert_yakobian[i][j];

}

double	calculate_dif(double x, double y)
{
	// std::cin >> eps;
	eps = 1E-5;

	// std::cout << "Начальное приближение: " << std::endl;
	// std::cin >> x >> y;
	
	// x = 0.5, y = 0.5;
	std::cout << "Производные вычисляются" << std::endl;
	std::cout << "Начальное приближение : ";
	std::cout << "x = " << x << " y = " << y <<std::endl << std::endl;
	std::cout << "|step|    x    |    y    |    f1   |   f2    |" << std::endl;


	int i = 0;
	while (i < 30)
	{
		double	yakobian[2][2];	//сменить название на приемлимое
		yakobian[0][0] = dx(f1, x, y);
		yakobian[0][1] = dy(f1, x, y);
		yakobian[1][0] = dx(f2, x, y);
		yakobian[1][1] = dy(f2, x, y);

		invert_yakobian(yakobian);

		double	dx = -yakobian[0][0] * f1(x, y) - yakobian[0][1] * f2(x, y);
		double	dy = -yakobian[1][0] * f1(x, y) - yakobian[1][1] * f2(x, y);
		
		std::cout << "|"
			<< std::setw(4) << i << "|"
			<< std::setw(9) << x << "|"
			<< std::setw(9) << y << "|"
			<< std::setw(9) << f1(x, y) << "|"
			<< std::setw(9) << f2(x, y) << std::endl;
		if (dx*dx + dy*dy < eps * eps)
		{
			break ;
		}
		x += dx;
		y += dy;
		i++;
	}
	
	std::cout << "Корень: x = " << x << " y = " << y <<std::endl;
	std::cout << "____________________________________________" <<std::endl << std::endl;
}



double	analytics_dif(double x, double y)
{
	eps = 1E-5;

	std::cout << "Производные известны" << std::endl;
	std::cout << "Начальное приближение : ";
	std::cout << "x = " << x << " y = " << y <<std::endl << std::endl;
	std::cout << "|step|    x    |    y    |    f1   |   f2    |" << std::endl;


	int i = 0;
	while (true && i < 15)
	{
		double	yakobian[2][2];	//сменить название на приемлимое
		yakobian[0][0] = f1_dx(x, y);
		yakobian[0][1] = f1_dy(x, y);
		yakobian[1][0] = f2_dx(x, y);
		yakobian[1][1] = f2_dy(x, y);

		double	det = yakobian[0][0] * yakobian[1][1] - yakobian[0][1] * yakobian[1][0];
		
		double	dx = (yakobian[1][1] * f1(x, y) - yakobian[0][1] * f2(x, y)) / det;
		double	dy = (yakobian[0][0] * f2(x, y) - yakobian[1][0] * f1(x, y)) / det;
		std::cout << "|"
			<< std::setw(4) << i << "|"
			<< std::setw(9) << x << "|"
			<< std::setw(9) << y << "|"
			<< std::setw(9) << f1(x, y) << "|"
			<< std::setw(9) << f2(x, y) << std::endl;
		if (dx*dx + dy*dy < eps * eps)
		{
			break ;
		}
		x -= dx;
		y -= dy;
		i++;
	}

	std::cout << "Корень: x = " << x << " y = " << y <<std::endl;
	std::cout << "____________________________________________" <<std::endl << std::endl;
}

int	main()
{
	calculate_dif(0.5, 0.2);
	analytics_dif(0.5, 0.2);
	calculate_dif(1.0, 6.0);
	analytics_dif(1.0, 6.0);
}

