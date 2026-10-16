#include <iostream>
#include <algorithm>
using namespace std; 

using namespace std;

enum Color { RED, BLACK };

class RedBlackTree {
private:
    struct Node {
        int data;
        Color color;
        Node* left;
        Node* right;
        Node* parent;

        Node(int value) 
            : data(value), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root;

    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;

        if (y->left != nullptr) {
            y->left->parent = x;
        }

        y->parent = x->parent;

        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }

        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* y) {
        Node* x = y->left;
        y->left = x->right;

        if (x->right != nullptr) {
            x->right->parent = y;
        }

        x->parent = y->parent;

        if (y->parent == nullptr) {
            root = x;
        } else if (y == y->parent->left) {
            y->parent->left = x;
        } else {
            y->parent->right = x;
        }

        x->right = y;
        y->parent = x;
    }

    void insertFixup(Node* z) {
        while (z->parent != nullptr && z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Node* uncle = z->parent->parent->right;

                if (uncle != nullptr && uncle->color == RED) {
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent; 
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            } else {
                Node* uncle = z->parent->parent->left;

                if (uncle != nullptr && uncle->color == RED) {
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void rbTransplant(Node* u, Node* v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        if (v != nullptr) {
            v->parent = u->parent;
        }
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    void deleteFixup(Node* x, Node* xParent) {
        while (x != root && (x == nullptr || x->color == BLACK)) {
            if (x == (xParent ? xParent->left : nullptr)) {
                Node* w = xParent->right; // Hermano de x

                if (w != nullptr && w->color == RED) {
                    w->color = BLACK;
                    xParent->color = RED;
                    leftRotate(xParent);
                    w = xParent->right;
                }

                if ((w->left == nullptr || w->left->color == BLACK) &&
                    (w->right == nullptr || w->right->color == BLACK)) {
                    w->color = RED;
                    x = xParent;
                    xParent = x->parent;
                } else {
                    if (w->right == nullptr || w->right->color == BLACK) {
                        if (w->left != nullptr) w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = xParent->right;
                    }
                    w->color = xParent->color;
                    xParent->color = BLACK;
                    if (w->right != nullptr) w->right->color = BLACK;
                    leftRotate(xParent);
                    x = root;
                }
            } else { 
                Node* w = xParent->left;

                if (w != nullptr && w->color == RED) {
                    w->color = BLACK;
                    xParent->color = RED;
                    rightRotate(xParent);
                    w = xParent->left;
                }

                if ((w->right == nullptr || w->right->color == BLACK) &&
                    (w->left == nullptr || w->left->color == BLACK)) {
                    w->color = RED;
                    x = xParent;
                    xParent = x->parent;
                } else {
                    if (w->left == nullptr || w->left->color == BLACK) {
                        if (w->right != nullptr) w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = xParent->left;
                    }
                    w->color = xParent->color;
                    xParent->color = BLACK;
                    if (w->left != nullptr) w->left->color = BLACK;
                    rightRotate(xParent);
                    x = root;
                }
            }
        }
        if (x != nullptr) {
            x->color = BLACK;
        }
    }

    void clearRecursive(Node* node) {
        if (node == nullptr) return;
        clearRecursive(node->left);
        clearRecursive(node->right);
        delete node;
    }

public:
    RedBlackTree() : root(nullptr) {}

    ~RedBlackTree() {
        clearRecursive(root);
        root = nullptr;
    }

    void insert(int data) {
        Node* z = new Node(data);
        Node* y = nullptr;
        Node* x = root;

        while (x != nullptr) {
            y = x;
            if (z->data < x->data) {
                x = x->left;
            } else if (z->data > x->data) {
                x = x->right;
            } else {
                delete z;
                return;
            }
        }

        z->parent = y;
        if (y == nullptr) {
            root = z; 
        } else if (z->data < y->data) {
            y->left = z;
        } else {
            y->right = z;
        }

        insertFixup(z);
    }

    void remove(int data) {
        Node* z = root;
        while (z != nullptr && z->data != data) {
            if (data < z->data) z = z->left;
            else z = z->right;
        }

        if (z == nullptr) return; 

        Node* y = z;
        Node* x = nullptr;
        Node* xParent = nullptr;
        Color yOriginalColor = y->color;

        if (z->left == nullptr) {
            x = z->right;
            xParent = z->parent;
            rbTransplant(z, z->right);
        } else if (z->right == nullptr) {
            x = z->left;
            xParent = z->parent;
            rbTransplant(z, z->left);
        } else {
            y = minValueNode(z->right);
            yOriginalColor = y->color;
            x = y->right;

            if (y->parent == z) {
                xParent = y;
            } else {
                xParent = y->parent;
                rbTransplant(y, y->right);
                y->right = z->right;
                if (y->right != nullptr) y->right->parent = y;
            }

            rbTransplant(z, y);
            y->left = z->left;
            if (y->left != nullptr) y->left->parent = y;
            y->color = z->color;
        }

        delete z;

        if (yOriginalColor == BLACK) {
            deleteFixup(x, xParent);
        }
    }

    bool search(int data) const {
        Node* current = root;
        while (current != nullptr) {
            if (data == current->data) return true;
            if (data < current->data) current = current->left;
            else current = current->right;
        }
        return false;
    }
};

int main() {
    RedBlackTree rbTree;

    return 0;
}
