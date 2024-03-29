/************************************************************
*															*
*				   Amarilda Celhaka							*
*				 Programming Project #2						*
*			Design and Analysis of Algorithms				*
*Performing empirical analysis of the sorting algorithms	*
*(a)	selection sort;										*
*(b)	insertion sort;										*
*(c)	two versions of a bubble sort: with and without		*
*		counting the number of swaps						*
*(d)	quicksort;											*
*(e)	mergesort.											*
*															*
*															*
*************************************************************/




#include "stdafx.h"
#include <iostream>
#include <stdlib.h>     // srand 
#include <time.h>		// to set seed
#include <chrono>		// to measure time
#include <cassert>
using namespace std;




//definitions of sorting algorithms functions
void selectionSort(int array[], int size);
void insertionSort(int array[], int size);
void bubbleSortWithoutSwaps(int array[], int size);
void bubbleSortWithSwaps(int array[], int size);
void quickSort(int array[], int p, int r);
int partion(int array[], int p, int r);
void merge(int *array, int p, int q, int r);
void mergeSort(int *array, int p, int r);

// definitions of functions that measure the time of sorting algorithms
void selectionSortTime();
void insertionSortTime();
void bubbleSortWithoutSwapsTime();
void bubbleSortWithSwapsTime();
void quickSortTime();
void mergeSortTime();

void exchange(int *first, int *second); //to exchange 2 elements of an array
void printArray(int array[], int size); //to print an array, sorted or not, for testing reasons
int *arrayOfSorted(int size);			//creating an array of sorted elements


int main()
{

	cout << "************************************************" << endl;
	cout << "   		Amarilda Celhaka		    		 " << endl;
	cout << "		 Programming Project #2					 " << endl;
	cout << "	Design and Analysis of Algorithms			 " << endl;
	cout << "************************************************" << endl << endl << endl;;
	/**initializng random seed*/
	srand(time(NULL));

	/*calling the function that will display the time of selection sort algorithm*/
	selectionSortTime();
	cout << "\n\n\n\n";

	/*calling the function that will display the time of insertion sort algorithm*/
	insertionSortTime();
	cout << "\n\n\n\n";

	/*calling the function that will display the time of bubble sort without     *
	 *  counting the number of swaps											 */
	bubbleSortWithoutSwapsTime();
	cout << "\n\n\n\n";

	/*calling the function that will display the time of bubble sort             *
	*  counting the number of swaps											     */
	bubbleSortWithSwapsTime();
	cout << "\n\n\n\n";

	/*calling the function that will display the time of quick sort algorithm    */
	quickSortTime();
	cout << "\n\n\n\n";

	/*calling the function that will display the time of merge sort algorithm    */
	mergeSortTime();
	cout << "\n\n\End of Program" << endl;



	system("Pause");
	return 0;
}



/* *******************************************
*	     selectionSort()					 *
*	This Function will sort arrays using	 *
*	the selection sort						 *
**********************************************/

void selectionSort(int array[], int size)
{
	int j;
	for (int i = 0; i < size - 1; i++)
	{
		int min = i; //setting min as the position of i

		for (j = i + 1; j < size; j++)
		{
			if (array[j] < array[min])
			{
				min = j;
				
			}
		}
		//calling the function to exchange A[min] with A[i]
		exchange(&array[min], &array[i]);
	}
}






/********************************************************
*				insertionsort() function				* 
*  We set the second element of array as key			*
*  and we compare key with every previous element		*
*  exchange in case the previous element is bigger		*
*********************************************************/

void insertionSort(int array[], int size)
{
	int j, i,
		key;
		
	for (j = 1; j < size; j++)
	{
		key = array[j];
		i = j - 1;
		while (i >= 0 && (array[i] > key))
		{
			array[i + 1] = array[i];
			i = i - 1;
		}
		array[i + 1] = key;
	}
}




/********************************************************
*       bubbleSortWithoutSwaps() function				*	
* bubble sort method will bubble the smallest element	*
* top of the array and will do so, until it checks	    *
* the last position	of the array						*
*********************************************************/

void bubbleSortWithoutSwaps(int array[], int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (array[j] > array[j + 1])
			{
				//call exchange function to swap A[j] with A[j+1]
				exchange(&array[j], &array[j + 1]);

			}

		}
	}
}



