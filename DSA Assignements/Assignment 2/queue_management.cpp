#include <iostream>
#include <queue>
#include <string>
using namespace std;

class PrintJob {
public:
    int jobNumber;
    int numPages;

    PrintJob(int jobNum, int pages) : jobNumber(jobNum), numPages(pages) {}
};

class PrintingQueue {
private:
    queue<PrintJob> printQueue;
    int nextJobNumber;

public:
    PrintingQueue() : nextJobNumber(1) {}

    void enqueueJob(int numPages) {
        PrintJob newJob(nextJobNumber++, numPages);
        printQueue.push(newJob);
        cout << "Print job with job number " << newJob.jobNumber << " and " << newJob.numPages << " pages added to the queue." << endl;
    }

    void dequeueJob() {
        if (printQueue.empty()) {
            cout << "Printing queue is empty. No job to dequeue." << endl;
        } else {
            PrintJob job = printQueue.front();
            printQueue.pop();
            cout << "Print job with job number " << job.jobNumber << " and " << job.numPages << " pages removed from the queue." << endl;
        }
    }

    void displayQueue() {
        cout << "Printing Queue Status:" << endl;
        cout << "----------------------" << endl;
        if (printQueue.empty()) {
            cout << "Printing queue is empty." << endl;
        } else {
            queue<PrintJob> tempQueue = printQueue;
            while (!tempQueue.empty()) {
                PrintJob job = tempQueue.front();
                cout << "Job Number: " << job.jobNumber << ", Pages: " << job.numPages << endl;
                tempQueue.pop();
            }
        }
    }
};

int main() {
    PrintingQueue printingQueue;
    int choice;
    int numPages;

    do {
        cout << "\nPrinting Queue Management System" << endl;
        cout << "1. Submit Print Job" << endl;
        cout << "2. Process Print Job" << endl;
        cout << "3. Display Queue" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter number of pages for the print job: ";
                cin >> numPages;
                printingQueue.enqueueJob(numPages);
                break;
            case 2:
                printingQueue.dequeueJob();
                break;
            case 3:
                printingQueue.displayQueue();
                break;
            case 0:
                cout << "Exiting Printing Queue Management System. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}
