#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;

    Node(int value = NULL, Node* nt = nullptr, Node* pr = nullptr) : data(value), next(nt), prev(pr) {}
};

class CircularList {
private:
    Node* headRef = nullptr;

    void dispUnderKapot() const {
        if (headRef == nullptr) {
            cout << "Empty";
            return;
        }

        Node* current = headRef;
        do {
            cout << current->data << " ";
            current = current->next;
        } while (current != headRef);
    }

public:
    ~CircularList() {
        if (headRef == nullptr) return;

        Node* current = headRef;
        Node* nextNode;
        do {
            nextNode = current->next;
            delete current;
            current = nextNode;
        } while (current != headRef);
    }

    void append(int value) {
        if (headRef == nullptr) {
            headRef = new Node(value);
            headRef->next = headRef;
            headRef->prev = headRef;
        }
        else {
            
            Node* tail = headRef->prev;
            Node* newNode = new Node(value, headRef, tail);
            tail->next = newNode;
            headRef->prev = newNode;
        }
    }

    void remove(int value) {
        if (headRef == nullptr) return;

        Node* current = headRef;
        do {
            if (current->data == value) {
                if (current == headRef && headRef->next == headRef) {
                    // If it's the only element left
                    delete headRef;
                    headRef = nullptr;
                    return;
                }
                current->prev->next = current->next;
                current->next->prev = current->prev;
                if (current == headRef) {
                    headRef = headRef->next;
                }
                delete current;
                return;
            }
            current = current->next;
        } while (current != headRef);
    }

    void display() 
    {
        this->dispUnderKapot();
        cout << endl;
    }

    bool isCircular() const {
        if (headRef == nullptr) return true;

        Node* current = headRef;
        while (current->next != headRef) {
            if (current->next == nullptr) return false;
            current = current->next;
        }
        return true;
    }
};

int zxcmain() {
    CircularList* list = new CircularList();

    for (int i = 0; i < 4; i++) list->append(i);
   
    list->display();

    list->remove(2);
    list->display();

    cout << (list->isCircular() ? "Yes" : "No") << endl;

    list->remove(0);
    list->remove(1);
    list->remove(3);

    // After deletion:
    list->display();

    delete list;
    return 0;
} 