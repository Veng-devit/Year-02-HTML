#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string command;
    Node* next;
    Node* prev;

    Node(string cmd) {
        command = cmd;
        next = nullptr;
        prev = nullptr;
    }
};

class UndoRedo {
private:
    Node* head;
    Node* tail;
    Node* current;

public:
    UndoRedo() {
        head = nullptr;
        tail = nullptr;
        current = nullptr;
    }
    void execute(string cmd) {
        Node* newNode = new Node(cmd);

        if (head == nullptr) {
            head = tail = current = newNode;
        } else {
            Node* temp = current->next;
            while (temp != nullptr) {
                Node* toDelete = temp;
                temp = temp->next;
                delete toDelete;
            }

            current->next = newNode;
            newNode->prev = current;
            tail = current = newNode;
        }

        cout << "Executed: " << cmd << endl;
    }
    void undo() {
        if (current == nullptr) {
            cout << "Nothing to undo!" << endl;
        } else {
            cout << "Undo: " << current->command << endl;
            current = current->prev;
        }
    }
    void redo() {
        if (current == nullptr) {
            if (head != nullptr) {
                current = head;
                cout << "Redo: " << current->command << endl;
            } else {
                cout << "Nothing to redo!" << endl;
            }
        } else if (current->next != nullptr) {
            current = current->next;
            cout << "Redo: " << current->command << endl;
        } else {
            cout << "Nothing to redo!" << endl;
        }
    }
    void showHistory() {
        Node* temp = head;
        cout << "History: ";
        while (temp != nullptr) {
            if (temp == current)
                cout << "[" << temp->command << "] ";
            else
                cout << temp->command << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    UndoRedo system;

    system.execute("Open File");
    system.execute("Edit Text");
    system.execute("Save File");

    system.showHistory();

    system.undo();
    system.undo();
    system.redo();

    system.execute("Print File");
    system.showHistory();

    return 0;
}
