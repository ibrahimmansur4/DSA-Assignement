#include <iostream>
#include <string>
using namespace std;

struct CartItem {
    int itemID;
    string itemName;
    double price;
    int quantity;
    CartItem* next;
};

class ShoppingCart {
private:
    CartItem* head;

public:
    ShoppingCart() {
        head = nullptr;
    }

    ~ShoppingCart() {
        while (head != nullptr) {
            CartItem* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addItem(int itemID, const string& itemName, double price, int quantity) {
        if (price < 0 || quantity < 0) {
            cout << "Error: Negative price or quantity is not allowed." << endl;
            return;
        }

        CartItem* newItem = new CartItem;
        newItem->itemID = itemID;
        newItem->itemName = itemName;
        newItem->price = price;
        newItem->quantity = quantity;
        newItem->next = nullptr;

        if (head == nullptr) {
            head = newItem;
        } else {
            CartItem* current = head;
            while (current->next != nullptr) {
                if (current->itemID == itemID) {
                    // Item already in the cart, update quantity
                    current->quantity += quantity;
                    delete newItem;
                    return;
                }
                current = current->next;
            }

            if (current->itemID == itemID) {
                // Item already in the cart, update quantity
                current->quantity += quantity;
                delete newItem;
                return;
            }

            current->next = newItem;
        }

        cout << "Item '" << itemName << "' added to the shopping cart." << endl;
    }

    void removeItem(int itemID) {
        if (head == nullptr) {
            cout << "Shopping cart is empty." << endl;
            return;
        }

        if (head->itemID == itemID) {
            CartItem* temp = head;
            head = head->next;
            delete temp;
            cout << "Item removed from the shopping cart." << endl;
            return;
        }

        CartItem* current = head;
        while (current->next != nullptr && current->next->itemID != itemID) {
            current = current->next;
        }

        if (current->next == nullptr) {
            cout << "Item not found in the shopping cart." << endl;
            return;
        }

        CartItem* temp = current->next;
        current->next = current->next->next;
        delete temp;
        cout << "Item removed from the shopping cart." << endl;
    }

    void updateQuantity(int itemID, int newQuantity) {
        if (head == nullptr) {
            cout << "Shopping cart is empty." << endl;
            return;
        }

        CartItem* current = head;
        while (current != nullptr) {
            if (current->itemID == itemID) {
                current->quantity = newQuantity;
                cout << "Quantity updated for the item in the shopping cart." << endl;
                return;
            }
            current = current->next;
        }

        cout << "Item not found in the shopping cart." << endl;
    }

    double calculateTotalPrice() {
        double total = 0.0;
        CartItem* current = head;
        while (current != nullptr) {
            total += (current->price * current->quantity);
            current = current->next;
        }
        return total;
    }

    void displayCart() {
        if (head == nullptr) {
            cout << "Shopping cart is empty." << endl;
            return;
        }

        CartItem* current = head;
        while (current != nullptr) {
            cout << "Item ID: " << current->itemID << endl;
            cout << "Item Name: " << current->itemName << endl;
            cout << "Price per unit: $" << current->price << endl;
            cout << "Quantity: " << current->quantity << endl;
            cout << endl;
            current = current->next;
        }

        cout << "Total Price: $" << calculateTotalPrice() << endl;
    }

    void displayMenu() {
        cout << "Shopping Cart Menu:" << endl;
        cout << "1. Add Item" << endl;
        cout << "2. Remove Item" << endl;
        cout << "3. Update Quantity" << endl;
        cout << "4. Display Cart" << endl;
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
                    int itemID, quantity;
                    double price;
                    string itemName;

                    cout << "Enter Item ID: ";
                    cin >> itemID;

                    cout << "Enter Item Name: ";
                    cin.ignore();
                    getline(cin, itemName);

                    cout << "Enter Price per unit: $";
                    cin >> price;

                    cout << "Enter Quantity: ";
                    cin >> quantity;

                    addItem(itemID, itemName, price, quantity);
                    break;
                }
                case 2: {
                    int itemID;
                    cout << "Enter Item ID to remove: ";
                    cin >> itemID;
                    removeItem(itemID);
                    break;
                }
                case 3: {
                    int itemID, newQuantity;
                    cout << "Enter Item ID to update quantity: ";
                    cin >> itemID;
                    cout << "Enter new Quantity: ";
                    cin >> newQuantity;
                    updateQuantity(itemID, newQuantity);
                    break;
                }
                case 4:
                    displayCart();
                    break;
                case 5:
                    cout << "Exiting Shopping Cart. Goodbye!" << endl;
                    break;
                default:
                    cout << "Invalid choice. Please enter a valid option." << endl;
            }
        } while (choice != 5);
    }
};

int main() {
    ShoppingCart cart;

    // Enter interactive menu
    cart.interactiveMenu();

    return 0;
}
