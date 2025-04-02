#include <iostream>
using namespace std;

struct TreeNode {
    int value;
    TreeNode *parent, *left, *right;
    bool color; // RED = true, BLACK = false
};

class RBTree {
private:
    TreeNode *root;

    void rotateLeft(TreeNode *node) {
        TreeNode *rightChild = node->right;
        node->right = rightChild->left;
        if (rightChild->left != nullptr) {
            rightChild->left->parent = node;
        }
        rightChild->parent = node->parent;
        if (node->parent == nullptr) {
            root = rightChild;
        } else if (node == node->parent->left) {
            node->parent->left = rightChild;
        } else {
            node->parent->right = rightChild;
        }
        rightChild->left = node;
        node->parent = rightChild;
    }

    void rotateRight(TreeNode *node) {
        TreeNode *leftChild = node->left;
        node->left = leftChild->right;
        if (leftChild->right != nullptr) {
            leftChild->right->parent = node;
        }
        leftChild->parent = node->parent;
        if (node->parent == nullptr) {
            root = leftChild;
        } else if (node == node->parent->right) {
            node->parent->right = leftChild;
        } else {
            node->parent->left = leftChild;
        }
        leftChild->right = node;
        node->parent = leftChild;
    }

    void fixInsertion(TreeNode *node) {
        TreeNode *uncle;
        while (node->parent != nullptr && node->parent->color == true) {
            if (node->parent == node->parent->parent->left) {
                uncle = node->parent->parent->right;
                if (uncle != nullptr && uncle->color == true) {
                    node->parent->color = false;
                    uncle->color = false;
                    node->parent->parent->color = true;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        rotateLeft(node);
                    }
                    node->parent->color = false;
                    node->parent->parent->color = true;
                    rotateRight(node->parent->parent);
                }
            } else {
                uncle = node->parent->parent->left;
                if (uncle != nullptr && uncle->color == true) {
                    node->parent->color = false;
                    uncle->color = false;
                    node->parent->parent->color = true;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rotateRight(node);
                    }
                    node->parent->color = false;
                    node->parent->parent->color = true;
                    rotateLeft(node->parent->parent);
                }
            }
        }
        root->color = false;
    }

public:
    RBTree() {
        root = nullptr;
    }

    void insert(int key) {
        TreeNode *newNode = new TreeNode;
        newNode->value = key;
        newNode->parent = nullptr;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->color = true;

        TreeNode *temp = nullptr;
        TreeNode *current = root;

        while (current != nullptr) {
            temp = current;
            if (newNode->value < current->value) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        newNode->parent = temp;
        if (temp == nullptr) {
            root = newNode;
        } else if (newNode->value < temp->value) {
            temp->left = newNode;
        } else {
            temp->right = newNode;
        }

        if (newNode->parent == nullptr) {
            newNode->color = false;
            return;
        }
        if (newNode->parent->parent == nullptr) {
            return;
        }
        fixInsertion(newNode);
    }

    void inorderTraversal(TreeNode *node) {
        if (node != nullptr) {
            inorderTraversal(node->left);
            cout << node->value << " ";
            inorderTraversal(node->right);
        }
    }

    void displayInOrder() {
        inorderTraversal(root);
        cout << endl;
    }

    void menu() {
        int choice, value;
        while (true) {
            cout << "\nRed-Black Tree Operations Menu:\n";
            cout << "1. Insert Node\n";
            cout << "2. Display In-order Traversal\n";
            cout << "3. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    cout << "Enter value to insert: ";
                    cin >> value;
                    insert(value);
                    break;
                case 2:
                    cout << "In-order Traversal: ";
                    displayInOrder();
                    break;
                case 3:
                    cout << "Exiting...\n";
                    return;
                default:
                    cout << "Invalid choice, please try again.\n";
            }
        }
    }
};

int main() {
    RBTree rbTree;
    rbTree.menu();
    return 0;
}

