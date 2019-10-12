/*
	Worked with Alex Munoz for creating code
*/

#include <iostream>
using namespace std;

#define MINIMUM -2147483647;													// Initial "max" value to use, set to minimum 32 bit value

void cutRod(int p[], int n) {
	int val[n + 1];																// Value of rod cut
	int cuts[n + 1];															// Cuts of the rod
	int max;																	// Used for comparisons
	int i, j;																	// Used for 'for' loops
	val[0] = 0;																	// Initialize first index value to 0

	for (i = 1; i <= n; i++) {
		max = MINIMUM;															// Set "max" value to lowest value for comparison
		for (j = 0; j < i; j++) {
			/*
				If 'max' is less than index value of p summed with index of 'val', then max is now the value of that summation. 
				The amount of cuts to maximize revenue for that index 'i' is 'j' + 1
				Else, keep checking each 'i' and 'j' value
			*/
			if (max < p[j] + val[i - j - 1]) {
				max = p[j] + val[i - j - 1];
				cuts[i] = j + 1;
			}
		}
		val[i] = max;															// Set the index 'i' value of 'val' to our new max found in the for loops
	}
	cout << val[n] << endl;														// Print out the 'n'th index value of 'val' 
	while (n > 0) {																// While n is positive, print out the 'n'th index value of cuts, and reduce n by the value held in index value 'n'
		cout << cuts[n] << " ";
		n = n - cuts[n];
	}
}

int main() {
	int size;																	// Size of the list
	cin >> size;																// User input of list
	int list[size];																// Create new list of size 'size'
	for (int i = 0; i < size; i++) {											// Take user input of all values of the list
		cin >> list[i];
	}
	cutRod(list, size);															// Call the cutRod function
	cout << -1 << endl;															// Print out -1 at the end of all printed values
}

/*
	CUT-ROD(p, n)
	if n == 0
		return 0
	q = -(infinty)
	for i = 1 to n
		q = max(q, p[i] + CUT-ROD(p, n - i))
	return q
*/