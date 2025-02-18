#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int value = NULL, Node* nt = nullptr) : data(value), next(nt) {}
};

class List {
private:
    Node* headRef = nullptr;

public:
    ~List() {
        Node* current = headRef;
        while (current) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    void append(int value) {
        Node* newNode = new Node(value);
        if (headRef == nullptr) {
            headRef = newNode;
        }
        else {
            Node* current = headRef;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void setSkip(int fromValue, int toValue) {
        Node* fromNode = nullptr;
        Node* toNode = nullptr;
        Node* current = headRef;

        while (current != nullptr) {
            if (current->data == fromValue) {
                fromNode = current;
            }
            if (current->data == toValue) {
                toNode = current;
            }
            if (fromNode != nullptr && toNode != nullptr) break;
            current = current->next;
        }

        if (fromNode != nullptr && toNode != nullptr) {
            fromNode->next = toNode;
        }
    }

    bool hasSkips() const {
        if (!headRef || !headRef->next) return false;

        Node* turtle = headRef;
        Node* hare = headRef;

        while (hare != nullptr && hare->next  != nullptr) {
            turtle = turtle->next;
            hare = hare->next->next;

            if (turtle == hare) {
                return true;
            }
        }

        return false;
    }

    void print() const {
        Node* current = headRef;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main() {

    List* list = new List();

    for (int i = 1; i < 6; i++) list->append(i);

    // Before skip
    list->print();

    cout << (list->hasSkips() ? "Yes" : "No") << endl;

    list->setSkip(3, 1);
    // After skip
    cout << (list->hasSkips() ? "Yes" : "No") << endl;
    // Funni function
    quick_exit(0);
}