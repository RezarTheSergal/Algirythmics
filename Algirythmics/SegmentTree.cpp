#include <iostream>

// ��������� ���� ������ ��������
struct Node {
    int l, r; // �������� [l, r]
    Node* left;
    Node* right;

    Node(int l, int r) : l(l), r(r), left(nullptr), right(nullptr) {}
};

// ����� ��� ������ � ������� ��������
class SegmentTree {
private:
    Node* root;

    // ����������� ���������� ������ ��������
    Node* buildTree(int l, int r) {
        if (l > r) return nullptr;

        Node* node = new Node(l, r);

        if (l != r) {
            int mid = (l + r) / 2;
            node->left = buildTree(l, mid);
            node->right = buildTree(mid + 1, r);
        }

        return node;
    }

    // ������ ����� ������ (preorder traversal)
    void preorderTraversal(Node* node) {
        if (!node) return;

        std::cout << "[" << node->l << ", " << node->r << "] ";
        preorderTraversal(node->left);
        preorderTraversal(node->right);
    }

    // ������� ���������� ����������, ���������� ����� X
    int countIntervalsContainingX(Node* node, int X) {
        if (!node) return 0;

        // ���� ������� �������� �� �������� X, ���������� 0
        if (X < node->l || X > node->r) {
            return 0;
        }

        // ���� ������� �������� �������� X, ��������� 1 � ��������� �����
        return 1 + countIntervalsContainingX(node->left, X) + countIntervalsContainingX(node->right, X);
    }

public:
    // �����������
    SegmentTree(int l, int r) {
        root = buildTree(l, r);
    }

    // ���������� (����������� �������� ������)
    ~SegmentTree() {
        deleteTree(root);
    }

    // ����������� �������� ������
    void deleteTree(Node* node) {
        if (!node) return;

        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

    // ������ ����� � ������ ����������
    void printTree() {
        std::cout << "Preorder traversal of the segment tree:\n";
        preorderTraversal(root);
        std::cout << "\n";
    }

    // ������� ���������� ����������, ���������� ����� X
    int countIntervals(int X) {
        return countIntervalsContainingX(root, X);
    }
};

int main() {
    int l, r;
    std::cout << "Enter the range for the segment tree [l, r]: ";
    std::cin >> l >> r;

    // �������� ������ ��������
    SegmentTree tree(l, r);

    // ������ ����� � ������ ����������
    tree.printTree();

    // ������� ���������� ����������, ���������� ����� X
    int X;
    std::cout << "Enter a point X to count intervals containing it: ";
    std::cin >> X;

    int count = tree.countIntervals(X);
    std::cout << "Number of intervals containing " << X << ": " << count << "\n";

    return 0;
}