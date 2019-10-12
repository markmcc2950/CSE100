// Worked with Alex Munoz for code

#include <iostream>
#include <sstream>
#include <list>
#include <iterator>

#define EMPTY NULL;
using namespace std;

class Entry {
	list<int> hashChain;														// Private hash list
public:
	Entry(int hashKey) {														// Handles the hashkey entries
		hashChain.push_front(hashKey);
	}

	void push(int hashKey) {													// Create the hashkey
		hashChain.push_front(hashKey);
	}
	/*
		"Search (key) in the table. If there is an element with the key value, then you have to output"
	*/
	int search(int hashKey) {
		list<int> :: iterator i;												// Checks through the list
		int j = 0;																// Counts the 'links' of our chain
		for (i = hashChain.begin(); i != hashChain.end(); i++) {				// Cycle through the chain until we reach the end		
			if (*i == hashKey) {
				return j;														// "Find" the hashkey if it matches (through our interator pointer)
			}
			j++;																// Proceed to next link in the chain
		}
		return -1;																// We've reached the end of the chain
	}

	bool deleteHash(int hashKey) {												// Deletes hashkeys
		int position = search(hashKey);											// Call the search function, set that to our position
		if (position == -1) {													// If we're at the end of the chain, return false.
			return false;
		}
		else {																	// If not at the end of the chain, continue through
			list<int> ::iterator i = hashChain.begin();							// New iterator at the beginning of our hash chain
			while (position > 0) {												// Increase iterator and decrease position until we reach position 0
				i++;
				position--;
			}
			hashChain.erase(i);													// Erase the value of the hashchain at iterator value of position 0, return true
			return true;
		}
	}
	/*
		"Output the entire hash table"
	*/
	void output() {
		list<int> :: iterator i;												// Iterator to cycle through the list
		for (i = hashChain.begin(); i != hashChain.end(); i++) {
			cout << *i << "->";													// Output the list
		}
	}

};

class HashTable {
	Entry **hTable;																// Double pointer to our entry class for the hash table
	int sizeCopy = 0;
	int i;
public:
	HashTable(int size) {
		hTable = new Entry*[size];												// Create a new entry table of size (int size)
		sizeCopy = size;														// Create a copy of the size value
		for (i = 0; i < size; i++) {
			hTable[i] = EMPTY;													// Set all values of hash table to NULL
		}
	}
	
	~HashTable() {																// Used to delete our hash table
		for (i = 0; i < sizeCopy; i++) {
			if (hTable[i]) {
				delete hTable[i];
			}
			delete hTable;														// Remove from memory
		}
	}

	string hashSearch(int hashKey) {
		int hash = hashKey % sizeCopy;											// Hash = (hash key) modulus (copy of hash size)
		/* 
			If we're at the position of the hash table of location 'hash', and
			if the hash key of this position is not -1 (end of chain), then
			"FOUND_AT(#),(#)"
		*/
		if (hTable[hash]) {
			if (hTable[hash]->search(hashKey) != -1) {
				return to_string(hash) + "," + to_string(hTable[hash]->search(hashKey));
			}
		}
		return "";

	}
	/*
		"Insert (key) into the table."
	*/
	void insert(int hashKey) {
		int hash = hashKey % sizeCopy;											// Hash = (hash key) modulus (copy of hash size)
		/*
			If we're at position of 'hash' on the hash table, then push our key
			Else, create a new hash key from Entry class
		*/
		if (hTable[hash]) {
			hTable[hash]->push(hashKey);
		}
		else {
			hTable[hash] = new Entry(hashKey);
		}
	}

	bool deleteHash(int hashKey) {												// To delete a hash with a hash key
		string position = hashSearch(hashKey);									// Search for and save hash key as a string
		/*
			If the hash key is anything but blank, set new string stream & string,
			Get the string stream and string just created, create hash index, and check
			if index of hash table is deleted through deleteHash function, then return true (successful deletion)
		*/
		if (position != "") {
			istringstream iss(position);
			string detect;
			getline(iss, detect, ',');
			int hashIndex = stoi(detect);
			if (hTable[hashIndex]->deleteHash(hashKey)) {
				return true;
			}
		}
		return false;															// Else return false (unsuccessful deletion)
	}
	/*
		Prints out the hash table
	*/
	void print() {
		/*
			For all values of hash table, print out the output of all values separated by a semicolon
			(Per lab instructions)
		*/
		for (int i = 0; i < sizeCopy; i++) {
			cout << i << ":";
			if (hTable[i]) {
				hTable[i]->output();
			}
			cout << ";" << endl;
		}
	}
};

int main() {
	int size;																	// Holds user input size of list
	cin >> size;
	HashTable *hTable = new HashTable(size);									// Pointer to hash table for new variable to hold our user-inputted hash table size
	string input;																// Takes user input in string (as specified by lab)
	cin >> input;

	/*   __________________________________
		|| i: Insert (key) into the table ||
		|| s: Search (key) in the table   ||
		|| d: Delete (key) from the table ||
		|| o: Output the table            ||
		|| e: Finish the program          ||
		||________________________________||
	*/
	while (input[0] != 'e') {													// While program is still running
		// "Insert (key) into the table"
		if (input[0] == 'i') {
			hTable->insert(stoi(input.substr(1)));
		}
		// "Search (key) in the table"
		if (input[0] == 's') {
			int key = stoi(input.substr(1));									// int key calls input function
			string pos = hTable->hashSearch(key);
			if (pos != "") {
				cout << key << ":FOUND_AT" << pos << ";" << endl;				// Successful search
			}
			else {
				cout << key << ":NOT_FOUND;" << endl;							// Unsucessful search
			}
		}
		// "Delete (key) from the table"
		if (input[0] == 'd') {
			int key = stoi(input.substr(1));
			if (hTable->deleteHash(key)) {
				cout << key << ":DELETED;" << endl;								// Successful deletion
			}
			else {
				cout << key << ":DELETE_FAILED;" << endl;						// Unsucessful deletion
			}
		}
		// "Output the table"
		if (input[0] == 'o') {
			hTable->print();
		}
		cin >> input;															// Take in input for next cycle (i, s, d, o, e)
	}
}