/********************************************************
*       bubbleSortWitSwaps() function					*
* bubble sort method will bubble the smallest element	*
* top of the array and will do so, until the number	    *
* of swaps will equal 0, meaning that array is sorted   *
*********************************************************/
void bubbleSortWithSwaps(int array[], int size)
{
	

	for (int i = 0; i < size - 1; i++)
	{
		int swaps = 0;

		for (int j = 0; j < size - i - 1; j++)
		{
			if (array[j] > array[j + 1])
			{
				exchange(&array[j], &array[j + 1]);
				swaps = swaps + 1;

			}
		}
		if (swaps == 0)
		{
			break;
		}
	}
}




/****************************************************
*                  quickSort() function				*
*Is a divide and conquer, same as mergeSort			*
*it will split the array in two parts depending on  *
*the location of pivot, and will partion the given  *
*array around pivot(p), which is the 0 position el  * 
*****************************************************/

void quickSort(int array[], int p, int r)
{
	if (p < r)     //if pivot < righmost element, pivot is in the right position
	{
		int q = partion(array, p, r); //call partion function which will put pivot in the right position
		quickSort(array, p, q - 1);	  //call quickSort for the two new subarrays
		quickSort(array, q + 1, r);

	}
}




int partion(int array[], int p, int r)
{
	int x = array[r];  //x = the righmost element of the array
	int i = p - 1;	   
	for (int j = p; j <= r - 1; j++)
	{
		if (array[j] <= x)		//if A[j] smaller than pivot, need to exchange
		{
			i = i + 1;
			//exchange A[i] with A[j]
			exchange(&array[i], &array[j]);
		}
		
	}
	//exchange A[i+1] with A[r]
	exchange(&array[i + 1], &array[r]);

	return (i + 1);
}






/* merge() function to merge the two halves of the array*/
void merge(int *array, int p, int q, int r)
{
	int i,  //index for the first array
		j,	//index for the second array
		t;
	int n = (q - p + 1); //size of first array
	int m = (r - q);	 //size of second array

	int *left = new int[n];	 //dynamically creating a left array, since size is unknown
	int *right = new int[m]; //dynamically creating a left array, since size is unknown

	for (int i = 0; i < n; i++)
	{
		*(left + i)= array[p + i]; //populating the array with the left elements
	}
	for (int j = 0; j < m; j++)
	{
		*(right + j) = array[q + 1 + j]; //populating the array with the right elements
	}

	    i = 0, j = 0, t = p;

	while ((i < n) && (j < m))
	{
		/* if left position el is less than right position,left positon 
			should go first in the new array */
		if (*(left+i) <= *(right + j))  
		{
			array[t] = *(left + i);
			i++;
		}
		/* if not, right postion goes first*/
		else
		{
			array[t] = *(right + j);   //
			j++;
		}
		t++;
	}

	/*copying the last elements of the array of left side*/
	while (i < n)
	{
		array[t] = *(left + i);
		i++;
		t++;
	}
	/*copying the last elements of the array of right side*/
	while (j < m)
	{
		array[t] = *(right + j);
		j++;
		t++;
	}

	/*delete the dynamically created arrays to avoid memory leaks */
	delete[]left; 
	delete[]right;


}





/********************************************************
*            mergeSort() function						*		
* Merge sort is a divide and conquer algorithm			*
*It will divide the array into two equals subarrays or	*
*sizes with 1 element difference. After each subarrays  *
*sorted they are all merged, combined in a full sorted	*
* array													*
*********************************************************/

void mergeSort(int *array, int p, int r)
{
	int q;
	if (p < r)
	{
		q = (p + r) / 2;     //q will be the mid element

		mergeSort(array, p, q);
		mergeSort(array, q + 1, r);
		merge(array, p, q, r);
	}

}


//function to exchange array elements
void exchange(int *first, int *second)
{
	int temp = *first;
	*first = *second;
	*second = temp;
} 


//function to print any array if needed
void printArray(int array[], int size)
{
	for (int i = 0; i < size; i++)
	{
		cout <<i << "-" << array[i] << endl;
	}
}

//function to generate a sorted array
int *arrayOfSorted(int size)
{
	int *sorted = new int[size];
	for (int i = 0; i < size; i++)
	{
		*(sorted + i) = i;
	}
	return sorted;
}


