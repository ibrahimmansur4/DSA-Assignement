#include <iostream>
#include <string>
#include <regex>
using namespace std;

struct Event {
    string name;
    string date;
    string details;
    Event* next;
    Event* prev;
};

class EventScheduler {
private:
    Event* head;

public:
    EventScheduler() {
        head = nullptr;
    }

    ~EventScheduler() {
        while (head != nullptr) {
            Event* temp = head;
            head = head->next;
            delete temp;
        }
    }

    bool isDateValid(const string& date) {
        // Validate date format (YYYY-MM-DD)
        regex dateRegex("\\d{4}-\\d{2}-\\d{2}");
        return regex_match(date, dateRegex);
    }

    void addEvent(const string& name, const string& date, const string& details) {
        if (!isDateValid(date)) {
            cout << "Incorrect date format. Please use YYYY-MM-DD." << endl;
            return;
        }

        Event* newEvent = new Event;
        newEvent->name = name;
        newEvent->date = date;
        newEvent->details = details;
        newEvent->next = nullptr;
        newEvent->prev = nullptr;

        if (head == nullptr || date < head->date) {
            newEvent->next = head;
            if (head != nullptr) {
                head->prev = newEvent;
            }
            head = newEvent;
        } else {
            Event* current = head;
            while (current->next != nullptr && date >= current->next->date) {
                current = current->next;
            }

            newEvent->next = current->next;
            newEvent->prev = current;

            if (current->next != nullptr) {
                current->next->prev = newEvent;
            }

            current->next = newEvent;
        }

        cout << "Event '" << name << "' on " << date << " added to the schedule." << endl;
    }

    void removeEvent(const string& name) {
        if (head == nullptr) {
            cout << "Event schedule is empty." << endl;
            return;
        }

        if (head->name == name) {
            Event* temp = head;
            head = head->next;
            if (head != nullptr) {
                head->prev = nullptr;
            }
            delete temp;
            cout << "Event '" << name << "' has been removed from the schedule." << endl;
            return;
        }

        Event* current = head;
        while (current != nullptr && current->name != name) {
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Event '" << name << "' not found in the schedule." << endl;
            return;
        }

        if (current->next != nullptr) {
            current->next->prev = current->prev;
        }
        if (current->prev != nullptr) {
            current->prev->next = current->next;
        }

        delete current;
        cout << "Event '" << name << "' has been removed from the schedule." << endl;
    }

    void updateEventDetails(const string& name, const string& newDetails) {
        Event* current = head;
        while (current != nullptr && current->name != name) {
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Event '" << name << "' not found in the schedule." << endl;
            return;
        }

        current->details = newDetails;
        cout << "Details for Event '" << name << "' updated." << endl;
    }

    void displayEvents() {
        if (head == nullptr) {
            cout << "Event schedule is empty." << endl;
            return;
        }

        Event* current = head;
        while (current != nullptr) {
            cout << "Name: " << current->name << endl;
            cout << "Date: " << current->date << endl;
            cout << "Details: " << current->details << endl;
            cout << endl;
            current = current->next;
        }
    }

    void displayMenu() {
        cout << "Event Scheduler Menu:" << endl;
        cout << "1. Add Event" << endl;
        cout << "2. Remove Event" << endl;
        cout << "3. Update Event Details" << endl;
        cout << "4. Display Events" << endl;
        cout << "5. Exit" << endl;
    }

    void interactiveMenu() {
        int choice;
        do {
            displayMenu();
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    string name, date, details;
                    cout << "Enter Event Name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter Date (YYYY-MM-DD): ";
                    getline(cin, date);
                    cout << "Enter Event Details: ";
                    getline(cin, details);
                    addEvent(name, date, details);
                    break;
                }
                case 2: {
                    string name;
                    cout << "Enter Event Name: ";
                    cin.ignore();
                    getline(cin, name);
                    removeEvent(name);
                    break;
                }
                case 3: {
                    string name, newDetails;
                    cout << "Enter Event Name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter New Details: ";
                    getline(cin, newDetails);
                    updateEventDetails(name, newDetails);
                    break;
                }
                case 4:
                    displayEvents();
                    break;
                case 5:
                    cout << "Exiting Event Scheduler. Goodbye!" << endl;
                    break;
                default:
                    cout << "Invalid choice. Please enter a valid option." << endl;
            }
        } while (choice != 5);
    }
};

int main() {
    EventScheduler scheduler;

    // Add events
    scheduler.addEvent("Meeting", "2024-03-01", "Team collaboration meeting");
    scheduler.addEvent("Conference", "2024-03-05", "Annual industry conference");
    scheduler.addEvent("Birthday Party", "2024-03-15", "Celebrating a friend's birthday");

    // Enter interactive menu
    scheduler.interactiveMenu();

    return 0;
}
