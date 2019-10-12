#include <iostream>

using namespace std;

int main() {
    int size;
    cout << "What's the size of your list?" << endl;
    cin >> size;

    int i;
    int list[size];

    for(i = 0; i < size; i++) {
        cout << "What's the value for list number [" << i+1 << "]" << endl;
        cin >> list[i];
    }

    int min = list[0];
    int max = list[0];

    for(i = 0; i < size; i++) {
        if(list[i] < min) {
            min = list[i];
        }
        if(max < list[i]) {
            max = list[i];
        }
    }

    // cout << "Minimum value:\t" << min << "\nMaximum Value:\t" << max << endl;
    cout << max << ";" << min << endl;

}