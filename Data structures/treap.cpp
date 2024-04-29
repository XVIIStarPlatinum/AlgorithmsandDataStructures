#include <cstdlib>
#include <ctime>
#include <iostream>

struct Node {
    int data;
    int priority;
    Node *l, *r;
    Node(int d) {
        this->data = d;
        this->priority = rand() % 100;
        this->l = this->r = nullptr;
    }
};
void rotateLeft(Node *&root) {
    Node *R = root->r;
    Node *X = root->r->l;
    R->l = root;
    root->r = X;
    root = R;
}
void rotateRight(Node *&root) {
    Node *L = root->l;
    Node *Y = root->l->r;
    L->r = root;
    root->l = Y;
    root = L;
}
void insertNode(Node *&root, int d) {
    if (root == nullptr) {
        root = new Node(d);
        return;
    }
    if (d < root->data) {
        insertNode(root->l, d);
        if (root->l != nullptr && root->l->priority > root->priority) {
            rotateRight(root);
        }
    } else {
        insertNode(root->r, d);
        if (root->r != nullptr && root->r->priority > root->priority) {
            rotateLeft(root);
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
        return searchNode(root->l, key);
    }
    return searchNode(root->r, key);
}
void deleteNode(Node *&root, int key) {
    if (root == nullptr) {
        return;
    }
    if (key < root->data) {
        deleteNode(root->l, key);
    } else if (key > root->data) {
        deleteNode(root->r, key);
    } else {
        if (root->l == nullptr && root->r == nullptr) {
            delete root;
            root = nullptr;
        } else if (root->l && root->r) {
            if (root->l->priority < root->r->priority) {
                rotateLeft(root);
                deleteNode(root->l, key);
            } else {
                rotateRight(root);
                deleteNode(root->r, key);
            }
        } else {
            Node *child = (root->l) ? root->l : root->r;
            Node *curr = root;
            root = child;
            delete curr;
        }
    }
}
void displayTreap(Node *root, int space = 0, int height = 10) {
    if (root == nullptr) return;
    space += height;
    displayTreap(root->l, space);
    //    std::cout << "\n";
    //    for (int i = height; i < space; i++) {
    //        std::cout << ' ';
    //    }
    std::cout << root->data << "(" << root->priority << ")\n";
    //    std::cout << "\n";
    displayTreap(root->r, space);
}
int main() {
    int nums[] = {1, 7, 6, 4, 3, 2, 8, 9, 10};
    Node *root = nullptr;
    srand(time(nullptr));
    for (int n: nums) {
        insertNode(root, n);
    }
    std::cout << "Построенная дуча:\n\n";
    displayTreap(root);
    std::cout << "\nДобавление узла 5:\n\n";
    insertNode(root, 5);
    displayTreap(root);
    std::cout << "\nУдаление узла 8:\n\n";
    deleteNode(root, 8);
    displayTreap(root);
    std::cout << "\nУдаление узла 3:\n\n";
    deleteNode(root, 3);
    displayTreap(root);
    std::cout << "\nПоиск всех узлов с 1 до 10:\n\n";
    for (int i = 1; i <= 10; i++) {
        std::cout << i << ": ";
        (searchNode(root, i)) ? std::cout << "есть" << "\n" : std::cout << "нет" << "\n";
    }
    return 0;
}