//selectionSortTime() function displays running time of the selection Sort Algorithm for each case
void selectionSortTime()
{
	srand(time(NULL));
	cout << "***************SELECTION SORT*************************" << endl;
	cout << "*      Measuring efficency of selection sort         *" << endl << endl;
	int Random1[100];
	for (int i = 0; i < 100; i++)
	{
		Random1[i] = rand() % 10000 + 1;
	}

	cout << "Random array, size = 100" << endl;

	auto startTime1 = chrono::steady_clock::now(); //start time
	selectionSort(Random1, 100);
	auto stopTime1 = chrono::steady_clock::now();  //stop time
	auto measuredTime1 = stopTime1 - startTime1;   //their difference will be the total time
	cout << "Measured time: ";
	//displaying total time in milliseconds
	cout << chrono::duration <double, milli>(measuredTime1).count() << " ms" << endl;




	int Random2[1000];
	for (int i = 0; i < 1000; i++)
	{
		Random2[i] = rand() % 10000 + 1;
	}


	cout << "Random array, size = 1000" << endl;
	auto startTime2 = chrono::steady_clock::now();
	selectionSort(Random2, 1000);
	auto stopTime2 = chrono::steady_clock::now();
	auto measuredTime2 = stopTime2 - startTime2;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime2).count() << " ms" << endl;




	int Random3[10000];
	for (int i = 0; i < 10000; i++)
	{
		Random3[i] = rand() % 10000 + 1;

	}


	cout << "Random array, size = 10000" << endl;
	auto startTime3 = chrono::steady_clock::now();
	selectionSort(Random3, 10000);
	auto stopTime3 = chrono::steady_clock::now();
	auto measuredTime3 = stopTime3 - startTime3;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime3).count() << " ms" << endl << endl;





	int SemiSorted1[100];
	for (int i = 0; i < 100; i++)
	{
		if ((i % 10) == 0)
		{
			SemiSorted1[i] = rand() % 10000 + 1;
		}
		else
		{
			SemiSorted1[i] = i;
		}
	}

	cout << "Semi-Sorted array, size = 100" << endl;

	auto startTime4 = chrono::steady_clock::now();
	selectionSort(SemiSorted1, 100);
	auto stopTime4 = chrono::steady_clock::now();
	auto measuredTime4 = stopTime4 - startTime4;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime4).count() << " ms" << endl;

	int SemiSorted2[1000];
	for (int i = 0; i < 1000; i++)
	{
		if ((i % 10) == 0)
		{
			SemiSorted2[i] = rand() % 10000 + 1;
		}
		else
		{
			SemiSorted2[i] = i;
		}
	}


	cout << "Semi-sorted array, size = 1000" << endl;
	auto startTime5 = chrono::steady_clock::now();
	selectionSort(SemiSorted2, 1000);
	auto stopTime5 = chrono::steady_clock::now();
	auto measuredTime5 = stopTime5 - startTime5;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime5).count() << " ms" << endl;



	int SemiSorted3[10000];
	for (int i = 0; i < 10000; i++)
	{
		if ((i % 10) == 0)
		{
			SemiSorted3[i] = rand() % 10000 + 1;
		}
		else
		{
			SemiSorted3[i] = i;
		}

	}


	cout << "Semi-Sorted array, size = 10000" << endl;
	auto startTime6 = chrono::steady_clock::now();
	selectionSort(SemiSorted3, 10000);
	auto stopTime6 = chrono::steady_clock::now();
	auto measuredTime6 = stopTime6 - startTime6;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime6).count() << " ms" << endl << endl;


	int *sorted1 = arrayOfSorted(100);

	cout << "Sorted array, size = 100" << endl;
	auto startTime7 = chrono::steady_clock::now();
	selectionSort(sorted1, 100);
	auto stopTime7 = chrono::steady_clock::now();
	auto measuredTime7 = stopTime7 - startTime7;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime7).count() << " ms" << endl;

	int *sorted2 = arrayOfSorted(1000);
	cout << "Sorted array, size = 1000" << endl;
	auto startTime8 = chrono::steady_clock::now();
	selectionSort(sorted2, 1000);
	auto stopTime8 = chrono::steady_clock::now();
	auto measuredTime8 = stopTime8 - startTime8;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime8).count() << " ms" << endl;

	int *sorted3 = arrayOfSorted(10000);
	cout << "Sorted array, size = 10000" << endl;
	auto startTime9 = chrono::steady_clock::now();
	selectionSort(sorted3, 10000);
	auto stopTime9 = chrono::steady_clock::now();
	auto measuredTime9 = stopTime9 - startTime9;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime9).count() << " ms" << endl;
}


