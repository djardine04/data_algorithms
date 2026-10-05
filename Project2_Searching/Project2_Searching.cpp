#include <iostream>
#include <cmath>
#include <algorithm> // for std::sort in testing

/**
 * Performs a linear search for target in lyst.
 * @param lyst The array to search.
 * @param size The size of the array.
 * @param target The value to search for.
 * @param found Reference to bool, set to true if found, false otherwise.
 * @return The number of comparisons performed.
 */
int linear_search(int lyst[], int size, int target, bool& found) {
    int comparisons = 0; //counter variable declared

    for (int i = 0; i < size; ++i) {
        comparisons++; //counts the number of comparisons made
        if (lyst[i] == target) {
            found = true; //shows that the value was found
            return comparisons;
        }
    }
    found = false; //shows that the value was not found
    return comparisons;
}

/**
 * Performs a binary search for target in lyst.
 * @param lyst The array to search (must be sorted).
 * @param size The size of the array.
 * @param target The value to search for.
 * @param found Reference to bool, set to true if found, false otherwise.
 * @return The number of comparisons performed.
 */
int binary_search(int lyst[], int size, int target, bool& found) {
    int left = 0;
    int right = size - 1;
    int comparisons = 0;
    found = false;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        comparisons++;
        if (lyst[mid] < target) {
            left = mid + 1;
        }
        else if (lyst[mid] > target) {
            right = mid - 1;
        }
        else if (lyst[mid] == target) {
            found = true;
            return comparisons;
        }
    }
    found = false;
    return comparisons;
}

/**
 * Performs a jump search for target in lyst.
 * @param lyst The array to search (must be sorted).
 * @param size The size of the array.
 * @param target The value to search for.
 * @param found Reference to bool, set to true if found, false otherwise.
 * @return The number of comparisons performed.
 */
int jump_search(int lyst[], int size, int target, bool& found) {
    int comparisons = 0;
    int step = static_cast<int>(std::sqrt(size));
    int prev = 0;
    int next = std::min(step, size); // create a 'next' variable that shows the next block


    // Find the block where the element may be present
    while (next < size && lyst[next - 1] < target) {
        prev = next;
        next = std::min(next + step, size);
        comparisons++;
    }
    comparisons++;
    // Linear search in the found block
    for (int i = prev; i < std::min(next, size); ++i) {
        comparisons++; //counts the number of comparisons made
        if (lyst[i] == target) {
            found = true; //shows that the value was found
            return comparisons;
        }
    }
        found = false; //shows that the value was not found
        return comparisons;
}


// Example main function for testing - in the future you will be expected to do this kind of thing yourself...
int main() {
    // Example data
    int data[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int size = 10;

    // The array must be sorted for binary and jump search
    // (data is already sorted here)

    int targets[] = {7, 2, 19, 1, 20};
    int num_targets = 5;
    for (int i = 0; i < num_targets; ++i) {
        bool found;
        int comps;
        std::cout << "Searching for " << targets[i] << ":\n";

        comps = linear_search(data, size, targets[i], found);
        std::cout << "  Linear Search: Found=" << (found ? "true" : "false") << ", Comparisons=" << comps << std::endl;

        comps = binary_search(data, size, targets[i], found);
        std::cout << "  Binary Search: Found=" << (found ? "true" : "false") << ", Comparisons=" << comps << std::endl;

        comps = jump_search(data, size, targets[i], found);
        std::cout << "  Jump Search: Found=" << (found ? "true" : "false") << ", Comparisons=" << comps << std::endl;

        std::cout << std::endl;
    }
    return 0;
}
