#include <iostream>
#include <stdio.h>
#include <time.h>
using namespace std;

int Partition(int A[], int p, int r) {
	int swap;																	// Variable to swap values
	int j;
	int rnd = p + (rand() % (r - p));											// Random pivot point
	int x = A[rnd];																// Pick position in list of pivot point selected

	// Swap the values of random pivot point with the last value of the array
	swap = A[r];
	A[r] = A[rnd];
	A[rnd] = swap;


	int i = p - 1;
	// Cycle through entire array from beginning to the pivot point
	for (j = p; j < r; j++) {
		if (A[j] <= x) {														// If index is less than pivot point value, swap values or A[i] and A[j], and proceed through the list
			i++;
			swap = A[i];
			A[i] = A[j];
			A[j] = swap;
		}		
	}
	swap = A[i + 1];
	A[i + 1] = A[r];
	A[r] = swap;

	return i + 1;																// Return new value
}

void QuickSort(int A[], int p, int r) {
	int q;
	if (p < r) {
		q = Partition(A, p, r);
		QuickSort(A, p, q - 1);													// Sort from beginning to partitioned point of list
		QuickSort(A, q + 1, r);													// Sort from partitioned point of list to end
	}
}

int main() {
	srand(time(0));																// Lets us use the random number generator

	int size;																	// Size of the list
	cin >> size;																// Take user input for the list size

	int list[size];																// Create list of size 'size'
	int i;
	for (i = 0; i < size; i++) {												// Loop for user input
		cin >> list[i];
	}
	QuickSort(list, 0, size - 1);												// Call QuickSort function
	for (i = 0; i < size; i++) {												// Return sorted list in format required by lab
		cout << list[i] << ";";
	}
	return 0;																	// Terminate the program
}

/*
	QUICKSORT(A, p, r)
	if p < r
		q = PARTITION(A, p, r)
		QUICKSORT(A, p, q - 1)
		QUICKSORT(A, q + 1, r)

	PARTITION(A, p, r)
	x = A[r]
	i = p - 1
	for j = p to r - 1
		if A[j] <= x
			i = i + 1
			exchange A[i] with A[j]
	exchange A[i + 1] with A[r]
	return i + 1
*/
