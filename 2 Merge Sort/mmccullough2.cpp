// LAB 2
// MARK MCCULLOUGH
// Referenced our textbook for algorithms on Merge & Merge-Sort
// Collaborated with Alex Munoz for debugging of Merge-Sort

#include <iostream>
using namespace std;
#define MAX_INT 2147483647

/*
	* mergeList[] takes in the full array to be sorted
	* min takes in the lowest index value of mergeList[]
	* half takes in the midpoint of mergeList[]
	* max takes in the final index of mergeList[]
*/
void merge(int mergeList[], int min, int half, int max) {
	/*
		Set up the array to broken down for a 'divide and conquer' approach.
	*/
	int left = half - min + 1;															// Size of left half of the array
	int right = max - half;																// Size of the right half of the array
	int L[left+1];																		// Takes in the left half of the array
	int R[right+1];																		// Takes in the right half of the array

	int i;																				// Used for 'for loop' for left half of array
	int j;																				// Used for 'for loop' for right half of array

	// Input the left half of the mergeList array into the divided left-hand array
	for (i = 0; i < left; i++) {
		L[i] = mergeList[min + i];
	}

	// Input the right half of the mergeList array into the divided right-hand array
	for (j = 0; j < right; j++) {
		R[j] = mergeList[half + j + 1];
	}
	
	L[left] = MAX_INT;																	// Sets value of highest index in left array to infinity
	R[right] = MAX_INT;																	// Sets value of highest index in right array to infinity

	/*
		Reinitialize 'i' and 'j' values to zero. 
		We use these values to count through the left and right sides of the list and their index values
		If the index value of the left is smaller than that in the right, we write that smaller value to our merged array
		Increment the value ('i' or 'j'), and check again. Keep rescanning on merging values until the end of the merged array
	*/
	i = 0;
	j = 0;

	for (int k = min; k <= max; k++) {
		if (L[i] <= R[j]) {
			mergeList[k] = L[i];
			i++;
		}
		else {
			mergeList[k] = R[j];
			j++;
		}
	}
}


/*
	mergeSort checks is the 'min' value is less than the 'max' value
	If so, create a 'half' value for the halfway point of the list
	We call the mergeSort function two times:
			- Once for the left half of the list,
			- Once for the right half of the list
			- This once again splits the lists in half again and again, until each index is sorted
	Next, we call the merge function and merge our lists
*/
void mergeSort(int mergeList[], int min, int max) {
	if (min < max) {
		int half = (min + max) / 2;
		mergeSort(mergeList, min, half);
		mergeSort(mergeList, half + 1, max);
		merge(mergeList, min, half, max);
	}
}

int main() {
	int size;																			// Size of the array

	// cout << "What is the size of the list?" << endl;
	cin >> size;																		// Store the user input of array size

	int list[size];																		// Set list array to be of size 'size'

	// Get user input via 'for loop' for entire list array
	int i;
	for (i = 0; i < size; i++) {
		// cout << "Enter a value for list value [" << i + 1 << "]" << endl;
		cin >> list[i];
	}

	// Call mergeSort function for our list
	mergeSort(list, 0, size-1);

	// Use 'for loop' to return values of sorted list in format required (1;2;3;...;n;)
	for (i = 0; i < size; i++) {
		cout << list[i] << ";";
	}
	//cout << endl;
}


/*
 MERGE ALGORITHM:
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 MERGE(A,p,q,r)
 n1 = q - p + 1
 n2 = r - q
 let L[1 ... n1 + 1] and R[1 ... n2 + 1] be new arrays
 for i = 1 to n1
      L[i] = A[p + i - 1]
 for j = 1 to n2
      R[j] = A[q + j]
 L[n1 + 1] = infty
 R[n2 + 1] = infty
 i = 1
 j = 1
 for k = p to r
      if L[i] <= R[j]
          A[k] = L[i]
          i = i + 1
      else A[k] = R[j]
          j = j + 1
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

 MERGE-SORT(A, p, r)
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 if P < r
		q = [(p+r)/2]
		MERGE-SORT(A,p,q)
		MERGE-SORT(A,q+1,r)
		MERGE(A,p,q,r)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