//insertionSortTime() function displays running time of the insertion Sort Algorithm for each case
void insertionSortTime()
{
	srand(time(NULL));
	cout << "***************IINSERTION SORT*************************" << endl;
	cout << "*      Measuring efficency of insertion sort         *" << endl << endl;
	int Random1[100];
	for (int i = 0; i < 100; i++)
	{
		Random1[i] = rand() % 10000 + 1;
	}

	cout << "Random array, size = 100" << endl;

	auto startTime1 = chrono::steady_clock::now();
	insertionSort(Random1, 100);
	auto stopTime1 = chrono::steady_clock::now();
	auto measuredTime1 = stopTime1 - startTime1;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime1).count() << " ms" << endl;




	int Random2[1000];
	for (int i = 0; i < 1000; i++)
	{
		Random2[i] = rand() % 10000 + 1;
	}

	cout << "Random array, size = 1000" << endl;
	auto startTime2 = chrono::steady_clock::now();
	insertionSort(Random2, 1000);
	auto stopTime2 = chrono::steady_clock::now();
	auto measuredTime2 = stopTime2 - startTime2;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime2).count() << " ms" << endl;


	int Random3[10000];
	for (int i = 0; i < 10000; i++)
	{
		Random3[i] = rand() % 10000 + 1;

	}


	cout << "Random array, size = 10000" << endl;
	auto startTime3 = chrono::steady_clock::now();
	insertionSort(Random3, 10000);
	auto stopTime3 = chrono::steady_clock::now();
	auto measuredTime3 = stopTime3 - startTime3;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime3).count() << " ms" << endl << endl;





	int SemiSorted1[100];
	for (int i = 0; i < 100; i++)
	{
		if ((i % 10) == 0)
		{
			SemiSorted1[i] = rand() % 10000 + 1;
		}
		else{
			SemiSorted1[i] = i;
		}
	}

	cout << "Semi-Sorted array, size = 100" << endl;

	auto startTime4 = chrono::steady_clock::now();
	insertionSort(SemiSorted1, 100);
	auto stopTime4 = chrono::steady_clock::now();
	auto measuredTime4 = stopTime4 - startTime4;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime4).count() << " ms" << endl;

	int SemiSorted2[1000];
	for (int i = 0; i < 1000; i++)
	{
		if ((i % 10) == 0)
		{
			SemiSorted2[i] = rand() % 10000 + 1;
		}
		else{
			SemiSorted2[i] = i;
		}
	}


	cout << "Semi-sorted array, size = 1000" << endl;
	auto startTime5 = chrono::steady_clock::now();
	insertionSort(SemiSorted2, 1000);
	auto stopTime5 = chrono::steady_clock::now();
	auto measuredTime5 = stopTime5 - startTime5;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime5).count() << " ms" << endl;



	int SemiSorted3[10000];
	for (int i = 0; i < 10000; i++)
	{
		if ((i % 10) == 0) {
			SemiSorted3[i] = rand() % 10000 + 1;
		}
		else {
			SemiSorted3[i] = i;
		}

	}


	cout << "Semi-Sorted array, size = 10000" << endl;
	auto startTime6 = chrono::steady_clock::now();
	insertionSort(SemiSorted3, 10000);
	auto stopTime6 = chrono::steady_clock::now();
	auto measuredTime6 = stopTime6 - startTime6;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime6).count() << " ms" << endl << endl;


	int *sorted1 = arrayOfSorted(100);

	cout << "Sorted array, size = 100" << endl;
	auto startTime7 = chrono::steady_clock::now();
	insertionSort(sorted1, 100);
	auto stopTime7 = chrono::steady_clock::now();
	auto measuredTime7 = stopTime7 - startTime7;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime7).count() << " ms" << endl;

	int *sorted2 = arrayOfSorted(1000);
	cout << "Sorted array, size = 1000" << endl;
	auto startTime8 = chrono::steady_clock::now();
	insertionSort(sorted2, 1000);
	auto stopTime8 = chrono::steady_clock::now();
	auto measuredTime8 = stopTime8 - startTime8;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime8).count() << " ms" << endl;

	int *sorted3 = arrayOfSorted(10000);
	cout << "Sorted array, size = 10000" << endl;
	auto startTime9 = chrono::steady_clock::now();
	insertionSort(sorted3, 10000);
	auto stopTime9 = chrono::steady_clock::now();
	auto measuredTime9 = stopTime9 - startTime9;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime9).count() << " ms" << endl;
}

