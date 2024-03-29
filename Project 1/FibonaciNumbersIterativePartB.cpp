// FibonaciNumbersIterative.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;


int fibonacciFunction(int);

int main()
{
	
	int subscript;

	cout << "Enter the subscript: ";
	cin >> subscript;

	while (subscript < 0)
	{
		cout << "ERROR! Your number must be greater than zero." << endl;
		cout << " Enter the subscript again: ";
		cin >> subscript;
	}
	
	
	
		cout << "Fibonaci number of subscript = " << subscript << " is " << 
			fibonacciNumber(subscript) << endl;
	

		system("Pause");
    return 0;
}

int fibonacciNumber(int n)
{
	int firstPosition = 0;
	int secondPosition = 1;
	int fibonacciNumber = 0;

	for (int i = 2; i <= n; i++)
	{

		fibonacciNumber = firstPosition + secondPosition;
		firstPosition = secondPosition;
		secondPosition = fibonacciNumber;

	}
	return fibonacciNumber;
}