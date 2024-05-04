#include <iostream>
#include <vector>

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

int main() {
    // Example 1: Merge Sort
    vector<int> example1 = {12, 11, 13, 5, 6, 7};
    mergeSort(example1, 0, example1.size() - 1);
    cout << "Merge Sort Example 1: ";
    for (int num : example1) cout << num << " ";
    cout << endl;

    // Example 2: Merge Sort
    vector<int> example2 = {38, 27, 43, 3, 9, 82, 10};
    mergeSort(example2, 0, example2.size() - 1);
    cout << "Merge Sort Example 2: ";
    for (int num : example2) cout << num << " ";
    cout << endl;

    // Example 3: Merge Sort
    vector<int> example3 = {5, 2, 9, 1, 6};
    mergeSort(example3, 0, example3.size() - 1);
    cout << "Merge Sort Example 3: ";
    for (int num : example3) cout << num << " ";
    cout << endl;

    // Example 1: Heap Sort
    vector<int> example4 = {12, 11, 13, 5, 6, 7};
    heapSort(example4);
    cout << "Heap Sort Example 1: ";
    for (int num : example4) cout << num << " ";
    cout << endl;

    // Example 2: Heap Sort
    vector<int> example5 = {38, 27, 43, 3, 9, 82, 10};
    heapSort(example5);
    cout << "Heap Sort Example 2: ";
    for (int num : example5) cout << num << " ";
    cout << endl;

    // Example 3: Heap Sort
    vector<int> example6 = {5, 2, 9, 1, 6};
    heapSort(example6);
    cout << "Heap Sort Example 3: ";
    for (int num : example6) cout << num << " ";
    cout << endl;

    return 0;
}
