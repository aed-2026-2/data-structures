#include<iostream>
#include<algorithm>
using namespace std; 

class AVLTree {
private: 
    struct Node {
        int data; 
        Node* left; 
        Node* right; 
        int height;
        Node(int value) : data(value), left(nullptr), right(nullptr), height(1) {}
    }; 
    Node* root; 
    
    Node* minValueNode(Node* node) {
        Node* current = node; 
        while (current->left != nullptr) {
            current = current->left; 
        }
        return current; 
    }
    
    Node* removeRecursive(Node* node, int data) { 
        if (node == nullptr) {
            return node;
        }

        if (data < node->data) {
            node->left = removeRecursive(node->left, data); 
        } else if (data > node->data) {
            node->right = removeRecursive(node->right, data); 
        } else {
            if ((node->left == nullptr) || (node->right == nullptr)) {
                Node* temp = node->left? node->left : node->right; 

                if (temp == nullptr) {
                    temp = node; 
                    node = nullptr; 
                } else {
                    Node* toRemove = node; 
                    node = temp; 
                    temp = toRemove; 
                }
                delete temp; 
            } else {
                Node* temp = minValueNode(node->right); 
                node->data = temp->data; 
                node->right = removeRecursive(node->right, temp->data); 
            }

        }

        if (node == nullptr) {
            return node; 
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right)); 
        int balance = getBalance(node); 

        if (balance > 1 && getBalance(node->left) >= 0) {
            return rightRotate(node);
        }
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(node->left); 
            return rightRotate(node); 
        }
        if (balance < -1 && getBalance(node->right) <= 0) {
            return leftRotate(node); 
        }
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(node->right); 
            return leftRotate(node); 
        }

        return node; 
    }


    Node* insertRecursive(Node* node, int data) {
        if (node == nullptr) {
            return new Node(data); 
        }

        if (data < node->data) {
            node->left = insertRecursive(node->left, data); 
        } else if (data > node->data) {
            node->right = insertRecursive(node->right, data); 
        } else {
            return node; 
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right)); 

        int balance = getBalance(node); 
    
        if (balance > 1 && data < node->left->data) {
            return rightRotate(node); 
        }

        if (balance > 1 && data > node->left->data) {
            node->left = leftRotate(node->left);  
            return rightRotate(node); 
        }

        if (balance < -1 && data > node->right->data) {
            return leftRotate(node); 
        }

        if (balance < -1 && data < node->right->data) {
            node->right = rightRotate(node->right); 
            return leftRotate(node); 
        }
        
        return node; 
    }

    Node* searchRecursive(Node* node, int data) {
        if (node == nullptr || node->data == data) {
            return node; 
        }
        if (data < node->data) {
            return searchRecursive(node->left, data); 
        } else {
            return searchRecursive(node->right, data); 
        }
    }; 

    int getHeight(Node* node) {
        if (node == nullptr) {
            return 0; 
        }
        return node->height;  
    }

    int getBalance(Node* node) {
        if (node == nullptr) 
            return 0; 
        return getHeight(node->left) - getHeight(node->right); 
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right; 

        x->right = y; 
        y->left = T2; 

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1; 
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1; 

        return x; 
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right; 
        Node* T2 = y->left; 

        y->left = x; 
        x->right = T2; 

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1; 
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1; 

        return y; 
    }

public: 
    AVLTree() {
        root = nullptr; 
    }

    void insert(int data) {
        root = insertRecursive(root, data); 
    }
    
    void remove(int data) {
        root = removeRecursive(root, data); 
    }

/*
    bool search(int data) {
        return searchRecursive(root, data) != nullptr;   
    }
*/
    bool search(int data) {
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
    
    cout << "hola como vas" << endl; 
    return 0; 
}

