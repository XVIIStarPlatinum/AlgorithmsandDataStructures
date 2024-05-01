#include <ctime>
#include <iostream>
#include <random>

int randomGenerator(size_t min, size_t max) {
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
    return dist(rng);
}
struct Node {
    int data;
    int priority;
    Node *left, *right;
    explicit Node(int d) {
        data = d;
        priority = (int) randomGenerator(1, 100);
        left = nullptr;
        right = nullptr;
    }
};
class CartesianTree {

public:
    static void rotateLeft(Node *&root) {
        Node *Right = root->right;
        Node *Key = root->right->left;
        Right->left = root;
        root->right = Key;
        root = Right;
    }
    static void rotateRight(Node *&root) {
        Node *Left = root->left;
        Node *Priority = root->left->right;
        Left->right = root;
        root->left = Priority;
        root = Left;
    }
    void insertNode(Node *&root, int d) {
        if (root == nullptr) {
            root = new Node(d);
        }
        else {
            if (d < root->data) {
                insertNode(root->left, d);
                if (root->left && root->left->priority > root->priority) {
                    rotateRight(root);
                }
            } else {
                insertNode(root->right, d);
                if (root->right && root->right->priority > root->priority) {
                    rotateLeft(root);
                }
            }
        }
    }
    bool searchNode(Node *root, int key) {
        if (root == nullptr) {
            return false;
        }
        if (root->data == key) {
            return true;
        }
        if (key < root->data) {
            return searchNode(root->left, key);
        }
        return searchNode(root->right, key);
    }
    void deleteNode(Node *&root, int key) {
        if (root == nullptr) {
            return;
        }
        if (key < root->data) {
            deleteNode(root->left, key);
        } else if (key > root->data) {
            deleteNode(root->right, key);
        } else {
            if (root->left == nullptr && root->right == nullptr) {
                delete root;
                root = nullptr;
            } else if (root->left && root->right) {
                if (root->left->priority < root->right->priority) {
                    rotateLeft(root);
                    deleteNode(root->left, key);
                } else {
                    rotateRight(root);
                    deleteNode(root->right, key);
                }
            } else {
                Node *child = (root->left) ? root->left : root->right;
                Node *curr = root;
                root = child;
                delete curr;
            }
        }
    }
    void displayTreap(Node *root, int space = 0, int height = 10) {
        if (root != nullptr) {
            space += height;
            displayTreap(root->left, space);
            //    std::cout << "\n";
            //    for (int i = height; i < space; i++) {
            //        std::cout << ' ';
            //    }
            std::cout << root->data << "(" << root->priority << ")\n";
            //    std::cout << "\n";
            displayTreap(root->right, space);
        }
    }
};
int main() {
    int nums[] = {1, 7, 6, 4, 3, 2, 8, 9, 10};
    Node *root = nullptr;
    CartesianTree cartesianTree;
    for (int n: nums) {
        cartesianTree.insertNode(root, n);
    }
    std::cout << "Построенная дуча:\n\n";
    cartesianTree.displayTreap(root);
    std::cout << "\nДобавление узла 5:\n\n";
    cartesianTree.insertNode(root, 5);
    cartesianTree.displayTreap(root);
    std::cout << "\nУдаление узла 8:\n\n";
    cartesianTree.deleteNode(root, 8);
    cartesianTree.displayTreap(root);
    std::cout << "\nУдаление узла 3:\n\n";
    cartesianTree.deleteNode(root, 3);
    cartesianTree.displayTreap(root);
    std::cout << "\nПоиск всех узлов с 1 до 10:\n\n";
    for (int i = 1; i <= 10; i++) {
        std::cout << i << ": ";
        (cartesianTree.searchNode(root, i)) ? std::cout << "есть" << "\n" : std::cout << "нет" << "\n";
    }
    return 0;
}
