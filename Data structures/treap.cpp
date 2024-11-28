#include <ctime>
#include <iostream>
#include <random>

int randomGenerator(std::mt19937 &rng, size_t min, size_t max) {
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
    return dist(rng);
}

struct Node {
    int data;
    int priority;
    Node *left, *right;
    explicit Node(int d, int p) : data(d), priority(p) {
        left = nullptr;
        right = nullptr;
    }
};

class CartesianTree {
    Node *root;
public:
    // Default constructor
    CartesianTree(){
        root = nullptr;
    };
    // Alternative constructor
    explicit CartesianTree(Node *&root) : root(root) {}
    // Destructor
    ~CartesianTree() {
        delete root;
    }
    // Copy constructor
    CartesianTree(const CartesianTree& other) : root(other.root){
        std::copy(other.root, other.root, root);
    }
    // Copy assignment constructor
    CartesianTree& operator=(const CartesianTree& other) {
        if(this != &other) {
            delete root;
            root = new Node(other.root->data, other.root->priority);
        }
        return *this;
    }
    // Move constructor
    CartesianTree(CartesianTree&& other) noexcept : root(other.root){
        other.root = nullptr;
    }
    // Move assignment constructor
    CartesianTree& operator=(CartesianTree&& other) {
        if(this != &other) {
            delete root;
            root = other.root;
        }
        return *this;
    }

    void rotateLeft() {
        Node *r = root->right;
        Node *Key = root->right->left;
        r->left = root;
        root->right = Key;
        root = r;
    }
    void rotateRight() {
        Node *l = root->left;
        Node *Priority = root->left->right;
        l->right = root;
        root->left = Priority;
        root = l;
    }
    void insertNode(int d, int p) {
        if (!root) {
            root = new Node{d, p};
        }
        else {
            if (d < root->data) {
                insertNode(d, p);
                if (root->left && root->left->priority > root->priority) {
                    rotateRight();
                }
            } else {
                insertNode(d, p);
                if (root->right && root->right->priority > root->priority) {
                    rotateLeft();
                }
            }
        }
    }
    bool searchNode(int key) {
        if (!root) {
            return false;
        }
        if (root->data == key) {
            return true;
        }
        if (key < root->data) {
            return searchNode(key);
        }
        return searchNode(key);
    }
    void deleteNode(int key) {
        if (!root) {
            return;
        }
        if (key < root->data) {
            deleteNode(key);
        } else if (key > root->data) {
            deleteNode(key);
        } else {
            if (root->left == nullptr && root->right == nullptr) {
                delete root;
                root = nullptr;
            } else if (root->left && root->right) {
                if (root->left->priority < root->right->priority) {
                    rotateLeft();
                    deleteNode(key);
                } else {
                    rotateRight();
                    deleteNode(key);
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
    std::random_device dev;
    std::mt19937 rng(dev());
    Node *root = nullptr;
    CartesianTree cartesianTree;
    for (int n: nums) {
        cartesianTree.insertNode(n, randomGenerator(rng, 1, 100));
    }
    std::cout << "Построенная дуча:\n\n";
    cartesianTree.displayTreap(root);
    std::cout << "\nДобавление узла 5:\n\n";
    cartesianTree.insertNode(5, randomGenerator(rng, 1, 100));
    cartesianTree.displayTreap(root);
    std::cout << "\nУдаление узла 8:\n\n";
    cartesianTree.deleteNode(8);
    cartesianTree.displayTreap(root);
    std::cout << "\nУдаление узла 3:\n\n";
    cartesianTree.deleteNode(3);
    cartesianTree.displayTreap(root);
    std::cout << "\nПоиск всех узлов с 1 до 10:\n\n";
    for (int i = 1; i <= 10; i++) {
        std::cout << i << ": ";
        (cartesianTree.searchNode(i)) ? std::cout << "есть" << "\n" : std::cout << "нет" << "\n";
    }
    return 0;
}
