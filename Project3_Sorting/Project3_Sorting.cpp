#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

// Predicate function to check if a vector is sorted
bool is_sorted(const vector<int>& listOfInts) {
    for (unsigned long i = 1; i < listOfInts.size(); ++i) {
        if (listOfInts[i] < listOfInts[i - 1]) {
            return false;
        }
    }
    return true;
}


// Selection Sort
void selection_sort(vector<int>& listOfInts, int& numComps, int& numSwaps) {
    numComps = 0; // number of comparisons
    numSwaps = 0; // number of swaps
    int temp = 0; // temporary placement for numbers being swapped
    int size = listOfInts.size(); // retrieve the size of the list of integers
    
    for (int i = 0; i < size - 1; i++) {

        int indexSmallest = i; // leftmost point is considered the indexSmallest
        for (int j = i + 1; j < size; j++) {
            numComps++; //increment comparison counter
            if (listOfInts[j] < listOfInts[indexSmallest]) { // if smaller number than leftmost in considered list is found, mark it as the smallest
                indexSmallest = j;
            }
        }
        
        if(indexSmallest == i) {  //if current lefmost is already smallest, skip swap
            continue;  
        }

        // Swap leftmost integer with the smallest integer in list
        temp = listOfInts[i]; // places leftmost into temporary spot
        listOfInts[i] = listOfInts[indexSmallest]; //places smallest value into leftmost position of considered list
        listOfInts[indexSmallest] = temp; //places previous leftmost into empty slot
        numSwaps++; //increment swap counter
    }   

}

// Insertion Sort
void insertion_sort(vector<int>& listOfInts, int& numComps, int& numSwaps) {
    numComps = 0; // number of comparisons
    numSwaps = 0; // number of swaps
    int temp = 0; // temporary placement for numbers being swapped
    int size = listOfInts.size(); // retrieve the size of the list of integers

    for (int i = 1; i < size; i++) {
        int j = i; //place j comparisons where i is

        while (j > 0 && (numComps++, listOfInts[j] < listOfInts[j - 1])) {  //checks if the value to the left of j is greater than j. If so, it swaps the values
            
            temp = listOfInts[j];
            listOfInts[j] = listOfInts[j - 1];
            listOfInts[j - 1] = temp;
            j--; //have j go backwards to compare with leftside of the list
            numSwaps++; //increment swaps counter
        }
    }
}

//Merge function for mergesort
void merge(vector<int>& listOfInts, int start, int middle, int end, int& numComps, int& numSwaps) {
    int mergedSize = end - start + 1; // This is the size the array will be after merging them
    int mergePos = 0; // Position to insert merged number
    vector<int> mergedNumbers(mergedSize); //New array for merging numbers
    int leftPos = start; // Initializes left partition position
    int rightPos = middle + 1; // Initializes right partition position

    // Add smallest element from left or right partition to mergedNumbers
    while (leftPos <= middle && rightPos <= end) {
        if (numComps++, listOfInts[leftPos] <= listOfInts[rightPos]) { // If left posistion is smaller
            mergedNumbers[mergePos] = listOfInts[leftPos]; // add it to the temporary array
            leftPos ++; // Iterate left position
        }
        else {
            mergedNumbers[mergePos] = listOfInts[rightPos]; // else, take right partition number and andd it to temporary array
            rightPos ++;
        }
        mergePos ++; // iterate merge position on temporary array

    }

    while (leftPos <= middle) { // If left partition is not empty
        mergedNumbers[mergePos] = listOfInts[leftPos]; // add left partition numbers to array
        leftPos ++; 
        mergePos ++; 
    
    }

    while (rightPos <= end) { // If right partition is not empty
        mergedNumbers[mergePos] = listOfInts[rightPos]; // add right partition numbers to array
        rightPos ++;
        mergePos ++;
    
    }

    for (mergePos = 0; mergePos < mergedSize; mergePos++) { // Copy merged numbers back into original array
        listOfInts[start + mergePos] = mergedNumbers[mergePos];
        numSwaps ++;
    }
}

//Mergesort
void mergesort_imp(vector<int>& listOfInts, int start, int end, int& numComps, int& numSwaps) {

    if (start < end) {
        int middle = (start + end) / 2; // split array

        mergesort_imp(listOfInts, start, middle, numComps, numSwaps);
        mergesort_imp(listOfInts, middle+1, end, numComps, numSwaps);

        // Merge left and right partitions in sorted order
        merge(listOfInts, start, middle, end, numComps, numSwaps);
    }
}

void mergesort(vector<int>& listOfInts, int& numComps, int& numSwaps) { //wrapper for test cases

    if (listOfInts.empty()) {
        return;
    }
    mergesort_imp(listOfInts, 0, (int)listOfInts.size() - 1, numComps, numSwaps);

}

