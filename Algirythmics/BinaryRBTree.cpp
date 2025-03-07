#include <iostream>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(int value) : data(value), color(RED) {} // �� ��������� ���� �������
};

class BST {
private:
    Node* root = nullptr;

    void clear(Node* node) {
        if (!node) return;

        exit(0);
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
            cout << node->data << "(" << (node->color == RED ? "RED" : "BLACK") << ") ";
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

    // ����������� ������� ��� ��������� �������� ������
    void colorTreeByLevels(Node* node, int level) {
        if (node == nullptr) return;

        // ������� 1 (������) � ������, ������� 2 � �������, ������� 3 � ������ � �.�.
        node->color = (level % 2 != 0) ? BLACK : RED;

        // ���������� ������ ����� � ������ ����������
        colorTreeByLevels(node->left, level++);
        colorTreeByLevels(node->right, level++);
    }

    // �������� ������� ������-������� ������
    bool isRedBlackTree(Node* root) {
        if (root == nullptr) return true;

        // �������� 2: ������ ������ ���� ������
        if (this->root->color != BLACK) {
            cout << "Violation: Root is not black!" << endl;
            return false;
        }

        // �������� 4: ���� ���� �������, ��� ��� ������� ������ ���� �������
        if (root->color == RED &&
            ((root->left && root->left->color == RED) ||
                (root->right && root->right->color == RED))) {
            cout << "Violation: Red node has red children!" << endl;
            return false;
        }

        // ����������� �������� ��� ������ � ������� �����������
        return isRedBlackTree(root->left) && isRedBlackTree(root->right);
    }

public:
    ~BST() {
        clear(root);
    }

    void insert(int value) {
        root = insert(root, value);
    }

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

    // �������� ������ �� �������
    void colorTree() {
        colorTreeByLevels(root, 1); // �������� � ������ 1 (������)
    }

    // �������� ������� ������-������� ������
    bool checkRedBlackProperties() {
        return isRedBlackTree(root);
    }
};

int main() {
    srand(time(0));
    BST* bst = new BST();

    int n;
    cout << "Enter number of tree's elements: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int value = rand() % 100 + 1;
        cout << value << " ";
        bst->insert(value);
    }

    // �������� ������ �� �������
    bst->colorTree();

    cout << "\nInorder Traversal (after coloring): ";
    bst->inorderTraversal();

    // �������� ������� ������-������� ������
    if (bst->checkRedBlackProperties()) {
        cout << "The tree satisfies Red-Black tree properties." << endl;
    }
    else {
        cout << "The tree does not satisfy Red-Black tree properties." << endl;
    }

    delete bst;
    return 0;
}