#include <iostream>

struct Node {
    int data;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent;
    int balanceFactor;

    Node(int value, int bf = 0, Node* p = nullptr)
        : data(value), balanceFactor(bf), parent(p)
    {}
};

class BinarySearchTree {
private:
    Node* root = nullptr;



    void clear(Node* node) {
        if (!node) return;

        clear(node->left);
        clear(node->right);
        delete node;
    }

    Node* insert(Node* node, int value, Node* parent = nullptr) {
        if (node == nullptr) {
            Node* temp = new Node(value, 0, parent);
            return temp;
        }
        if (value < node->data) {
            node->left = insert(node->left, value, node);
            node->left->balanceFactor = height(node->left->left) - height(node->left->right);
        }
        else if (value > node->data) {
            node->right = insert(node->right, value, node);
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
        return std::max(leftHeight, rightHeight);
    }

    int balanceFactor(Node* node)
    {
        if (node == nullptr) {
            return 0;
        }
        return height(node->left) - height(node->right);
    }

    void balanceTree(Node* node) 
    {
        if (node == nullptr) {
            return;
        }
        balanceTree(node->left);
    }

    void rightRotation(Node* node, bool lr = false)
    {
        if (!lr) node->parent->left = node->left;
        else node->parent->right = node->left;

        Node* temp = node->left->right;
        node->left->right = node;
        node->left = temp;
    }

    void leftRotation(Node* node, bool lr = false)
    {
        if (!lr) node->parent->left = node->right;
        else node->parent->right = node->right;

        Node* temp = node->right->left;
        node->right->left = node;
        node->right = temp;
    }

public:
    ~BinarySearchTree() {
        clear(root);
    }

    void insert(int value) {
        root = insert(root, value);
        balanceTree(nullptr);
    }

    // Симметричный обход
    void inorderTraversal() {
        inorderTraversal(root);
        std::cout << std::endl;
    }

};

int main() {
    BinarySearchTree* bst = new BinarySearchTree();

    bst->insert(3);
    bst->insert(2);
    bst->insert(4);
    bst->insert(1);
    bst->insert(5);

    std::cout << "Inorder Traversal 1: ";
    bst->inorderTraversal();

    delete bst;
    bst = new BinarySearchTree();

    bst->insert(1);
    bst->insert(2);
    bst->insert(3);
    bst->insert(4);
    bst->insert(5);

    std::cout << "Inorder Traversal 2: ";
    bst->inorderTraversal();
}