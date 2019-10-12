/*
	CODE WRITTEN BY MARK MCCULLOUGH
	PSEUDOCODE WRITTEN WITHIN CLASSES BEFORE EACH FUNCTION
	PSEUDOCODE COPIED FROM ALGORITHMS TEXTBOOK
*/

#include <iostream>
#include <string>

using namespace std;

struct nodes {
	nodes* l = NULL;
	nodes* r = NULL;
	nodes* p = NULL;
	int key;

public:
	nodes(int z) {
		p;																		// Parent node
		l;																		// Left child
		r;																		// Right child
		key = z;																// Node key
	}
};

class BINARY_SEARCH_TREE {
public:
	nodes* nodeRoot = NULL;

	/*
		TREE-INSERT(T, z) (P.294)
		y = NIL
		x = T.root
		while x != NIL
			y = x
			if z.key < x.key
				x = x.left
			else x = x.right
		z.p = y
		if y == NIL
			T.root = z							// Tree T was empty
		elseif z.key < y.key
			y.left = z
		else y.right = z
	*/

	void TREE_INSERT(nodes* T, int z) {
		nodes* y = this->nodeRoot;
		if (!y) {
			this->nodeRoot = new nodes(z);
		}
		else {
			// If z >= key of node T, and not of the right child, right child gets value of key 'z'. Else, call TREE_INSERT function again with right child and key 'z'
			if (z >= T->key) {
				if (!T->r) {
					T->r = new nodes(z);
					T->r->p = T;
				}
				else {
					TREE_INSERT(T->r, z);
				}
			}
			// If not of left child, left child gets value of key 'z'. Else, call TREE_INSERT function again with left child and key 'z'
			else {
				if (!T->l) {
					T->l = new nodes(z);
					T->l->p = T;
				}
				else {
					TREE_INSERT(T->l, z);
				}
			}
		}
	}

	// "A PREORDER_TREE_WALK prints the root before the values in either subtree"
	void PREORDER_TREE_WALK(nodes* x) {
		if (x == NULL) {
			return;																// Base case, if root is empty, then return
		}
		cout << x->key << endl;										// Print out key value of root
		PREORDER_TREE_WALK(x->l);									// Walk left child of root
		PREORDER_TREE_WALK(x->r);									// Walk right child of root
	}

	/*
		INORDER-TREE-WALK(x) (P.288)
		if x != NIL
		INORDER-TREE-WALK(x.left)
		print x.key
		INORDER-TREE-WALK(x.right)
	*/
	void INORDER_TREE_WALK(nodes* x) {
		if (x == NULL) {
			return;
		}
		INORDER_TREE_WALK(x->l);										// Call INORDER for left child
		cout << x->key << endl;										// Print out key of child
		INORDER_TREE_WALK(x->r);										// Call INORDER for right child
	}

	// "A POSTORDER_TREE_WALK prints the root after the values in its subtrees"
	void POSTORDER_TREE_WALK(nodes* x) {
		if (x == NULL) {											// Base case, if root is null, then return 
			return;
		}
		POSTORDER_TREE_WALK(x->l);									// Call POSTORDER function for left child
		POSTORDER_TREE_WALK(x->r);									// Call POSTORDER function for right child
		cout << x->key << endl;										// Print key of root
	}

	/*
		TREE-SEARCH(x,k) (P.290)
		if x == NIL or k == x.key
			return x
		if k < x.key
			return TREE-SEARCH(x.left, k)
		else return TREE-SEARCH(x.right, k)
	*/
	nodes* TREE_SEARCH(nodes* x, int k) {
		if (x == NULL || k == x->key) {						// "if x == NIL or k == x.key, return x"
			return x;
		}
		if (k < x->key) {											// "if k < x.key, return TREE-SEARCH(x.left, k)"
			return TREE_SEARCH(x->l, k);
		}
		else {																	// "else return TREE-SEARCH(x.right, k)"
			return TREE_SEARCH(x->r, k);
		}
	}

	/*
		TREE-MINIMUM(x) (P.291)
		while x.left != NIL
			x = x.left
		return x
	*/
	nodes* TREE_MINIMUM(nodes* minRoot) {
		while (minRoot->l != NULL) {
			minRoot = minRoot->l;
		}
		return minRoot;
	}

	/*
		TRANSPLANT(T, u, v) (P.296)
		if u.p == NIL
			T.root = v
		elseif u == u.p.left
			u.p.left = v
		else u.p.right = v
		if v != NIL
			v.p = u.p
	*/
	nodes* TRANSPLANT(nodes* u, nodes* v) {
		if (u->p == NULL) {
			nodeRoot = v;
		}
		else if (u == u->p->l) {
			u->p->l = v;
		}
		else {
			u->p->r = v;
		}
		if (v != NULL) {
			v->p = u->p;
		}
	}

