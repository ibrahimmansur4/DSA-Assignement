#include <iostream>
#include <vector>

using namespace std;

class MaxPriorityQueue {
private:
    vector<int> heap;

    // Helper function to maintain the max-heap property
    void maxHeapify(int i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (left < heap.size() && heap[left] > heap[largest])
            largest = left;
        if (right < heap.size() && heap[right] > heap[largest])
            largest = right;

        if (largest != i) {
            swap(heap[i], heap[largest]);
            maxHeapify(largest);
        }
    }

public:
    // Constructor
    MaxPriorityQueue() {}

    // Insert an element with a priority
    void insert(int key) {
        heap.push_back(key);
        int i = heap.size() - 1;
        while (i > 0 && heap[(i - 1) / 2] < heap[i]) {
            swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    // Extract the maximum priority element
    int extractMax() {
        if (heap.empty()) {
            cerr << "Priority queue is empty!" << endl;
            return -1; // Assuming -1 represents an error
        }
        int max = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        maxHeapify(0);
        return max;
    }

    // Display the elements in the priority queue
    void display() {
        for (int num : heap)
            cout << num << " ";
        cout << endl;
    }

    // Increase the priority of an element in the queue
    void increasePriority(int index, int newPriority) {
        if (index >= heap.size() || index < 0) {
            cerr << "Invalid index!" << endl;
            return;
        }
        if (newPriority < heap[index]) {
            cerr << "New priority must be greater than current priority!" << endl;
            return;
        }
        heap[index] = newPriority;
        while (index > 0 && heap[(index - 1) / 2] < heap[index]) {
            swap(heap[index], heap[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }
};

int main() {
    MaxPriorityQueue pq;

    // Inserting elements with priorities
    pq.insert(10);
    pq.insert(20);
    pq.insert(15);
    pq.insert(5);

    // Displaying the priority queue
    cout << "Priority queue after insertion: ";
    pq.display();

    // Extracting the maximum priority element
    int max = pq.extractMax();
    cout << "Max priority element extracted: " << max << endl;

    // Displaying the priority queue after extraction
    cout << "Priority queue after extraction: ";
    pq.display();

    // Increasing the priority of an element
    pq.increasePriority(2, 25);

    // Displaying the priority queue after increasing priority
    cout << "Priority queue after increasing priority: ";
    pq.display();

    return 0;
}
