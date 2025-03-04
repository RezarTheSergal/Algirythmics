#include <iostream>

using namespace std;

struct Node {
    int l, r;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(int l, int r) : l(l), r(r) {}
};

class SegmentTree {
private:
    Node* root;

    Node* buildTree(int l, int r) {
        if (l > r) return nullptr;

        Node* node = new Node(l, r);

        if (r-l > 1) {
            int mid = (l + r) / 2;
            node->left = buildTree(l, mid);
            node->right = buildTree(mid, r);
        }

        return node;
    }

    void inorder(Node* node) {
        if (!node) return;

        inorder(node->left);
        cout << "[" << node->l << ", " << node->r << "] ";
        inorder(node->right);
    }

    int countIntervalsContainingX(Node* node, int x) {
        if (!node) return 0;

        if (x < node->l || x > node->r) {
            return 0;
        }

        return 1 + countIntervalsContainingX(node->left, x) + countIntervalsContainingX(node->right, x);
    }

    void clear(Node* node) {
        if (!node) return;

        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    SegmentTree(int l, int r) {
        root = buildTree(l, r);
    }

    ~SegmentTree() {
        clear(root);
    }

    void inorderTraversal() {
        inorder(root);
        cout << endl;
    }

    int countIntervals(int x) {
        return countIntervalsContainingX(root, x);
    }
};

int dfghmain() {
    int l, r, x, count;
    cout << "Enter the range for the segment tree: ";
    cin >> l >> r;

    SegmentTree* tree = new SegmentTree(l, r);

    tree->inorderTraversal();
    cout << "Enter a point X to count intervals containing it: ";
    cin >> x;

    count = tree->countIntervals(x);
    cout << "Number of intervals containing " << x << ": " << count << endl;

    return 0;
}