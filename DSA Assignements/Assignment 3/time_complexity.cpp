#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

// Merge function for Merge Sort
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    vector<int> L(n1), R(n2);

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Merge Sort function
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// Heapify function for Heap Sort
void heapify(vector<int>& arr, int n, int i) {
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1; // Left child
    int right = 2 * i + 2; // Right child

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// Heap Sort function
void heapSort(vector<int>& arr) {
    int n = arr.size();

    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]); // Move current root to end
        heapify(arr, i, 0); // Call max heapify on the reduced heap
    }
}

// Function to generate a random array of given size
vector<int> generateRandomArray(int size) {
    vector<int> arr;
    srand(time(0)); // Seed the random number generator
    for (int i = 0; i < size; ++i) {
        arr.push_back(rand() % 1000); // Generate random integers between 0 and 999
    }
    return arr;
}

// Function to measure the time taken by Merge Sort to sort an array
double measureMergeSortTime(int size) {
    vector<int> arr = generateRandomArray(size);

    clock_t start = clock();
    mergeSort(arr, 0, arr.size() - 1);
    clock_t end = clock();

    return double(end - start) / CLOCKS_PER_SEC;
}

// Function to measure the time taken by Heap Sort to sort an array
double measureHeapSortTime(int size) {
    vector<int> arr = generateRandomArray(size);

    clock_t start = clock();
    heapSort(arr);
    clock_t end = clock();

    return double(end - start) / CLOCKS_PER_SEC;
}

int main() {
    // Test sizes
    vector<int> testSizes = {1000, 5000, 10000, 50000, 100000};

    cout << "Time taken by Merge Sort:" << endl;
    for (int size : testSizes) {
        double timeTaken = measureMergeSortTime(size);
        cout << "Size " << size << ": " << timeTaken << " seconds" << endl;
    }

    cout << "\nTime taken by Heap Sort:" << endl;
    for (int size : testSizes) {
        double timeTaken = measureHeapSortTime(size);
        cout << "Size " << size << ": " << timeTaken << " seconds" << endl;
    }

    return 0;
}
