#include <iostream>

struct Node {
    int data;
    Node* left = nullptr;
    Node* right = nullptr;
    int balanceFactor;

    Node(int value, int bf = 0, Node* p = nullptr)
        : data(value), balanceFactor(bf)
    {}
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

    Node* insert(Node* node, int& value) {
        if (!node) {
            return new Node(value, 0);
        }
        if (value < node->data) {
            node->left = insert(node->left, value);
        }
        else if (value > node->data) {
            node->right = insert(node->right, value);
        }
        else
        {
            return node;
        }

        node->balanceFactor = balanceFactor(node);
        return balanceTree(node, value);
        
    }

    Node* deleteNode(Node* node, int& value)
    {
        if (!node) return node;

        if (value < node->data)
            node->left = deleteNode(node->left, value);
        else if (value > node->data)
            node->right = deleteNode(node->right, value);
        else {
            if ((!node->left) || (!node->right)) {
                Node* temp = node->left ? node->left : node->right;
                if (!temp) {
                    temp = node;
                    node = nullptr;
                }
                else
                    *node = *temp;
                delete temp;
            }
            else {

                Node* temp = minValueNode(node->right);
                node->data = temp->data;
                node->right = deleteNode(node->right, temp->data);
            }
        }

        if (!node) return node;

        node->balanceFactor = balanceFactor(node);
        return balanceDeletionTree(node);
    }
    
    Node* minValueNode(Node* node)
    {
        Node* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
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
        return std::max(leftHeight, rightHeight) + 1;
    }

    int balanceFactor(Node* node)
    {
        if (node == nullptr) {
            return 0;
        }
        return height(node->left) - height(node->right);
    }

    Node* balanceTree(Node* node, int& value) 
    {
        // Left Left Case
        if (node->balanceFactor > 1 && value < node->left->data)
            return rightRotation(node);

        // Right Right Case
        if (node->balanceFactor < -1 && value > node->right->data)
            return leftRotation(node);

        // Left Right Case
        if (node->balanceFactor > 1 && value > node->left->data) {
            node->left = leftRotation(node->left);
            return rightRotation(node);
        }

        // Right Right Case
        if (node->balanceFactor < -1 && value < node->right->data) {
            node->right = rightRotation(node->right);
            return rightRotation(node);
        }

        return node;
    }

    Node* balanceDeletionTree(Node* node)
    {
        // Left Left Case
        if (node->balanceFactor > 1 && balanceFactor(node->left) >= 0)
            return rightRotation(node);

        // Right Right Case
        if (node->balanceFactor < -1 && balanceFactor(node->right) <= 0)
            return leftRotation(node);

        // Left Right Case
        if (node->balanceFactor > 1 && balanceFactor(node->left) < 0) {
            root->left = leftRotation(node->left);
            return rightRotation(node);
        }

        // Right Left Case
        if (node->balanceFactor < -1
            && balanceFactor(node->right) > 0) {
            root->right = rightRotation(node->right);
            return leftRotation(node);
        }

        return node;
    }

    Node* rightRotation(Node* B)
    {
        Node* A = B->left;
        Node* T2 = A->right;

        A->right = B;
        B->left = T2;

        B->balanceFactor = balanceFactor(B);
        A->balanceFactor = balanceFactor(A);

        return A;

    }

    Node* leftRotation(Node* A)
    {
        Node* B = A->right;
        Node* T2 = B->left;

        B->left = A;
        A->right = T2;

        B->balanceFactor = balanceFactor(B);
        A->balanceFactor = balanceFactor(A);

        return B;
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

    void remove(int value) 
    {
        root = deleteNode(root, value);
    }

};

int sdffhgmain() {
    AVLTree* avl = new AVLTree();

    avl->insert(3);
    avl->insert(2);
    avl->insert(4);
    avl->insert(1);
    avl->insert(5);

    std::cout << "Inorder Traversal 1: ";
    avl->inorderTraversal();

    delete avl;
    avl = new AVLTree();

    avl->insert(1);
    avl->insert(2);
    avl->insert(3);
    avl->insert(4);
    avl->insert(5);
    avl->insert(6);
    avl->insert(7);
    avl->insert(8);
    avl->insert(9);
    avl->insert(10);

    std::cout << "Inorder Traversal 2: ";
    avl->inorderTraversal();

    avl->insert(11);

    avl->remove(5);
    avl->remove(4);

    std::cout << "Inorder Traversal 3: ";
    avl->inorderTraversal();
    return 0;
}