//bubbleSortWithoutSwapsTime() function displays running time of the bubble Sort Algorithm(without counting swaps) for each case
void bubbleSortWithoutSwapsTime()
{
	srand(time(NULL));
	cout << "************BUBBLE SORT WITHOUT SWAPS*****************" << endl;
	cout << "*   Measuring efficency of bubble sort without swap  *" << endl << endl;
	int Random1[100];
	for (int i = 0; i < 100; i++)
	{
		Random1[i] = rand() % 10000 + 1;
	}

	cout << "Random array, size = 100" << endl;

	auto startTime1 = chrono::steady_clock::now();
	bubbleSortWithoutSwaps(Random1, 100);
	auto stopTime1 = chrono::steady_clock::now();
	auto measuredTime1 = stopTime1 - startTime1;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime1).count() << " ms" << endl;




	int Random2[1000];
	for (int i = 0; i < 1000; i++)
	{
		Random2[i] = rand() % 10000 + 1;
	}

	cout << "Random array, size = 1000" << endl;
	auto startTime2 = chrono::steady_clock::now();
	bubbleSortWithoutSwaps(Random2, 1000);
	auto stopTime2 = chrono::steady_clock::now();
	auto measuredTime2 = stopTime2 - startTime2;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime2).count() << " ms" << endl;


	int Random3[10000];
	for (int i = 0; i < 10000; i++)
	{
		Random3[i] = rand() % 10000 + 1;

	}


	cout << "Random array, size = 10000" << endl;
	auto startTime3 = chrono::steady_clock::now();
	bubbleSortWithoutSwaps(Random3, 10000);
	auto stopTime3 = chrono::steady_clock::now();
	auto measuredTime3 = stopTime3 - startTime3;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime3).count() << " ms" << endl << endl;


	int SemiSorted1[100];
	for (int i = 0; i < 100; i++)
	{
		if ((i % 10) == 0)
		{
			SemiSorted1[i] = rand() % 10000 + 1;
		}
		else {
			SemiSorted1[i] = i;
		}
	}

	cout << "Semi-Sorted array, size = 100" << endl;

	auto startTime4 = chrono::steady_clock::now();
	bubbleSortWithoutSwaps(SemiSorted1, 100);
	auto stopTime4 = chrono::steady_clock::now();
	auto measuredTime4 = stopTime4 - startTime4;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime4).count() << " ms" << endl;

	int SemiSorted2[1000];
	for (int i = 0; i < 1000; i++)
	{
		if ((i % 10) == 0)
		{
			SemiSorted2[i] = rand() % 10000 + 1;
		}
		else {
			SemiSorted2[i] = i;
		}
	}


	cout << "Semi-sorted array, size = 1000" << endl;
	auto startTime5 = chrono::steady_clock::now();
	bubbleSortWithoutSwaps(SemiSorted2, 1000);
	auto stopTime5 = chrono::steady_clock::now();
	auto measuredTime5 = stopTime5 - startTime5;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime5).count() << " ms" << endl;


	int SemiSorted3[10000];
	for (int i = 0; i < 10000; i++)
	{
		if ((i % 10) == 0) {
			SemiSorted3[i] = rand() % 10000 + 1;
		}
		else {
			SemiSorted3[i] = i;
		}

	}
	cout << "Semi-Sorted array, size = 10000" << endl;
	auto startTime6 = chrono::steady_clock::now();
	bubbleSortWithoutSwaps(SemiSorted3, 10000);
	auto stopTime6 = chrono::steady_clock::now();
	auto measuredTime6 = stopTime6 - startTime6;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime6).count() << " ms" << endl << endl;


	int *sorted1 = arrayOfSorted(100);

	cout << "Sorted array, size = 100" << endl;
	auto startTime7 = chrono::steady_clock::now();
	bubbleSortWithoutSwaps(sorted1, 100);
	auto stopTime7 = chrono::steady_clock::now();
	auto measuredTime7 = stopTime7 - startTime7;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime7).count() << " ms" << endl;

	int *sorted2 = arrayOfSorted(1000);
	cout << "Sorted array, size = 1000" << endl;
	auto startTime8 = chrono::steady_clock::now();
	bubbleSortWithoutSwaps(sorted2, 1000);
	auto stopTime8 = chrono::steady_clock::now();
	auto measuredTime8 = stopTime8 - startTime8;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime8).count() << " ms" << endl;

	int *sorted3 = arrayOfSorted(10000);
	cout << "Sorted array, size = 10000" << endl;
	auto startTime9 = chrono::steady_clock::now();
	bubbleSortWithoutSwaps(sorted3, 10000);
	auto stopTime9 = chrono::steady_clock::now();
	auto measuredTime9 = stopTime9 - startTime9;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime9).count() << " ms" << endl;
}

