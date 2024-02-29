#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    // Function to insert a new node at the beginning of the list
    void insertAtBeginning(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    // Function to insert a new node at the middle of the list
    void insertAtMiddle(int value) {
        if (head == nullptr) {
            insertAtBeginning(value);
            return;
        }

        Node* slow = head;
        Node* fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        Node* newNode = new Node(value);
        newNode->next = slow->next;
        slow->next = newNode;
    }

    // Function to insert a new node at the end of the list
    void insertAtEnd(int value) {
        Node* newNode = new Node(value);

        if (head == nullptr) {
            head = newNode;
            return;
        }

        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }

        temp->next = newNode;
    }

    // Function to delete a node from the list
    void deleteNode(int value) {
        if (head == nullptr) {
            cout << "List is empty. Cannot delete." << endl;
            return;
        }

        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            cout << "Node with value " << value << " deleted." << endl;
            return;
        }

        Node* temp = head;
        while (temp->next != nullptr && temp->next->data != value) {
            temp = temp->next;
        }

        if (temp->next == nullptr) {
            cout << "Node with value " << value << " not found." << endl;
            return; // Node with the given value not found
        }

        Node* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
        cout << "Node with value " << value << " deleted." << endl;
    }

    // Function to search for a node based on a given value
    Node* searchNode(int value) {
        Node* temp = head;
        while (temp != nullptr && temp->data != value) {
            temp = temp->next;
        }

        return temp;
    }

    // Function to traverse and print the contents of the list
    void printList() {
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }

        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Function to display the interactive menu
    void displayMenu() {
        cout << "Linked List Menu:" << endl;
        cout << "1. Insert at Beginning" << endl;
        cout << "2. Insert at Middle" << endl;
        cout << "3. Insert at End" << endl;
        cout << "4. Delete Node" << endl;
        cout << "5. Search Node" << endl;
        cout << "6. Print List" << endl;
        cout << "7. Exit" << endl;
    }

    // Function to interactively handle user input
    void interactiveMenu() {
        int choice;
        do {
            displayMenu();
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    int value;
                    cout << "Enter value to insert at the beginning: ";
                    cin >> value;
                    insertAtBeginning(value);
                    break;
                }
                case 2: {
                    int value;
                    cout << "Enter value to insert at the middle: ";
                    cin >> value;
                    insertAtMiddle(value);
                    break;
                }
                case 3: {
                    int value;
                    cout << "Enter value to insert at the end: ";
                    cin >> value;
                    insertAtEnd(value);
                    break;
                }
                case 4: {
                    int value;
                    cout << "Enter value to delete: ";
                    cin >> value;
                    deleteNode(value);
                    break;
                }
                case 5: {
                    int value;
                    cout << "Enter value to search: ";
                    cin >> value;
                    Node* result = searchNode(value);
                    if (result != nullptr) {
                        cout << "Node with value " << value << " found." << endl;
                    } else {
                        cout << "Node with value " << value << " not found." << endl;
                    }
                    break;
                }
                case 6:
                    printList();
                    break;
                case 7:
                    cout << "Exiting Linked List Menu. Goodbye!" << endl;
                    break;
                default:
                    cout << "Invalid choice. Please enter a valid option." << endl;
            }
        } while (choice != 7);
    }
};

int main() {
    LinkedList myList;

    myList.interactiveMenu();

    return 0;
}
