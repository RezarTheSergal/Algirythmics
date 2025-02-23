#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;

    Node(int value = NULL, Node* nt = nullptr, Node* pr = nullptr) : data(value), next(nt), prev(pr) {}
};

class CDLList {
private:
    Node* headRef = nullptr;

public:
    void append(int val) {
        Node* newNode = new Node(val);
        if (!headRef) {
            headRef = newNode;
            headRef->next = headRef;
            headRef->prev = headRef;
        }
        else {
            Node* tail = headRef->prev;
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = headRef;
            headRef->prev = newNode;
        }
    }

    void insertBefore(int targetValue, int newValue) {
        if (!headRef) return;

        Node* current = headRef;
        do {
            if (current->data == targetValue) {
                Node* newNode = new Node(newValue);
                newNode->next = current;
                newNode->prev = current->prev;
                current->prev->next = newNode;
                current->prev = newNode;

                if (current == headRef) {
                    headRef = newNode;
                }
                return;
            }
            current = current->next;
        } while (current != headRef);
    }

    void remove(int val) {
        if (!headRef) return;

        Node* current = headRef;
        do {
            if (current->data == val) {
                if (current->next == current) { // Lonely node :<
                    delete current;
                    headRef = nullptr;
                }
                else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                    // Updating head, if first node is deleted
                    if (current == headRef) {
                        headRef = current->next; 
                    }
                    delete current;
                }
                return;
            }
            current = current->next;
        } while (current != headRef);

        cout << "I refuse to elaborate" << endl;
    }

    int countNodes() {
        if (!headRef) return 0;

        int count = 0;
        Node* current = headRef;
        do {
            count++;
            current = current->next;
        } while (current != headRef);

        return count;
    }


    void displayForward() {
        if (!headRef) {
            cout << "NULL" << endl;
            return;
        }

        Node* current = headRef;
        do {
            cout << current->data << " <-> ";
            current = current->next;
        } while (current != headRef);
        cout << "(REP'S)" << endl;
    }


    void displayBackward() {
        if (!headRef) {
            cout << "NULL" << endl;
            return;
        }

        Node* current = headRef->prev;
        do {
            cout << current->data << " <-> ";
            current = current->prev;
        } while (current != headRef->prev);
        cout << "(REP'S)" << endl;
    }

    ~CDLList() {
        if (!headRef) return;

        Node* current = headRef;
        Node* nextNode;

        do {
            nextNode = current->next;
            delete current;
            current = nextNode;
        } while (current != headRef);
    }
};

int main() {
    CDLList* list = new CDLList();

    for (int i = 1; i < 6; i++) list->append(i);


    list->displayForward();
    list->displayBackward();

    list->insertBefore(5, 25);
    list->displayForward();


    list->remove(4);
    list->displayForward();

    cout << list->countNodes() << endl;

    delete list;
    return 0;
}