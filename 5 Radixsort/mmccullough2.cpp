#include <iostream>
#include <vector>
#define VEC_SIZE 10

using namespace std;

/*
	The book algorithm describes RadixSort as using a stable sort,
	I will be using CountingSort for this stable sort
*/
vector<vector<int>> countingSort(vector<vector<int>> myVector, int d, int k) {
	int A[VEC_SIZE] = {};
	int i;
	vector<vector<int>> vector1 = myVector;										// Output vector (Take on traits of myVector of the function)
	
	for (i = 0; i <= k; i++) {													// Check the number of times each unique number appears in our vector
		A[myVector[i][d]] = A[myVector[i][d]] + 1;
	}
	for (i = 1; i < VEC_SIZE; i++) {											// Calculate the starting index values for our vector (vector1)
		A[i] = A[i] + A[i - 1];
	}
	for (i = k; i >= 0; i--) {													// Transfer the values from myVector to the function vector (vector1) from the index values counted
		int A_Index = myVector[i][d];
		int V_Index = (A[A_Index]) - 1;
		vector<int> tempVector;
		tempVector = myVector[i];
		vector1[V_Index] = tempVector;
		A[A_Index] = V_Index;
	}

	myVector = vector1;															// Store the values of our new vector in myVector
	return myVector;															// Return the newly constructed myVector
}

void radixSort(vector<vector<int>> myVector, int d) {
	int i, j;																	// For counting through index values
	for (i = VEC_SIZE - 1; i >= 0; i--) {
		myVector = countingSort(myVector, i, d);
	}
	for (i = 0; i <= d; i++) {
		for (j = 0; j < VEC_SIZE; j++) {
			cout << myVector.at(i).at(j) << ";";
		}
		cout << endl;
	}
}

int main() {
	int size;																	// Size of our vector list
	int i, j, k;																// For counting
	cin >> size;																// Take user input of our size
	vector<vector<int>> myVector;												// Used to store values inputted

	/*
		Take all the user inputted values and put them in the vector, sort them, and return our values
	*/
	for (i = 0; i < size; i++) {
		vector<int> newVector;
		for (j = 0; j < VEC_SIZE; j++) {
			cin >> k;
			newVector.push_back(k);
		}
		myVector.push_back(newVector);
	}
	radixSort(myVector, (size - 1));
}

/*
	PSEUDOCODE FROM TEXTBOOK:

		RADIX-SORT(A, d)
		for i = 1 to d
			use a stable sort to sort array A on digit i

		**For stable sort, using CountingSort**
		COUNTING-SORT(A, B, k)
			let C[0...k] be a new array
			for i = 0 to k
				C[i] = 0
			for j = 1 to A.length
				C[A[j]] = C[A[j]] + 1
			// C[i] now contains the number of elements equal to i
			for i = 1 to k
				C[i] = C[i] + C[i - 1]
			// C[i] now contains the number of elements less than or equal to i
			for j = A.length downto 1
				B[C[A[J]]] = A[J]
				C[A[J]] = C[A[J]] - 1
*/