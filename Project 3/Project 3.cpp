/* FILE NAME: Project 3.cpp
* AUTHOR: Brantley Robertson
* SOURCES: I looked at methods from https://www.geeksforgeeks.org/bubble-sort/ for
* inspiration, https://www.cplusplus.com/doc/tutorial/files/ to learn more about fstream and stream functions,
* and https://www.cplusplus.com/doc/tutorial/arrays/ to learn more about arrays in C++.
* TO COMPILE THIS FILE ENTER THIS COMMAND: g++ Project 3.cpp
*/


#include <fstream>
#include <iostream>
using namespace std;

const int MAX_SIZE = 100;       // Max array size

/* This method checks to make sure a file is valid or invalid. */
bool checkFile(string file);

/* This method reads in a file's contents. */
int readFile(int inputArray[], ifstream& stream);

/* This is a helper function that works in combine to sort everything */
void swap(int* x, int* y);

/* This method combines both arrays of numbers from the
* input files, sorts them, and combines them into one array.
*/
int combine(int array1[], int array1Size, int array2[], int array2Size, int outputArray[]);

/* This method writes the output array to its own file. */
void writeFile(int outputArray[], int outputArraySize);


int main() {
    
    /* declare your variables */
    int array1[MAX_SIZE];
    int array1Size;
    int array2[MAX_SIZE];
    int array2Size;
    int outputArray[MAX_SIZE];
    int outputArraySize;

    cout << endl << "*** Welcome to Brantley's sorting program ***\n";

    /* Get name of file one. */
    ifstream stream;

    string file1;
    do {
        cout << "Enter the first input file name: ";
        cin >> file1;
        stream.open((char*)file1.c_str());
    } while (cin.fail() || !checkFile(file1));

    array1Size = readFile(array1, stream);
    stream.close();

    cout << "The list of " << array1Size << " numbers in file " << file1 << " is:\n";

    for (int i = 0; i < array1Size; i++) {
        cout << array1[i] << "\n";
    }

    cout << endl;

    /* Get name of file two. */
    string file2;
    do {
        cout << "Enter the second input file name: ";
        cin >> file2;
        stream.open((char*)file2.c_str());
    } while (cin.fail() || !checkFile(file1));

    array2Size = readFile(array2, stream);
    stream.close();

    cout << "The list of " << array2Size << " numbers in file " << file2 << " is:\n";

    for (int i = 0; i < array2Size; i++) {
        cout << array2[i] << "\n";
    }

    cout << endl;

    /* Combine and sort the array to be output */
    outputArraySize = combine(array1, array1Size, array2, array2Size, outputArray);

    cout << "The sorted list of " << outputArraySize << " numbers is:";

    for (int i = 0; i < outputArraySize; i++) {
        cout << " " << outputArray[i];
    }

    cout << endl;
    
    /* Write the output array to its own file */
    writeFile(outputArray, outputArraySize);

    cout << "*** Goodbye. ***" << endl;
    return 0;
}


bool checkFile(string file) {
    /* Input file stream. (ifstream) */
    ifstream stream;

    /* Check whether file exists. */
    stream.open(file.c_str());
    if (stream.fail()) {
        return false;
    }
    stream.close();
    return true;

}


int readFile(int inputArray[], ifstream& stream) {
    int index = 0;

    stream >> inputArray[index];
    while (!stream.eof()) {
        index++;
        stream >> inputArray[index];
    }
    return index;
}


void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}


int combine(int array1[], int array1Size, int array2[], int array2Size, int outputArray[]) {
    int outputArraySize = array1Size + array2Size;

    for (int i = 0; i < array1Size; i++) {
        outputArray[i] = array1[i];
    }
    for (int i = 0; i < array2Size; i++) {
        outputArray[i + array1Size] = array2[i];
    }

    /* sort */
    for (int i = 0; i < outputArraySize - 1; i++) {
        for (int j = 0; j < outputArraySize - i - 1; j++) {
            if (outputArray[j] >= outputArray[j + 1]) {
                swap(outputArray[j], outputArray[j + 1]);
            }
        }
    }

    return outputArraySize;
}


void writeFile(int outputArray[], int outputArraySize) {
    ofstream outstream;
    string outputFile;
    cout << "Enter the output file name: ";
    cin >> outputFile;

    outstream.open((char*)outputFile.c_str());
    for (int i = 0; i < outputArraySize; i++) {
        outstream << outputArray[i] << "\n";
    }
    outstream.close();

    cout << "*** Please check the new file - " << outputFile << " ***\n";
}
