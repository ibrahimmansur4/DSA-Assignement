#include <iostream>
#include <string>
using namespace std;

struct Employee {
    int employeeID;
    string name;
    string contactNumber;
    int age;
    double salary;
    string maritalStatus;
    Employee* next;
};

class EmployeeManagementSystem {
private:
    Employee* head;

public:
    EmployeeManagementSystem() {
        head = nullptr;
    }

    ~EmployeeManagementSystem() {
        while (head != nullptr) {
            Employee* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addEmployee(int employeeID, const string& name, const string& contactNumber, int age, double salary, const string& maritalStatus) {
        if (age < 0 || salary < 0) {
            cout << "Invalid age or salary. Please provide valid values." << endl;
            return;
        }

        Employee* newEmployee = new Employee;
        newEmployee->employeeID = employeeID;
        newEmployee->name = name;
        newEmployee->contactNumber = contactNumber;
        newEmployee->age = age;
        newEmployee->salary = salary;
        newEmployee->maritalStatus = maritalStatus;
        newEmployee->next = nullptr;

        if (head == nullptr) {
            head = newEmployee;
        } else {
            Employee* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newEmployee;
        }

        cout << "Employee with ID " << employeeID << " has been added." << endl;
    }

    void removeEmployee(int employeeID) {
        if (head == nullptr) {
            cout << "Employee list is empty." << endl;
            return;
        }

        if (head->employeeID == employeeID) {
            Employee* temp = head;
            head = head->next;
            delete temp;
            cout << "Employee with ID " << employeeID << " has been removed." << endl;
            return;
        }

        Employee* current = head;
        while (current->next != nullptr && current->next->employeeID != employeeID) {
            current = current->next;
        }

        if (current->next == nullptr) {
            cout << "Employee with ID " << employeeID << " not found." << endl;
            return;
        }

        Employee* temp = current->next;
        current->next = current->next->next;
        delete temp;
        cout << "Employee with ID " << employeeID << " has been removed." << endl;
    }

    void updateEmployee(int employeeID, const string& name, const string& contactNumber, int age, double salary, const string& maritalStatus) {
        Employee* current = findEmployee(employeeID);

        if (current == nullptr) {
            cout << "Employee with ID " << employeeID << " not found." << endl;
            return;
        }

        if (age < 0 || salary < 0) {
            cout << "Invalid age or salary. Please provide valid values." << endl;
            return;
        }

        current->name = name;
        current->contactNumber = contactNumber;
        current->age = age;
        current->salary = salary;
        current->maritalStatus = maritalStatus;

        cout << "Employee with ID " << employeeID << " has been updated." << endl;
    }

    void displayEmployees() {
        if (head == nullptr) {
            cout << "Employee list is empty." << endl;
            return;
        }

        Employee* current = head;
        while (current != nullptr) {
            printEmployeeDetails(current);
            current = current->next;
        }
    }

private:
    Employee* findEmployee(int employeeID) {
        Employee* current = head;
        while (current != nullptr && current->employeeID != employeeID) {
            current = current->next;
        }
        return current;
    }

    void printEmployeeDetails(Employee* employee) {
        cout << "Employee ID: " << employee->employeeID << endl;
        cout << "Name: " << employee->name << endl;
        cout << "Contact Number: " << employee->contactNumber << endl;
        cout << "Age: " << employee->age << endl;
        cout << "Salary: " << employee->salary << endl;
        cout << "Marital Status: " << employee->maritalStatus << endl;
        cout << endl;
    }
};

int main() {
    EmployeeManagementSystem ems;

    int choice;
    do {
        cout << "\nEmployee Management System Menu\n";
        cout << "1. Add Employee\n";
        cout << "2. Remove Employee\n";
        cout << "3. Update Employee\n";
        cout << "4. Display Employees\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id, age;
                double salary;
                string name, contact, maritalStatus;
                cout << "Enter Employee ID: ";
                cin >> id;
                cout << "Enter Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Contact Number: ";
                cin >> contact;
                cout << "Enter Age: ";
                cin >> age;
                cout << "Enter Salary: ";
                cin >> salary;
                cout << "Enter Marital Status: ";
                cin >> maritalStatus;

                ems.addEmployee(id, name, contact, age, salary, maritalStatus);
                break;
            }
            case 2: {
                int idToRemove;
                cout << "Enter Employee ID to Remove: ";
                cin >> idToRemove;
                ems.removeEmployee(idToRemove);
                break;
            }
            case 3: {
                int idToUpdate, newAge;
                double newSalary;
                string newName, newContact, newMaritalStatus;
                cout << "Enter Employee ID to Update: ";
                cin >> idToUpdate;
                cout << "Enter New Name: ";
                cin.ignore();
                getline(cin, newName);
                cout << "Enter New Contact Number: ";
                cin >> newContact;
                cout << "Enter New Age: ";
                cin >> newAge;
                cout << "Enter New Salary: ";
                cin >> newSalary;
                cout << "Enter New Marital Status: ";
                cin >> newMaritalStatus;

                ems.updateEmployee(idToUpdate, newName, newContact, newAge, newSalary, newMaritalStatus);
                break;
            }
            case 4:
                ems.displayEmployees();
                break;
            case 0:
                cout << "Exiting Program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 0);

    return 0;
}
