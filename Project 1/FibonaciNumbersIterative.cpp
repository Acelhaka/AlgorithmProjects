// FibonaciNumbersIterative.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
using namespace std;
#include <ctime>

int main()
{
	int start_s = clock();
	// the code you wish to time goes here
	

	int subscript;
	int *fibonaciArray = NULL;
	//int fibonaciArray[1] = 1;

	cout << "Enter the subscript: ";
	cin >> subscript;
	
	long firstPosition = 0;
	long secondPosition = 1;
	long fibonaciNumber = 0;

	for (int i = 2; i <= subscript; i++)
	{
		//fibonaciArray[i] = fibonaciArray[i - 1] + fibonaciArray[i - 2];
		//cout << fibonaciArray[i] << endl;
		//fibonaciNumber = fibonaciArray[i];
		fibonaciNumber = firstPosition + secondPosition;
		firstPosition = secondPosition;
		secondPosition = fibonaciNumber;

	}
	
		cout << "Fibonaci Number of position " << subscript << " = " << fibonaciNumber << endl;
	
	int stop_s = clock();
	cout << "time: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) << endl;
		system("Pause");
    return 0;
}