	/*
		TREE-DELETE(T, z) (P.298)
		if z.left == NIL
			TRANSPLANT(t, z, z.right)
		elseif z.right == NIL
			TRANSPLANT(T, z, z.left)
		else y = TREE.MINIMUM(z.right)
		if y.p != z
			TRANSPLANT(t, y, y.right)
			y.right = z.right
			y.right.p = y
		TRANSPLANT(T, z, y)
		y.left = z.left
		y.left.p = y
	*/
	void TREE_DELETE(int k) {
		nodes* z = TREE_SEARCH(this->nodeRoot, k);
		if (z) {
			if (z->l == NULL) {
				TRANSPLANT(z, z->r);
			}
			else if (z->r == NULL) {
				TRANSPLANT(z, z->l);
			}
			else {
				nodes* y = TREE_MINIMUM(z->r);
				if (y->p != z) {
					TRANSPLANT(y, y->r);
					y->r = z->r;
					y->r->p = y;
				}
				TRANSPLANT(z, y);
				y->l = z->l;
				y->l->p = y;
			}
		}
	}
};

int main() {
	BINARY_SEARCH_TREE* binSearchTree = new BINARY_SEARCH_TREE();
	string input;
	cin >> input;
	int key;
	// e: finish your program
	if (input[0] == 'e') {
		return 0;
	}
	while (input[0] != 'e') {
		// i(key): Insert (key) into the BST. For example, i2 implies “Insert key 2 into the BST.”
		if (input[0] == 'i') {
			key = stoi(input.substr(1));										// Remainder of string after 'i' is the key
			// Call insert function with the root value and the input value from index 1. input[0] is i, so input[1] on is needed key
			binSearchTree->TREE_INSERT(binSearchTree->nodeRoot, key);
		}
		// d(key): delete (key) from the BST. For example, d2 implies “delete key 2 from the BST.” Do nothing if the BST doesn’t have the key.
		else if (input[0] == 'd') {
			key = stoi(input.substr(1));										// Remainder of string after 'd' is the key
			// Call delete function
			binSearchTree->TREE_DELETE(key);
		}
		// opre: output all keys via preorder walk.
		else if (input == "opre") {
			binSearchTree->PREORDER_TREE_WALK(binSearchTree->nodeRoot);
		}
		// opost: output all keys via postorder walk.
		else if (input == "opost") {
			binSearchTree->POSTORDER_TREE_WALK(binSearchTree->nodeRoot);
		}
		// oin: output all keys via inorder walk.
		else if (input == "oin") {
			binSearchTree->INORDER_TREE_WALK(binSearchTree->nodeRoot);
		}
		cin >> input;															// While program is running (input[0] != e), keep taking inputs
	}
}

/*
	PSEUDOCODE FROM BOOK FOR BINARY SEARCH TREE ALGORITHMS:
	(P.286 - 307)

			(Page 287 from Algorithms book)
		-	...Inorder tree walk. This algorithm is so named because it prints the key of the root of a subtree between printing the values 
			in its left subtree and printing those in its right subtree. (Similarly, a PREORDER TREE WALK prints the root before the values 
			in either subtree, and a POSTORDER TREE WALK prints the root after the values in its subtrees.) 
----------------------------------------------------------------------------------------------------------------------------------------------------------
	INORDER-TREE-WALK(x) (P.288)
		if x != NIL
			INORDER-TREE-WALK(x.left)
			print x.key
			INORDER-TREE-WALK(x.right)
----------------------------------------------------------------------------------------------------------------------------------------------------------
	TREE-SEARCH(x,k) (P.290)
		if x == NIL or k == x.key
			return x
		if k < x.key
			return TREE-SEARCH(x.left, k)
		else return TREE-SEARCH(x.right, k)
----------------------------------------------------------------------------------------------------------------------------------------------------------
	ITERATIVE-TREE-SEARCH(x, k) (P.291)
		while x != NIL and k != x.key
			if k < x.key
				x = x.left
			else x = x.right
		return x
----------------------------------------------------------------------------------------------------------------------------------------------------------
	TREE-MINIMUM(x) (P.291)
		while x.left != NIL
			x = x.left
		return x
----------------------------------------------------------------------------------------------------------------------------------------------------------
	TREE-MAXIMUM(x) (P.291)
		while x.right != NIL
			x = x.right
		return x
----------------------------------------------------------------------------------------------------------------------------------------------------------
	TREE-SUCCESSOR(x) (P.292)
		if x.right != NIL
			return TREE-MINIMUM(x.right)
		y = x.p
		while y != NIL and x == y.right
			x = y
			y = y.p
		return y
----------------------------------------------------------------------------------------------------------------------------------------------------------
	TREE-INSERT(T, z) (P.294)
		y = NIL
		x = T.root
		while x != NIL
			y = x
			if z.key < x.key
				x = x.left
			else x = x.right
		z.p = y
		if y == NIL
			T.root = z							// Tree T was empty
		elseif z.key < y.key
			y.left = z
		else y.right = z
----------------------------------------------------------------------------------------------------------------------------------------------------------
	TRANSPLANT(T, u, v) (P.296)
		if u.p == NIL
			T.root = v
		elseif u == u.p.left
			u.p.left = v
		else u.p.right = v
		if v != NIL
			v.p = u.p
----------------------------------------------------------------------------------------------------------------------------------------------------------
	TREE-DELETE(T, z) (P.298)
		if z.left == NIL
			TRANSPLANT(t, z, z.right)
		elseif z.right == NIL
			TRANSPLANT(T, z, z.left)
		else y = TREE.MINIMUM(z.right)
		if y.p != z
			TRANSPLANT(t, y, y.right)
			y.right = z.right
			y.right.p = y
		TRANSPLANT(T, z, y)
		y.left = z.left
		y.left.p = y
----------------------------------------------------------------------------------------------------------------------------------------------------------
*/