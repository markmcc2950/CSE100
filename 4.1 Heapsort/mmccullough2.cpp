#include <stdio.h>
#include <iostream>
using namespace std;

/*
	"The key to maintaining the max-heap property"
*/
void MaxHeapify(int A[], int i, int j) {
	int swap;																	// Used for swapping positions in the list
	int largest = j;															// Largest value
	int l = (2 * j) + 1;														// Left side
	int r = (2 * j) + 2;														// Right side
	// If index stored on the left is largest, terminate procedure as we already have max-heap
	if (l < i && A[l] > A[j]) {
		largest = l;
	}
	// If index stored on the right is largest, terminate procedure as we already have max-heap
	if (r < i && A[r] > A[largest]) {
		largest = r;
	}
	// Otherwise, swap value with largest, recursively call MaxHeapify and run again until left or right is largest
	if (largest != j) {
		swap = A[j];															// Swap values
		A[j] = A[largest];
		A[largest] = swap;
		MaxHeapify(A, i, largest);												// Recursively call MaxHeapify until l or r is largest
	}
}

/*
	"Produces a max-heap from an unordered input array"
*/
void BuildMaxHeap(int A[], int i) {
	for (int j = (i / 2) - 1; j >= 0; j--) {
		MaxHeapify(A, i, j);
	}
}

/*
	"Sorts an array in place"
*/
void HeapSort(int A[], int i) {
	BuildMaxHeap(A, i);															// Produce a max heap first
	int swap;
	// Sort the array and call MaxHeapify at the end of each iteration
	for (int j = i - 1; j >= 0; j--) {
		swap = A[j];
		A[j] = A[0];
		A[0] = swap;
		MaxHeapify(A, j, 0);
	}
}


int main() {
	int size;																	// Size of the list
	cin >> size;

	int list[size];																// Create list of size n
	int i;
	for (i = 0; i < size; i++) {												// Take user input for list items 1 through n
		cin >> list[i];
	}
	HeapSort(list, size);														// Call HeapSort to sort the list

	for (i = 0; i < size; i++) {												// Return the list in format required by lab
		cout << list[i] << ";";
	}
}


/*
	MAX-HEAPIFY(A, i)
	l = LEFT(i)
	r = RIGHT(i)
	if (l <= A.heap-size and A[l] > A[i])
		largest = l
	else largest = i
	if (r <= A.heap-size and A[r] > A[largest])
		largest = r
	if largest != i
		exchange A[i] with A[largest]
		MAX-HEAPIFY(A.largest)

	BUILD-MAX-HEAP(A)
	A.heap-size = A.length
	for i = [A.length/2] downto 1
		MAX-HEAPIFY(A,i)

	HEAPSORT(A)
	BUILD-MAX-HEAP(A)
	for i = A.length downto 2
		exchange A[1] with A[i]
		A.heap-size = A.heap-size - 1
		MAX-HEAPIFY(A,1)
*/