#include <stdio.h>
#include <iostream>
using namespace std;
#define MIN_INT -2147483647

// A is the array, x is min, y is mid, z is max
int crossArray(int cross[], int x, int y, int z) {
	// Set lSum to largest negative value to make comparing easier for first needed comparison, initialize sum = 0 for left side sum
	int lSum = MIN_INT;
	int sum = 0;
	// Create max sum for the left side
	int i;
	for (i = y; i >= x; i--) {
		sum = sum + cross[i];
		if (sum > lSum) {
			lSum = sum;
		}
	}

	// Set rSum to largest negative value to make comparing easier for first needed comparison, reinitialize sum = 0 for right side sum
	int rSum = MIN_INT;
	sum = 0;
	// Create max sum for the right side
	int j;
	for (j = y + 1; j <= z; j++) {
		sum = sum + cross[j];
		if (sum > rSum) {
			rSum = sum;
		}
	}
	return (lSum + rSum);
}

int maxArray(int max[], int x, int z) {
	// Base case (1 element in the array)
	if (z == x) {
		return (max[z]);
	}

	// Any array greater than 1 element
	else {
		int y = (x + z) / 2;
		/*
			Create the three array sums for comparison
			lSum is left-side sum of the array
			rSum is right-side sum of the array
			xSum is sum of the complete array
		*/
		int lSum = maxArray(max, x, y);
		int rSum = maxArray(max, y + 1, z);
		int xSum = crossArray(max, x, y, z);

		// Compare the three sums to see which is largest
		if (lSum >= rSum && lSum >= xSum) {												// If left sum is greatest, return left sum
			return (lSum);
		}
		else if (rSum >= lSum && rSum >= xSum) {										// If right sum is greatest, return right sum
			return (rSum);
		}
		else {																			// Return full sum if neither left sum or right sum are greatest (this means xSum is greatest)
			return xSum;
		}
	}
}

int main() {
	int size;																			// Size of the array
	int val;																			// Takes in the max subarray
	// cout << "What is the size of our list?" << endl;
	cin >> size;																		// Take in the size of the array
	int list[size];																		// Initialize array 'list' of user inputted size

	// Take user input for each element in the array
	int i;
	for (i = 0; i < size; i++) {
		cin >> list[i];
	}
	// Find max subarray and return the value
	val = maxArray(list, 0, size-1);
	cout << val;

	return 0;																			// End the program
}

/*
	****************************************************
				PSEUDO-CODE FROM BOOK
	****************************************************

	FIND-MAXIMUM-SUBARRAY(A, low, high)
		if high == low
			return (low, high, A[low])
		else mid = [(low + high) / 2]
			(left-low, left-high, left-sum) =
				FIND-MAXIMUM-SUBARRAY(A, low, mid)
			(right-low, right-high, right-sum) =
				FIND-MAX-CROSSING-SUBARRAY(A, low, mid, high)
			if left-sum >= right-sum AND left-sum >= cross-sum
				return (right-low, right-high, right-sum)
			else return (cross-low, cross-high, cross-sum)


		FIND-MAX-CROSSING-SUBARRAY(A, low, mid, high)
		left-sum = -infinity
		sum = 0
		for i = mid DOWN TO low
			sum = sum + A[i]
			if sum > left-sum
				left-sum = sum
				max-left = i
		right-sum = -infinity
		sum = 0
		for j = mid + 1 TO high
			sum = sum + A[j]
			if sum > right-sum
				right-sum = sum
				max-right = j
		return (max-left, max-right, left-sum + right-sum)
*/