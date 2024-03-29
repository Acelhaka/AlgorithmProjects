// FibonaciNumbers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <chrono>    //this header file used to measure time
using namespace std;


int calculateFibonaci(int);

int main()
{	
	
	int number;
	cout << "Enter a number: ";
	cin >> number;
	while (number < 0)
	{
		cout << "ERROR! Your number must be greater than zero." << endl;
		cout << "Enter the number again: ";
		cin >> number;
	}

	cout << endl;

	//starting to measure time by enabling steady_clock
	

	for (int i = 0; i < number; i++) {
		auto startTime = chrono::steady_clock::now();
		//calling the function to calculate Fibunaci number 
		cout << "Fibonacci number for n = " << i <<
			" is " << calculateFibonaci(i ) << endl << endl;

		auto stopTime = chrono::steady_clock::now();
		auto measuredTime = stopTime - startTime;

		cout << "Measured time is ";
		cout << chrono::duration <double, milli>(measuredTime).count() << " ms" << endl;
	}
	system("Pause");
    return 0;
	
}

/*  Function to calculate Fibunaci Number								 //
//  if n is 0, then it will return 0 since the first element is 0		 //
//  if n is 1 then it will return 1 since the first element of			 //
//  the sequence is 0 and the second one is 1, their sum equal to 1		 //
//  if it is a bigger then 1 then by calling itself the function will	 //
//	calculate the sum of the previous elements                           */

int calculateFibonaci(int n) 
{
	if (n == 1)
	{
		return 1;
	}
	if (n == 0)
	{
		return 0;
	}
	return calculateFibonaci(n - 1) + calculateFibonaci(n - 2);
}
