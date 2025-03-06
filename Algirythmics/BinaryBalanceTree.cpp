#include <iostream>

struct Node {
    int data;
    Node* left = nullptr;
    Node* right = nullptr;
    int balanceFactor = 0;

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
            Node* temp = new Node(value);
            temp->balanceFactor = 0;
            return temp;
        }
        if (value < node->data) {
            node->left = insert(node->left, value);
            node->left->balanceFactor = height(node->left->left) - height(node->left->right);
        }
        else if (value > node->data) {
            node->right = insert(node->right, value);
            node->right->balanceFactor = height(node->right->left) - height(node->right->right);
        }
        return node;
    }

    void inorderTraversal(Node* node) {
        if (node != nullptr) {
            inorderTraversal(node->left);
            std::cout << node->data << "(" << node->balanceFactor << ") ";
            inorderTraversal(node->right);
        }
    }

    int height(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        return std::max(leftHeight, rightHeight) ;
    }

public:
    ~AVLTree() {
        clear(root);
    }

    void insert(int value) {
        root = insert(root, value);
    }

    // Симметричный обход
    void inorderTraversal() {
        inorderTraversal(root);
        std::cout << std::endl;
    }

    int height() {
        return height(root);
    }

};

int fghjmain() {
    AVLTree* bst = new AVLTree();

    bst->insert(3);
    bst->insert(2);
    bst->insert(4);
    bst->insert(1);
    bst->insert(5);

    std::cout << "Inorder Traversal 1: ";
    bst->inorderTraversal();

    delete bst;
    bst = new AVLTree();
    
    bst->insert(1);
    bst->insert(2);
    bst->insert(3);
    bst->insert(4);
    bst->insert(5);

    std::cout << "Inorder Traversal 2: ";
    bst->inorderTraversal();
    return 0;
}