#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
public:
    string name;
    vector<string> phones;

    Person(const string n) : name(n) {}

    void addPhone(const string phone) {
        phones.push_back(phone);
    }

    void display() const {
        cout << name << ": ";
        for (const auto& phone : phones) {
            cout << phone << " ";
        }
        cout << endl;
    }
};

struct Node {
    Person person;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(const string name) : person(name) {}
};

class PhoneBook {
private:
    Node* root = nullptr;

    Node* insert(Node* node, const string name, const string phone) {
        if (!node) {
            Node* newNode = new Node(name);
            newNode->person.addPhone(phone);
            return newNode;
        }

        if (name < node->person.name) {
            node->left = insert(node->left, name, phone);
        }
        else if (name > node->person.name) {
            node->right = insert(node->right, name, phone);
        }

        node->person.addPhone(phone);
        return node;
    }

    Node* search(Node* node, const string name) const {
        if (!node || node->person.name == name) {
            return node;
        }

        if (name < node->person.name) {
            return search(node->left, name);
        }
        else {
            return search(node->right, name);
        }
    }

    Node* deleteNode(Node* node, const string name) {
        if (!node) return nullptr;

        if (name < node->person.name) {
            node->left = deleteNode(node->left, name);
        }
        else if (name > node->person.name) {
            node->right = deleteNode(node->right, name);
        }

        // Node found
        if (!node->left && !node->right) {
            // No children
            delete node;
            return nullptr;
        }
        else if (!node->left) {
            // Only right child
            Node* temp = node->right;
            delete node;
            return temp;
        }
        else if (!node->right) {
            // Only left child
            Node* temp = node->left;
            delete node;
            return temp;
        }
        // Two children
        Node* minNode = findMin(node->right);
        node->person = minNode->person;
        node->right = deleteNode(node->right, minNode->person.name);
        return node;
    }

    Node* findMin(Node* node) const {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    void inorder(Node* node) const {
        if (!node) return;

        inorder(node->left);
        node->person.display();
        inorder(node->right);
    }

    void clear(Node* node) {
        if (!node) return;

        clear(node->left);
        clear(node->right);
        delete node;
    }

public:

    ~PhoneBook() {
        clear(root);
    }

    void add(const string name, const string phone) {
        root = insert(root, name, phone);
    }

    void find(const string name) const {
        Node* node = search(root, name);
        if (node) {
            node->person.display();
        }
        else {
            cout << "Person not found." << endl;
        }
    }

    void deleteNode(const string name) {
        root = deleteNode(root, name);
    }

    void dispAll() const {
        if (!root) {
            cout << "Phone book is empty." << endl;
        }
        else {
            inorder(root);
        }
    }
};


void displayMenu() {
    cout << endl << "Phone Book Menu: " << endl;
    cout << "1. Add a new entry" << endl;
    cout << "2. Find phones by name" << endl;
    cout << "3. Remove an entry by name" << endl;
    cout << "4. Print all entries" << endl;
    cout << "5. Exit" << endl;
    cout << "Choose an option: ";
}

int qazmain() {
    PhoneBook phoneBook;
    int choice;
    string name, phone;

    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            cout << "Enter name: ";
            getline(cin, name);
            cout << "Enter phone: ";
            getline(cin, phone);
            phoneBook.add(name, phone);
            break;
        case 2:
            cout << "Enter name to search: ";
            getline(cin, name);
            phoneBook.find(name);
            break;
        case 3:
            cout << "Enter name to remove: ";
            getline(cin, name);
            phoneBook.deleteNode(name);
            break;
        case 4:
            phoneBook.dispAll();
            break;
        case 5:
            cout << "Exiting." << endl;
            return 0;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}