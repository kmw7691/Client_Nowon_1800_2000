#pragma once
//선언
int sum(int a, int b),  sub(int a, int b),  div(int a, int b),  mul(int a, int b),  mod(int a, int b);

//정의
int sum(int a, int b) {
	return a + b;
}

int sub(int a, int b) {
	return a - b;
}


int div(int a, int b) {
	return a / b;
}


int mul(int a, int b) {
	return a * b;
}


int mod(int a, int b) {
	return a % b;
}

int factorial(int n) {
	if (n < 1)
		return 0;
	else if (n == 1)
		return 1;
	else
		return n * factorial(n-1);
}