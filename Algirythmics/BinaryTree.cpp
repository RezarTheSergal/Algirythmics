#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(int value) : data(value) {}
};

class AVLTree {
private:
    Node* root = nullptr;

    void clear(Node* node) {
        if (!node) return;

        clear(node->left);
        clear(node->right);
        delete node;
    }

    Node* insert(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }
        if (value < node->data) {
            node->left = insert(node->left, value);
        }
        else if (value > node->data) {
            node->right = insert(node->right, value);
        }
        return node;
    }

    void inorderTraversal(Node* node) {
        if (node != nullptr) {
            inorderTraversal(node->left);
            cout << node->data << " ";
            inorderTraversal(node->right);
        }
    }

    int height(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        return max(leftHeight, rightHeight) + 1;
    }

    Node* search(Node* node, int value) {
        if (node == nullptr || node->data == value) {
            return node;
        }
        if (value < node->data) {
            return search(node->left, value);
        }
        return search(node->right, value);
    }

    Node* deleteNode(Node* node, int value) {
        if (node == nullptr) {
            return node;
        }
        if (value < node->data) {
            node->left = deleteNode(node->left, value);
        }
        else if (value > node->data) {
            node->right = deleteNode(node->right, value);
        }
        else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }
        return node;
    }

    Node* findMin(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

public:
    ~AVLTree() {
        clear(root);
    }

    void insert(int value) {
        root = insert(root, value);
    }

    // ������������ �����
    void inorderTraversal() {
        inorderTraversal(root);
        cout << endl;
    }

    int height() {
        return height(root);
    }

    bool search(int value) {
        return search(root, value) != nullptr;
    }

    void deleteNode(int value) {
        root = deleteNode(root, value);
    }
};

int gfhdsadsmain() {
    srand(time(0));
    AVLTree* bst = new AVLTree();

    int n;
    cout << "Enter number of tree's elements: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int value = rand() % 100 + 1;
        bst->insert(value);
    }

    cout << "Inorder Traversal: ";
    bst->inorderTraversal();

    cout << "Tree Height: " << bst->height() << endl;

    int valueToSearch;
    cout << "Enter element to find: ";
    cin >> valueToSearch;
    if (bst->search(valueToSearch)) {
        cout << "Found!" << endl;
    }
    else {
        cout << "Not Found :<" << endl;
    }

    int valueToDelete;
    cout << "Enter elem to destroy: ";
    cin >> valueToDelete;
    bst->deleteNode(valueToDelete);
    cout << "Inorder Traversal after deletion: ";
    bst->inorderTraversal();

    delete bst;
    return 0;
}