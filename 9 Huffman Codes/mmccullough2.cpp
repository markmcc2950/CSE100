/*
	COLLABORATED LOGIC WITH ALEX MUNOZ
	REFERENCED MATERIAL AT BOTTOM OF CODE
	PSEUDOCODE FROM BOOK AT BOTTOM OF CODE
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

char nodeNames[] = {'A', 'B', 'C', 'D', 'E', 'F'};								// Names of all used nodes
string nodeList[] = { "", "", "", "", "", "" };									// List to house strings to return in main function


/*
	We create this struct to create each node for the tree
*/
struct nodes {
	char node;																	// Name of the node
	int f;																		// Frequency of the node

	// Initialize left and right nodes to 0 values initially to keep them minimal. Helps keep comparisons simplified
	nodes* l = 0;
	nodes* r = 0;
public:
	nodes() {																	// Default constructor (as a backup just in case)
		node = ' ';
		f = 0;
	}
	nodes(char name, int f) {
		this->node = name;														// Takes the name for nodes (a, b, c, d, e, f)
		this->f = f;															// Takes the frequencies associated with each node
	}
};

struct nodeCheck {																// Used for comparisons of left & right node frequencies
	bool operator()(nodes* l, nodes* r) {
		return(l->f > r->f);													// Return true if left frequency > right frequency
	}
};

void binary(struct nodes* n, string s) {
	if (n == NULL) {															// Base case
		return;
	}
	if (n->node == nodeNames[0]) {
		nodeList[0] += "A:" + s;												// Print node A and binary value of tree position
	}
	else if (n->node == nodeNames[1]) {
		nodeList[1] += "B:" + s;												// Print node B and binary value of tree position
	}
	else if (n->node == nodeNames[2]) {
		nodeList[2] += "C:" + s;												// Print node C and binary value of tree position
	}
	else if (n->node == nodeNames[3]) {
		nodeList[3] += "D:" + s;												// Print node D and binary value of tree position
	}
	else if (n->node == nodeNames[4]) {
		nodeList[4] += "E:" + s;												// Print node E and binary value of tree position
	}
	else if (n->node == nodeNames[5]) {
		nodeList[5] += "F:" + s;												// Print node F and binary value of tree position
	}
	binary(n->l, s + "0");														// Print "0" if left node
	binary(n->r, s + "1");														// Print "1" if right node
}

void HUFFMAN(char name[], int f[]) {
	priority_queue<nodes*, vector<nodes*>, nodeCheck> depth;
	int i;
	/*
		REFERENCED: 
		https://en.cppreference.com/w/cpp/container/priority_queue 
			- For understanding on the priority_queue function
		http://www.cplusplus.com/reference/stack/stack/pop/
			- For understanding on how to properly go through the tree nodes
	*/	
	nodes *l, *r, *junction;													// Left node, right node, junction is where they meet. Equals sum of the L & R frequencies
	for (i = 0; i < 6; i++) {
		depth.push(new nodes(name[i], f[i]));
	}
	while (depth.size() > 1) {													// Loop creates the tree while size > 1
		l = depth.top();
		depth.pop();															// Destroys left depth value (reference above)
		r = depth.top();
		depth.pop();															// Destroys right depth value (reference above)
		junction = new nodes('z', l->f + r->f);									// New temporary node 'z' for the junction node, sums frequency values of L & R nodes
		junction->l = l;
		junction->r = r;
		depth.push(junction);
	}
	binary(depth.top(), "");													// Call binary function to create binary values for nodes
}

int main() {
	int x = sizeof(nodeNames);
	int f[x], i;																// Frequency list of size of amount of nodes (dynamic allocation of size based on # of global nodes)

	for (i = 0; i < x; i++) {
		cin >> f[i];															// Take user inputs of frequency values for nodes
	}
	HUFFMAN(nodeNames, f);														// Call HUFFMAN function

	for (i = 0; i < x; i++) {													// Return binary values of all nodes
		cout << nodeList[i] << endl;
	}
}

/*
PSEUDOCODE FROM TEXTBOOK
Huffman Code (P. 431)

HUFFMAN(C)
	n = |C|																		// n is 
	Q = C																		// Min-priority queue with the characters in C
	for i = 1 to n - 1
		allocate a new node z
		z.left = x = EXTRACT-MIN(Q)												// EXTRACT-MIN IS PART OF HEAP SORT ALGORITHM
		z.right = y = EXTRACT-MIN(Q)
		z.freq = x.freq + y.freq
		INSERT(Q, z)
	return EXTRACT-MIN(Q)														// Return the root of the tree

MY NOTES FOR LOGIC FLOW:
	Check lowest two numbers
		- Lesser value is left node, larger is right node
		- Sum of these two is value of next node
			- Check value of this sum to next lowest value
				- If sum < next value, sum is left node, value is right node
				- If sum > next value, value is left node, sum is right node
			- Continue this process until we've gone through all 6 values (A, B, C, D, E, F)
			- Left nodes are assigned a '0'
			- Right nodes are assigned a '1'

STATED UNDER HUFFMAN FUNCTION, REPEATING REFERENCES AS PRECAUTION:
	REFERENCED:
	https://en.cppreference.com/w/cpp/container/priority_queue
	- For understanding on the priority_queue function
	http://www.cplusplus.com/reference/stack/stack/pop/
	- For understanding on how to properly go through the tree nodes
*/