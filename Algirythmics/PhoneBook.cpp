#include <iostream>
#include <string>
#include <vector>

// Структура для хранения информации о человеке
class Person {
public:
    std::string name;
    std::vector<std::string> phones;

    Person(const std::string& n) : name(n) {}

    void addPhone(const std::string& phone) {
        phones.push_back(phone);
    }

    void print() const {
        std::cout << name << ": ";
        for (const auto& phone : phones) {
            std::cout << phone << " ";
        }
        std::cout << "\n";
    }
};

// Узел двоичного дерева поиска
struct TreeNode {
    Person person;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const std::string& name) : person(name), left(nullptr), right(nullptr) {}
};

// Класс для работы с телефонной книгой
class PhoneBook {
private:
    TreeNode* root;

    // Рекурсивное добавление узла
    TreeNode* insert(TreeNode* node, const std::string& name, const std::string& phone) {
        if (!node) {
            TreeNode* newNode = new TreeNode(name);
            newNode->person.addPhone(phone);
            return newNode;
        }

        if (name < node->person.name) {
            node->left = insert(node->left, name, phone);
        }
        else if (name > node->person.name) {
            node->right = insert(node->right, name, phone);
        }
        else {
            // Если имя уже существует, добавляем телефон
            node->person.addPhone(phone);
        }

        return node;
    }

    // Рекурсивный поиск узла по имени
    TreeNode* search(TreeNode* node, const std::string& name) const {
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

    // Рекурсивное удаление узла
    TreeNode* remove(TreeNode* node, const std::string& name) {
        if (!node) return nullptr;

        if (name < node->person.name) {
            node->left = remove(node->left, name);
        }
        else if (name > node->person.name) {
            node->right = remove(node->right, name);
        }
        else {
            // Узел найден
            if (!node->left && !node->right) {
                // Нет детей
                delete node;
                return nullptr;
            }
            else if (!node->left) {
                // Только правый ребёнок
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right) {
                // Только левый ребёнок
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }
            else {
                // Два ребёнка: находим минимальный узел в правом поддереве
                TreeNode* minNode = findMin(node->right);
                node->person = minNode->person;
                node->right = remove(node->right, minNode->person.name);
            }
        }

        return node;
    }

    // Нахождение минимального узла в поддереве
    TreeNode* findMin(TreeNode* node) const {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    // Рекурсивный вывод всех записей в отсортированном порядке
    void inorder(TreeNode* node) const {
        if (!node) return;

        inorder(node->left);
        node->person.print();
        inorder(node->right);
    }

    // Рекурсивное удаление всего дерева
    void clear(TreeNode* node) {
        if (!node) return;

        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    PhoneBook() : root(nullptr) {}

    ~PhoneBook() {
        clear(root);
    }

    // Добавление записи
    void add(const std::string& name, const std::string& phone) {
        root = insert(root, name, phone);
    }

    // Поиск телефонов по имени
    void find(const std::string& name) const {
        TreeNode* node = search(root, name);
        if (node) {
            node->person.print();
        }
        else {
            std::cout << "Person not found.\n";
        }
    }

    // Удаление записи по имени
    void remove(const std::string& name) {
        root = remove(root, name);
    }

    // Вывод всех записей
    void printAll() const {
        if (!root) {
            std::cout << "Phone book is empty.\n";
        }
        else {
            inorder(root);
        }
    }
};

// Основное меню
void displayMenu() {
    std::cout << "\nPhone Book Menu:\n";
    std::cout << "1. Add a new entry\n";
    std::cout << "2. Find phones by name\n";
    std::cout << "3. Remove an entry by name\n";
    std::cout << "4. Print all entries\n";
    std::cout << "5. Exit\n";
    std::cout << "Choose an option: ";
}

int main() {
    PhoneBook phoneBook;
    int choice;
    std::string name, phone;

    while (true) {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore(); // Игнорируем оставшийся символ новой строки

        switch (choice) {
        case 1:
            std::cout << "Enter name: ";
            std::getline(std::cin, name);
            std::cout << "Enter phone: ";
            std::getline(std::cin, phone);
            phoneBook.add(name, phone);
            break;
        case 2:
            std::cout << "Enter name to search: ";
            std::getline(std::cin, name);
            phoneBook.find(name);
            break;
        case 3:
            std::cout << "Enter name to remove: ";
            std::getline(std::cin, name);
            phoneBook.remove(name);
            break;
        case 4:
            phoneBook.printAll();
            break;
        case 5:
            std::cout << "Exiting...\n";
            return 0;
        default:
            std::cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}