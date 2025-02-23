#include <iostream>

// Структура узла дерева отрезков
struct Node {
    int l, r; // Интервал [l, r]
    Node* left;
    Node* right;

    Node(int l, int r) : l(l), r(r), left(nullptr), right(nullptr) {}
};

// Класс для работы с деревом отрезков
class SegmentTree {
private:
    Node* root;

    // Рекурсивное построение дерева отрезков
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

    // Прямой обход дерева (preorder traversal)
    void preorderTraversal(Node* node) {
        if (!node) return;

        std::cout << "[" << node->l << ", " << node->r << "] ";
        preorderTraversal(node->left);
        preorderTraversal(node->right);
    }

    // Подсчёт количества интервалов, содержащих точку X
    int countIntervalsContainingX(Node* node, int X) {
        if (!node) return 0;

        // Если текущий интервал не содержит X, возвращаем 0
        if (X < node->l || X > node->r) {
            return 0;
        }

        // Если текущий интервал содержит X, добавляем 1 и проверяем детей
        return 1 + countIntervalsContainingX(node->left, X) + countIntervalsContainingX(node->right, X);
    }

public:
    // Конструктор
    SegmentTree(int l, int r) {
        root = buildTree(l, r);
    }

    // Деструктор (рекурсивное удаление дерева)
    ~SegmentTree() {
        deleteTree(root);
    }

    // Рекурсивное удаление дерева
    void deleteTree(Node* node) {
        if (!node) return;

        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

    // Прямой обход и печать интервалов
    void printTree() {
        std::cout << "Preorder traversal of the segment tree:\n";
        preorderTraversal(root);
        std::cout << "\n";
    }

    // Подсчёт количества интервалов, содержащих точку X
    int countIntervals(int X) {
        return countIntervalsContainingX(root, X);
    }
};

int main() {
    int l, r;
    std::cout << "Enter the range for the segment tree [l, r]: ";
    std::cin >> l >> r;

    // Создание дерева отрезков
    SegmentTree tree(l, r);

    // Прямой обход и печать интервалов
    tree.printTree();

    // Подсчёт количества интервалов, содержащих точку X
    int X;
    std::cout << "Enter a point X to count intervals containing it: ";
    std::cin >> X;

    int count = tree.countIntervals(X);
    std::cout << "Number of intervals containing " << X << ": " << count << "\n";

    return 0;
}