//Partitioning function for Quicksort
int partition(vector<int>& listOfInts, int lowIndex, int highIndex, int& numComps, int& numSwaps) {
    int midpoint = lowIndex + (highIndex - lowIndex) / 2;  //find midpoint of the partition
    int pivot = listOfInts[midpoint]; //Retrieve integer at midpoint
    int temp = 0; //temporary value for swapping numbers

    bool done = false; 
    while (!done) {

        while (numComps++, listOfInts[lowIndex] < pivot) {
            lowIndex ++; //increment lowIndex if it is less than the pivot value
        }

        while (numComps++, pivot < listOfInts[highIndex]) {
            highIndex --; //decrement highIndex if it is greater than the pivot
        }

        if (lowIndex >= highIndex) {
            done = true; //if lowIndex passes the highIndex in position, then end the loop
        }
        else {
            //but if not, swap integer values of lowIndex and highIndex
            temp = listOfInts[lowIndex];
            listOfInts[lowIndex] = listOfInts[highIndex];
            listOfInts[highIndex] = temp;

            lowIndex ++; //increment lowIndex
            highIndex --; //decrement highIndex
            numSwaps ++; //increment number of swaps
        }
    }
    return highIndex; //return the highIndex
}

//Quicksort
void quicksort_imp(vector<int>& listOfInts, int lowIndex, int highIndex, int& numComps, int& numSwaps) {

    if (highIndex <= lowIndex) {  //if the partition size is 1 or zero elements then the partition will be immediately returned
        return;
    }

    int lowEndIndex = partition(listOfInts, lowIndex, highIndex, numComps, numSwaps); //last element of the left partition after sorting around pivot

    quicksort_imp(listOfInts, lowIndex, lowEndIndex, numComps, numSwaps); //partition and sort left partition recursively
    quicksort_imp(listOfInts, lowEndIndex+1, highIndex, numComps, numSwaps); //partition and sort right partition recursively
}

void quicksort(vector<int>& listOfInts, int&numComps, int&numSwaps) { //wrapper for quicksort function to pass assignment testcases

    quicksort_imp(listOfInts, 0, (int)listOfInts.size() - 1, numComps, numSwaps); //call implimentation of quicksort
}

// Utility function to print a vector -- for your convenience
void print_vector(const vector<int>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i];
        if (i < v.size() - 1) cout << ", ";
    }
    cout << endl;
}

vector<int> generate_random_vector(int size, int minVal, int maxVal) {
    vector<int> vec(size);
    for (int i = 0; i < size; ++i) {
        vec[i] = rand() % (maxVal - minVal + 1) + minVal;
    }
    return vec;
}


int main() {
    // Generage a random number array
    srand((unsigned int)time(0));
    vector<int> sample = generate_random_vector(20, 0, 99);

    // Sort array using selection sort and print results
    cout << "Original list: ";
    print_vector(sample);

    // Selection sort example manual validation code...
    vector<int> selectVec(sample);
    int selectComps = 0, selectSwaps = 0;
    selection_sort(selectVec, selectComps, selectSwaps);
    cout << "After selection sort: ";
    print_vector(selectVec);
    cout << "Comparisons: " << selectComps << ", Swaps: " << selectSwaps << endl;
    cout << "Is sorted? " << (is_sorted(selectVec) ? "Yes" : "No") << endl << endl;

    // Sort array using insertion sort and print results
    vector<int> insertionVec(sample);
    int insertionComps = 0, insertionSwaps = 0;
    insertion_sort(insertionVec, insertionComps, insertionSwaps);
    cout << "After insertion sort: ";
    print_vector(insertionVec);
    cout << "Comparisons: " << insertionComps << ", Swaps: " << insertionSwaps << endl;
    cout << "Is sorted? " << (is_sorted(insertionVec) ? "Yes" : "No") << endl << endl;

    // Sort array using mergesort and print results
    vector<int> mergeVec(sample);
    int mergeComps = 0, mergeSwaps = 0;
    mergesort(mergeVec, mergeComps, mergeSwaps);
    cout << "After mergesort: ";
    print_vector(mergeVec);
    cout << "Comparisons: " << mergeComps << ", Swaps: " << mergeSwaps << endl;
    cout << "Is sorted? " << (is_sorted(mergeVec) ? "Yes" : "No") << endl << endl;
    
    // Sort array using quicksort and print results
    vector<int> quickVec(sample);
    int quickComps = 0, quickSwaps = 0;
    quicksort(quickVec, quickComps, quickSwaps);
    cout << "After quicksort: ";
    print_vector(quickVec);
    cout << "Comparisons: " << quickComps << ", Swaps: " << quickSwaps << endl;
    cout << "Is sorted? " << (is_sorted(quickVec) ? "Yes" : "No") << endl << endl;

    return 0;
}