//bubbleSortWithSwapsTime() function displays running time of the bubble Sort Algorithm(counting swaps) for each case
void bubbleSortWithSwapsTime()
{
	srand(time(NULL));
	cout << "************BUBBLE SORT WITH SWAPS********************" << endl;
	cout << "*    Measuring efficency of bubble sort with swap    *" << endl << endl;
	int Random1[100];
	for (int i = 0; i < 100; i++)
	{
		Random1[i] = rand() % 10000 + 1;
	}

	cout << "Random array, size = 100" << endl;

	auto startTime1 = chrono::steady_clock::now();
	bubbleSortWithSwaps(Random1, 100);
	auto stopTime1 = chrono::steady_clock::now();
	auto measuredTime1 = stopTime1 - startTime1;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime1).count() << " ms" << endl;




	int Random2[1000];
	for (int i = 0; i < 1000; i++)
	{
		Random2[i] = rand() % 10000 + 1;
	}

	cout << "Random array, size = 1000" << endl;
	auto startTime2 = chrono::steady_clock::now();
	bubbleSortWithSwaps(Random2, 1000);
	auto stopTime2 = chrono::steady_clock::now();
	auto measuredTime2 = stopTime2 - startTime2;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime2).count() << " ms" << endl;


	int Random3[10000];
	for (int i = 0; i < 10000; i++)
	{
		Random3[i] = rand() % 10000 + 1;

	}


	cout << "Random array, size = 10000" << endl;
	auto startTime3 = chrono::steady_clock::now();
	bubbleSortWithSwaps(Random3, 10000);
	auto stopTime3 = chrono::steady_clock::now();
	auto measuredTime3 = stopTime3 - startTime3;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime3).count() << " ms" << endl << endl;


	int SemiSorted1[100];
	for (int i = 0; i < 100; i++)
	{
		if ((i % 10) == 0)
		{
			SemiSorted1[i] = rand() % 10000 + 1;
		}
		else {
			SemiSorted1[i] = i;
		}
	}

	cout << "Semi-Sorted array, size = 100" << endl;

	auto startTime4 = chrono::steady_clock::now();
	bubbleSortWithSwaps(SemiSorted1, 100);
	auto stopTime4 = chrono::steady_clock::now();
	auto measuredTime4 = stopTime4 - startTime4;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime4).count() << " ms" << endl;

	int SemiSorted2[1000];
	for (int i = 0; i < 1000; i++)
	{
		if ((i % 10) == 0)
		{
			SemiSorted2[i] = rand() % 10000 + 1;
		}
		else {
			SemiSorted2[i] = i;
		}
	}


	cout << "Semi-sorted array, size = 1000" << endl;
	auto startTime5 = chrono::steady_clock::now();
	bubbleSortWithSwaps(SemiSorted2, 1000);
	auto stopTime5 = chrono::steady_clock::now();
	auto measuredTime5 = stopTime5 - startTime5;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime5).count() << " ms" << endl;


	int SemiSorted3[10000];
	for (int i = 0; i < 10000; i++)
	{
		if ((i % 10) == 0) {
			SemiSorted3[i] = rand() % 10000 + 1;
		}
		else {
			SemiSorted3[i] = i;
		}

	}
	cout << "Semi-Sorted array, size = 10000" << endl;
	auto startTime6 = chrono::steady_clock::now();
	bubbleSortWithSwaps(SemiSorted3, 10000);
	auto stopTime6 = chrono::steady_clock::now();
	auto measuredTime6 = stopTime6 - startTime6;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime6).count() << " ms" << endl << endl;


	int *sorted1 = arrayOfSorted(100);

	cout << "Sorted array, size = 100" << endl;
	auto startTime7 = chrono::steady_clock::now();
	bubbleSortWithSwaps(sorted1, 100);
	auto stopTime7 = chrono::steady_clock::now();
	auto measuredTime7 = stopTime7 - startTime7;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime7).count() << " ms" << endl;

	int *sorted2 = arrayOfSorted(1000);
	cout << "Sorted array, size = 1000" << endl;
	auto startTime8 = chrono::steady_clock::now();
	bubbleSortWithSwaps(sorted2, 1000);
	auto stopTime8 = chrono::steady_clock::now();
	auto measuredTime8 = stopTime8 - startTime8;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime8).count() << " ms" << endl;

	int *sorted3 = arrayOfSorted(10000);
	cout << "Sorted array, size = 10000" << endl;
	auto startTime9 = chrono::steady_clock::now();
	bubbleSortWithSwaps(sorted3, 10000);
	auto stopTime9 = chrono::steady_clock::now();
	auto measuredTime9 = stopTime9 - startTime9;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime9).count() << " ms" << endl;
}

