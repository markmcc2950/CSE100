/*
	Code written by Mark McCullough
	Collaborated with Alex Munoz
	Using help from:
	Introduction to Algorithms, 3rd Edition
	and the pseudocode given for:
	Matrix Chain Multiplication
	[Pages 371-377]
*/

#include <iostream>
#include <climits>
#define MAX_INT 2147483647;														// For when m[i, j] = infinity
using namespace std;

void PRINT_OPTIMAL_PARENS(int* s, int i, int j, int p) {
	if (i == j) {
		cout << "A" << i - 1;
		return;
	}
	else {
		// Parenthesize the matrix
		cout << "(";
		PRINT_OPTIMAL_PARENS(s, i, *((s + (i * p)) + j), p);
		PRINT_OPTIMAL_PARENS(s, *((s + i * p) + j) + 1, j, p);
		cout << ")";
	}
}

void MATRIX_CHAIN_ORDER(int A[], int p) {
	int m[p][p];																// Square matrix 'm' of size p x p
	int s[p][p];																// Square matrix 's' of size p x p
	int i, l, k;																// Iterator variables
	int j, q;																	// For holding some values later for comparison
	for (i = 1; i < p; i++) {
		m[i][i] = 0;															// Diagonal of matrix all have values of 0
	}
	for (l = 2; l < p; l++) {
		for (i = 1; i < (p - l) + 1; i++) {
			j = i + l - 1;
			m[i][j] = MAX_INT;													// m[i, j] = infinity
			for (k = i; k < j; k++) {
				q = m[i][k] + m[k + 1][j] + A[i - 1] * A[k] * A[j];
				if (q < m[i][j]) {
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}
	cout << m[1][p - 1] << endl;
	PRINT_OPTIMAL_PARENS((int*)s, 1, p - 1, p);									// Order (parenthesize) the matrix
	cout << "\n";
}

int main() {
	int size, i;
	cin >> size;																// User inputted size for matrix dimensions
	int list[size + 1];															// Array list of size inputted by user, plus 1
	for (i = 0; i <= size; i++) {
		cin >> list[i];															// Take in user inputted values for the list
	}
	MATRIX_CHAIN_ORDER(list, size + 1);											// Run values through matrix chain order function
}

/*
	PSEUDOCODE FROM TEXTBOOK:

	MATRIX-MULTIPLY (A, B)														(Not using)
	if A.columns != B.rows
		error "incompatible dimensions"
	else let C be a new A.rows x B.columns matrix
		for i = 1 to A.rows
			for j = 1 to B.columns
				c(i, j) = 0
				for k = 1 to A.columns
					c(i, j) = c(i, j) + a(i, k) * b(k, j)
		return C
		
	MATRIX-CHAIN-ORDER(p)														(Using)
	n = p.length - 1
	let m[1...n, 1...n] and s[1...n-1, 2...n] be new tables
	for i = 1 to n
		m[i, i] = 0
	for l = 2 to n					// l is the chain length
		for i = 1 to (n - l) + 1
			j = i + l - 1
			m[i, j] = infinity
			for k = i to j - 1
				q = m[i, k] + m[k + 1, j] + p(i-1)p(k)p(j)
				if q < m[i, j]
					m[i, j] = q
					s[i, j] = k
	return m and s

	PRINT-OPTIMAL-PARENS(s, i, j)												(Using)
	if i == j
		print "A"
	else print "("
		PRINT-OPTIMAL-PARENS(s, i, s[i, j])
		PRINT-OPTIMAL-PARENS(s, s[i, j] + 1, j)
		print ")"
*/