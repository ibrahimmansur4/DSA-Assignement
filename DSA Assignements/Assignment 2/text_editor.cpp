#include <iostream>
#include <stack>
#include <string>

using namespace std;

class TextEditor {
private:
    stack<string> undoStack;
    stack<string> redoStack;
    string currentText;

public:
    void insertText(const string& text) {
        undoStack.push(currentText);
        currentText += text;
        redoStack = stack<string>(); // Clear redo stack
    }

    void deleteText(int length) {
        if (length > currentText.length()) {
            length = currentText.length();
        }
        undoStack.push(currentText);
        currentText = currentText.substr(0, currentText.length() - length);
        redoStack = stack<string>(); // Clear redo stack
    }

    void undo() {
        if (!undoStack.empty()) {
            redoStack.push(currentText);
            currentText = undoStack.top();
            undoStack.pop();
        }
    }

    void redo() {
        if (!redoStack.empty()) {
            undoStack.push(currentText);
            currentText = redoStack.top();
            redoStack.pop();
        }
    }

    void printCurrentText() {
        cout << "Current Text: " << currentText << endl;
    }
};

int main() {
    TextEditor editor;
    int choice;
    string text;
    int length;

    do {
        cout << "Text Editor Menu:" << endl;
        cout << "1. Insert Text" << endl;
        cout << "2. Delete Text" << endl;
        cout << "3. Undo" << endl;
        cout << "4. Redo" << endl;
        cout << "5. Print Current Text" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter text to insert: ";
                cin.ignore();
                getline(cin, text);
                editor.insertText(text);
                break;
            case 2:
                cout << "Enter length of text to delete: ";
                cin >> length;
                editor.deleteText(length);
                break;
            case 3:
                editor.undo();
                break;
            case 4:
                editor.redo();
                break;
            case 5:
                editor.printCurrentText();
                break;
            case 0:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

        cout << endl;
    } while (choice != 0);

    return 0;
}