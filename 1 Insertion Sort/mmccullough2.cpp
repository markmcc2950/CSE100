#include <iostream>

using namespace std;

int main() {
    int size;                                                                           // Size of the array
    // cout << "What is the size of the list?" << endl;                                    // User input for the list
    cin >> size;                                                                        // Save user input for size

    // Create the list values
    int i;
    int list[size];                                                                     // Create the list
    int j;                                                                              // Used to safely decrease list values without affecting int i
    int k;                                                                              // Used strictly for a for loop to print sorted values
    int swap;                                                                           // To swap list values safely without overwriting useful data   

    // Get user input for all list values from 1 through n
    for(i=0; i<size; i++) {
        // cout << "Enter a value for list value [" << i+1 << "]" << endl;
        cin >> list[i];        
    }                                                              

    // Loop to scan the list and compare values
    for(i=1; i<size; i++) {
        j = i;                                                                          // Store portion of list we're on
        while(list[j] < list[j-1] && j > -1) {                                          // Sorting loop from i through 0
            swap = list[j-1];                                                           // Stores larger value
            list[j-1] = list[j];                                                        // Move lower value down the list
            list[j] = swap;                                                             // Move higher value up the list
            j--;                                                                        // Decrease j to move down list and check if everything's sorted
        }
    

        for(k=0; k<i+1; k++) {
            cout << list[k] << ";";
        }
        cout << endl;
    }
}