//quickSortTime() function displays running time of the quick Sort Algorithm for each case
void quickSortTime()
{
	srand(time(NULL));
	cout << "******************   QUICK SORT   ********************" << endl;
	cout << "*         Measuring efficency of Quick Sort           *" << endl << endl;
	int Random1[100];
	for (int i = 0; i < 100; i++)
	{
		Random1[i] = rand() % 10000 + 1;
	}

	cout << "Random array, size = 100" << endl;

	auto startTime1 = chrono::steady_clock::now();
	quickSort(Random1, 0, 99);
	auto stopTime1 = chrono::steady_clock::now();
	auto measuredTime1 = stopTime1 - startTime1;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime1).count() << " ms" << endl;



	
	int Random2[1000];
	for (int i = 0; i < 1000; i++)
	{
		Random2[i] = rand() % 10000 + 1;
	}

	cout << "Random array, size = 1000" << endl;
	auto startTime2 = chrono::steady_clock::now();
	quickSort(Random2, 0, 999);
	auto stopTime2 = chrono::steady_clock::now();
	auto measuredTime2 = stopTime2 - startTime2;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime2).count() << " ms" << endl;

	
	int Random3[10000];
	for (int i = 0; i < 10000; i++)
	{
		Random3[i] = rand() % 10000 + 1;

	}


	cout << "Random array, size = 10000" << endl;
	auto startTime3 = chrono::steady_clock::now();
	quickSort(Random3, 0, 9999);
	auto stopTime3 = chrono::steady_clock::now();
	auto measuredTime3 = stopTime3 - startTime3;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime3).count() << " ms" << endl << endl;

	
	int SemiSorted1[100];
	for (int i = 0; i < 100; i++)
	{
		if ((i % 10) == 0)
		{
			SemiSorted1[i] = rand() % 10000 + 1;
		}
		else {
			SemiSorted1[i] = i;
		}
	}

	cout << "Semi-Sorted array, size = 100" << endl;

	auto startTime4 = chrono::steady_clock::now();
	quickSort(SemiSorted1, 0, 99);
	auto stopTime4 = chrono::steady_clock::now();
	auto measuredTime4 = stopTime4 - startTime4;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime4).count() << " ms" << endl;
	
	int SemiSorted2[1000];
	for (int i = 0; i < 1000; i++)
	{
		if ((i % 10) == 0)
		{
			SemiSorted2[i] = rand() % 10000 + 1;
		}
		else {
			SemiSorted2[i] = i;
		}
	}

	
	cout << "Semi-sorted array, size = 1000" << endl;
	auto startTime5 = chrono::steady_clock::now();
	quickSort(SemiSorted2, 0, 999);
	auto stopTime5 = chrono::steady_clock::now();
	auto measuredTime5 = stopTime5 - startTime5;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime5).count() << " ms" << endl;


	int SemiSorted3[10000];
	for (int i = 0; i < 10000; i++)
	{
		if ((i % 10) == 0) {
			SemiSorted3[i] = rand() % 10000 + 1;
		}
		else {
			SemiSorted3[i] = i;
		}

	}
	cout << "Semi-Sorted array, size = 10000" << endl;
	auto startTime6 = chrono::steady_clock::now();
	quickSort(SemiSorted3, 0, 9999);
	auto stopTime6 = chrono::steady_clock::now();
	auto measuredTime6 = stopTime6 - startTime6;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime6).count() << " ms" << endl << endl;

	
	int *sorted1 = arrayOfSorted(100);

	cout << "Sorted array, size = 100" << endl;
	auto startTime7 = chrono::steady_clock::now();
	quickSort(sorted1, 0, 99);
	auto stopTime7 = chrono::steady_clock::now();
	auto measuredTime7 = stopTime7 - startTime7;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime7).count() << " ms" << endl;
	
	int *sorted2 = arrayOfSorted(1000);
	cout << "Sorted array, size = 1000" << endl;
	auto startTime8 = chrono::steady_clock::now();
	quickSort(sorted2, 0, 999);
	auto stopTime8 = chrono::steady_clock::now();
	auto measuredTime8 = stopTime8 - startTime8;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime8).count() << " ms" << endl;
	
	int *sorted3 = arrayOfSorted(10000);
	cout << "Sorted array, size = 10000" << endl;
	auto startTime9 = chrono::steady_clock::now();
	mergeSort(sorted3, 0, 9999);
	auto stopTime9 = chrono::steady_clock::now();
	auto measuredTime9 = stopTime9 - startTime9;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime9).count() << " ms" << endl;
	
}

