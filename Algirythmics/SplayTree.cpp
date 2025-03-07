#include <iostream>

using namespace std;

class SplayTree
{
public:
    SplayTree() : root(nullptr) {}
    ~SplayTree() { deleteTree(root); }

    void displayTree() 
    {
        preorder(root);
        cout << endl;
    }

    void insert(int value) 
    {
        root = insert(root, value);
    }

    void deleteNode(int key)
    {
        root = deleteNode(root, key);
    }

protected:
    struct Node {
        int key;
        Node* left;
        Node* right;

        Node(int key) 
            : key(key), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void preorder(Node* node) {
        if (node != nullptr) {
            cout << node->key << " ";
            preorder(node->left);
            preorder(node->right);
        }
    }

    void deleteTree(Node* node)
    {
        if (node != nullptr) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

    Node* searchTreeHelper(Node* node, int key) {
        if (node == nullptr || key == node->key) {
            return node;
        }

        if (key < node->key) {
            return searchTreeHelper(node->left, key);
        }
        return searchTreeHelper(node->right, key);
    }

    Node* deleteNode(Node* root, int key) {
        if (root == nullptr)
            return nullptr;

        root = splay(root, key);

        if (root->key != key)
            return root;

        Node* temp;
        if (root->left == nullptr) {
            temp = root;
            root = root->right;
        }
        else {
            temp = root;
            root = splay(root->left, key);
            root->right = temp->right;
        }

        delete temp;
        return root;
    }

    Node* rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }

    Node* splay(Node* root, int key) {
        if (root == nullptr || root->key == key)
            return root;

        if (root->key > key) {
            if (root->left == nullptr)
                return root;
            if (root->left->key > key) {
                root->left->left = splay(root->left->left, key);
                root = rightRotate(root);
            }
            else if (root->left->key < key) {
                root->left->right = splay(root->left->right, key);
                if (root->left->right != nullptr)
                    root->left = leftRotate(root->left);
            }
            return (root->left == nullptr) ? root : rightRotate(root);
        }
        else {
            if (root->right == nullptr)
                return root;
            if (root->right->key > key) {
                root->right->left = splay(root->right->left, key);
                if (root->right->left != nullptr)
                    root->right = rightRotate(root->right);
            }
            else if (root->right->key < key) {
                root->right->right = splay(root->right->right, key);
                root = leftRotate(root);
            }
            return (root->right == nullptr) ? root : leftRotate(root);
        }
    }

    Node* insert(Node* root, int key) {
        if (root == nullptr)
            return new Node(key);

        root = splay(root, key);

        if (root->key == key)
            return root;

        Node* node = new Node(key);
        if (root->key > key) {
            node->right = root;
            node->left = root->left;
            root->left = nullptr;
        }
        else {
            node->left = root;
            node->right = root->right;
            root->right = nullptr;
        }
        return node;
    }

};


int dghjdsdmain() {
    SplayTree* sp = new SplayTree();
    sp->insert(100);
    sp->displayTree();
    sp->insert(50);
    sp->displayTree();
    sp->insert(200);
    sp->displayTree();
    sp->insert(40);
    sp->displayTree();
    sp->insert(60);
    sp->displayTree();

    cout << "Deleting node 50" << endl;
    sp->deleteNode(50);
    sp->displayTree();

    cout << "Deleting node 200" << endl;
    sp->deleteNode(200);
    sp->displayTree();
    return 0;
}
