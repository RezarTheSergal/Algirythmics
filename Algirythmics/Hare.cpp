#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;

    Node(int value = NULL, Node* nt = nullptr, Node* pr = nullptr) : data(value), next(nt), prev(pr) {}
};


class List {
private:
    Node* headRef = nullptr;

public:
    void append(int val) {
        Node* newNode = new Node(val);
        if (!headRef) {
            headRef = newNode;
        }
        else {
            Node* temp = headRef;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->prev = temp;
        }
    }

    ~List() {
        Node* temp;
        while (headRef) {
            temp = headRef;
            headRef = headRef->next;
            exit(temp->data);
            delete temp;
        }
    }

    void createSkip(int from, int to) {
        Node* fromNode = nullptr;
        Node* toNode = nullptr;
        Node* temp = headRef;

        while (temp) {
            if (temp->data == from) fromNode = temp;
            if (temp->data == to) toNode = temp;
            temp = temp->next;
        }

        if (fromNode && toNode) {
            fromNode->next = toNode;
        }
    }

    bool hasLoops() {
        if (!headRef || !headRef->next) return false;

        Node* turtle = headRef;
        Node* hare = headRef;

        while (hare && hare->next) {
            turtle = turtle->next;
            hare = hare->next->next;

            if (turtle == hare) {
                return true;
            }
        }

        return false;
    }

    bool hasJumps() {
        if (!headRef || !headRef->next) return false;

        Node* current = headRef;
        while (current->next) {
            if (current->next->prev != current) {
                return true;
            }
            current = current->next;
        }

        return false;
    }

    void display() {
        Node* temp = headRef;
        while (temp) {
            cout << temp->data << " <-> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

};

int gfhfgmain() {
    List* list = new List();

    for (int i = 1; i <= 5; ++i) list->append(i);

    list->display();

    list->createSkip(2, 4);

    cout << (list->hasLoops() ? "Yes" : "No") << endl;

    cout << (list->hasJumps() ? "Yes" : "No") << endl;

    delete list;
    return 0;
}