//mergeSortTime() function displays running time of the merge Sort Algorithm for each case
void mergeSortTime()
{
	srand(time(NULL));
	cout << "******************  MERGE SORT   ********************" << endl;
	cout << "*         Measuring efficency of Merge Sort           *" << endl << endl;
	int Random1[100];
	for (int i = 0; i < 100; i++)
	{
		Random1[i] = rand() % 10000 + 1;
	}

	cout << "Random array, size = 100" << endl;

	auto startTime1 = chrono::steady_clock::now();
	mergeSort(Random1, 0, 99);
	auto stopTime1 = chrono::steady_clock::now();
	auto measuredTime1 = stopTime1 - startTime1;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime1).count() << " ms" << endl;




	int Random2[1000];
	for (int i = 0; i < 1000; i++)
	{
		Random2[i] = rand() % 10000 + 1;
	}

	cout << "Random array, size = 1000" << endl;
	auto startTime2 = chrono::steady_clock::now();
	mergeSort(Random2, 0, 999);
	auto stopTime2 = chrono::steady_clock::now();
	auto measuredTime2 = stopTime2 - startTime2;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime2).count() << " ms" << endl;


	int Random3[10000];
	for (int i = 0; i < 10000; i++)
	{
		Random3[i] = rand() % 10000 + 1;

	}


	cout << "Random array, size = 10000" << endl;
	auto startTime3 = chrono::steady_clock::now();
	mergeSort(Random3, 0, 9999);
	auto stopTime3 = chrono::steady_clock::now();
	auto measuredTime3 = stopTime3 - startTime3;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime3).count() << " ms" << endl << endl;


	int SemiSorted1[100];
	for (int i = 0; i < 100; i++)
	{
		if ((i % 10) == 0)
		{
			SemiSorted1[i] = rand() % 10000 + 1;
		}
		else {
			SemiSorted1[i] = i;
		}
	}

	cout << "Semi-Sorted array, size = 100" << endl;

	auto startTime4 = chrono::steady_clock::now();
	mergeSort(SemiSorted1, 0, 99);
	auto stopTime4 = chrono::steady_clock::now();
	auto measuredTime4 = stopTime4 - startTime4;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime4).count() << " ms" << endl;

	int SemiSorted2[1000];
	for (int i = 0; i < 1000; i++)
	{
		if ((i % 10) == 0)
		{
			SemiSorted2[i] = rand() % 10000 + 1;
		}
		else {
			SemiSorted2[i] = i;
		}
	}


	cout << "Semi-sorted array, size = 1000" << endl;
	auto startTime5 = chrono::steady_clock::now();
	mergeSort(SemiSorted2, 0, 999);
	auto stopTime5 = chrono::steady_clock::now();
	auto measuredTime5 = stopTime5 - startTime5;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime5).count() << " ms" << endl;


	int SemiSorted3[10000];
	for (int i = 0; i < 10000; i++)
	{
		if ((i % 10) == 0) {
			SemiSorted3[i] = rand() % 10000 + 1;
		}
		else {
			SemiSorted3[i] = i;
		}

	}
	cout << "Semi-Sorted array, size = 10000" << endl;
	auto startTime6 = chrono::steady_clock::now();
	mergeSort(SemiSorted3, 0, 9999);
	auto stopTime6 = chrono::steady_clock::now();
	auto measuredTime6 = stopTime6 - startTime6;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime6).count() << " ms" << endl << endl;


	int *sorted1 = arrayOfSorted(100);

	cout << "Sorted array, size = 100" << endl;
	auto startTime7 = chrono::steady_clock::now();
	mergeSort(sorted1, 0, 99);
	auto stopTime7 = chrono::steady_clock::now();
	auto measuredTime7 = stopTime7 - startTime7;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime7).count() << " ms" << endl;

	int *sorted2 = arrayOfSorted(1000);
	cout << "Sorted array, size = 1000" << endl;
	auto startTime8 = chrono::steady_clock::now();
	mergeSort(sorted2, 0, 999);
	auto stopTime8 = chrono::steady_clock::now();
	auto measuredTime8 = stopTime8 - startTime8;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime8).count() << " ms" << endl;

	int *sorted3 = arrayOfSorted(10000);
	cout << "Sorted array, size = 10000" << endl;
	auto startTime9 = chrono::steady_clock::now();
	mergeSort(sorted3, 0, 9999);
	auto stopTime9 = chrono::steady_clock::now();
	auto measuredTime9 = stopTime9 - startTime9;
	cout << "Measured time: ";
	cout << chrono::duration <double, milli>(measuredTime9).count() << " ms" << endl;
}
