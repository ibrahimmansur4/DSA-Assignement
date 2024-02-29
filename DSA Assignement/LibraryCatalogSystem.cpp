#include <iostream>
#include <string>
using namespace std;

struct Book {
    string title;
    string author;
    int copies;
    Book* next;
    Book* prev;
};

class LibraryCatalogSystem {
private:
    Book* head;

public:
    LibraryCatalogSystem() {
        head = nullptr;
    }

    ~LibraryCatalogSystem() {
        while (head != nullptr) {
            Book* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addBook(const string& title, const string& author, int copies) {
        Book* newBook = new Book;
        newBook->title = title;
        newBook->author = author;
        newBook->copies = copies;
        newBook->next = nullptr;
        newBook->prev = nullptr;

        if (head == nullptr) {
            head = newBook;
        } else {
            Book* current = head;
            while (current->next != nullptr) {
                if (current->title == title && current->author == author) {
                    current->copies += copies;
                    delete newBook;
                    return;
                }
                current = current->next;
            }
            if (current->title == title && current->author == author) {
                current->copies += copies;
                delete newBook;
                return;
            }
            current->next = newBook;
            newBook->prev = current;
        }

        cout << "Book \"" << title << "\" by " << author << " added to the catalog with " << copies << " copies." << endl;
    }

    void removeBook(const string& title, const string& author) {
        if (head == nullptr) {
            cout << "Library catalog is empty." << endl;
            return;
        }

        if (head->title == title && head->author == author) {
            Book* temp = head;
            head = head->next;
            if (head != nullptr) {
                head->prev = nullptr;
            }
            delete temp;
            cout << "Book \"" << title << "\" by " << author << " has been removed from the catalog." << endl;
            return;
        }

        Book* current = head;
        while (current != nullptr && !(current->title == title && current->author == author)) {
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Book \"" << title << "\" by " << author << " not found in the catalog." << endl;
            return;
        }

        if (current->next != nullptr) {
            current->next->prev = current->prev;
        }
        if (current->prev != nullptr) {
            current->prev->next = current->next;
        }

        delete current;
        cout << "Book \"" << title << "\" by " << author << " has been removed from the catalog." << endl;
    }

    void searchBookByTitle(const string& title) {
        searchBook(title, "", true);
    }

    void searchBookByAuthor(const string& author) {
        searchBook("", author, true);
    }

    void booksByAuthor(const string& author) {
        int count = 0;
        Book* current = head;
        while (current != nullptr) {
            if (current->author == author) {
                count += current->copies;
            }
            current = current->next;
        }
        cout << "Number of books by " << author << " in the catalog: " << count << endl;
    }

    void displayCatalogue() {
        if (head == nullptr) {
            cout << "Library catalog is empty." << endl;
            return;
        }

        Book* current = head;
        while (current != nullptr) {
            cout << "Title: " << current->title << endl;
            cout << "Author: " << current->author << endl;
            cout << "Number of Copies: " << current->copies << endl;
            cout << endl;
            current = current->next;
        }
    }

    void displayMenu() {
        cout << "Library Catalog System Menu:" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Remove Book" << endl;
        cout << "3. Search Book by Title" << endl;
        cout << "4. Search Book by Author" << endl;
        cout << "5. Number of Books by Author" << endl;
        cout << "6. Display Catalogue" << endl;
        cout << "7. Exit" << endl;
    }

    void interactiveMenu() {
        int choice;
        do {
            displayMenu();
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    string title, author;
                    int copies;
                    cout << "Enter Book Title: ";
                    cin.ignore();
                    getline(cin, title);
                    cout << "Enter Author: ";
                    getline(cin, author);
                    cout << "Enter Number of Copies: ";
                    cin >> copies;
                    addBook(title, author, copies);
                    break;
                }
                case 2: {
                    string title, author;
                    cout << "Enter Book Title: ";
                    cin.ignore();
                    getline(cin, title);
                    cout << "Enter Author: ";
                    getline(cin, author);
                    removeBook(title, author);
                    break;
                }
                case 3: {
                    string title;
                    cout << "Enter Book Title: ";
                    cin.ignore();
                    getline(cin, title);
                    searchBookByTitle(title);
                    break;
                }
                case 4: {
                    string author;
                    cout << "Enter Author: ";
                    cin.ignore();
                    getline(cin, author);
                    searchBookByAuthor(author);
                    break;
                }
                case 5: {
                    string author;
                    cout << "Enter Author: ";
                    cin.ignore();
                    getline(cin, author);
                    booksByAuthor(author);
                    break;
                }
                case 6:
                    displayCatalogue();
                    break;
                case 7:
                    cout << "Exiting Library Catalog System. Goodbye!" << endl;
                    break;
                default:
                    cout << "Invalid choice. Please enter a valid option." << endl;
            }
        } while (choice != 7);
    }
    private:
        void searchBook(const string& title, const string& author, bool displayDetails) {
            if (head == nullptr) {
                cout << "Library catalog is empty." << endl;
                return;
            }

            Book* current = head;
            bool found = false;

            while (current != nullptr) {
                if ((title.empty() || current->title == title) && (author.empty() || current->author == author)) {
                    found = true;

                    if (displayDetails) {
                        cout << "Title: " << current->title << endl;
                        cout << "Author: " << current->author << endl;
                        cout << "Number of Copies: " << current->copies << endl;
                        cout << endl;
                    }
                }
                current = current->next;
            }

            if (!found && !displayDetails) {
                cout << "Book \"" << title << "\" by " << author << " not found in the catalog." << endl;
            }
        }
};

int main() {
    LibraryCatalogSystem library;

    // Add books
    library.addBook("The Catcher in the Rye", "J.D. Salinger", 5);
    library.addBook("To Kill a Mockingbird", "Harper Lee", 3);
    library.addBook("The Great Gatsby", "F. Scott Fitzgerald", 8);
    library.addBook("The Catcher in the Rye", "J.D. Salinger", 2); // Adding more copies

    // Display catalog
    cout << "Library Catalog:" << endl;
    library.displayCatalogue();

    // Enter interactive menu
    library.interactiveMenu();

    return 0;
}
