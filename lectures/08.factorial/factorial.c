#include <stdio.h>

int fact(int n);
int fib(int n);
int collatz(int n);

int main(int argc, char *argv[])
{
	int x = fact(3);
	int y = fib(10);
	int z = collatz(7);

	printf("%i\n", x);
	printf("%i\n", y);
	printf("%i\n", z);

	return 0;
}

int fact(int n)
{
	if(n == 1)
		return 1;

	return n * fact(n - 1);
}

int fib(int n)
{
	if(n == 0) return 0;
	if(n == 1) return 1;

	return fib(n - 1) + fib(n - 2);
}

int collatz(int n)
{
	if(n == 1)
		return 0;

	if(n % 2 == 0)
		return collatz(n / 2) + 1;

	else
		return collatz(n * 3 + 1) + 1;
}
