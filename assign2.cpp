#include <iostream>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    int height;

    TreeNode(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

class Tree {
public:
    TreeNode* root;

    // Constructor
    Tree();

    // Insert methods
    void insert(int value);
    void insert(TreeNode*& root, int value);

    // In-order traversal method
    void inOrder(TreeNode* root);

    // AVL Rotation methods
    TreeNode* rightRotate(TreeNode* y);
    TreeNode* leftRotate(TreeNode* x);

    // Get height and balance factor
    int height(TreeNode* node);
    int balanceFactor(TreeNode* node);

    // Method to interact with the tree (Menu-driven)
    void create();
};

Tree::Tree() {
    root = nullptr;
}

// Insert method (public interface)
void Tree::insert(int value) {
    insert(root, value);
}

// Insert method (recursive helper)
void Tree::insert(TreeNode*& root, int value) {
    if (root == nullptr) {
        root = new TreeNode(value);
        return;
    }

    if (value < root->data) {
        insert(root->left, value);
    } else {
        insert(root->right, value);
    }

    // Update height of the ancestor node
    root->height = max(height(root->left), height(root->right)) + 1;

    // Get balance factor
    int balance = balanceFactor(root);

    // Left-Left Case
    if (balance > 1 && value < root->left->data) {
        root = rightRotate(root);
    }

    // Right-Right Case
    else if (balance < -1 && value > root->right->data) {
        root = leftRotate(root);
    }

    // Left-Right Case
    else if (balance > 1 && value > root->left->data) {
        root->left = leftRotate(root->left);
        root = rightRotate(root);
    }

    // Right-Left Case
    else if (balance < -1 && value < root->right->data) {
        root->right = rightRotate(root->right);
        root = leftRotate(root);
    }
}

// In-order traversal (Left, Root, Right)
void Tree::inOrder(TreeNode* root) {
    if (root != nullptr) {
        inOrder(root->left);
        cout << root->data << " ";
        inOrder(root->right);
    }
}

// AVL right rotation
TreeNode* Tree::rightRotate(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// AVL left rotation
TreeNode* Tree::leftRotate(TreeNode* x) {
    TreeNode* y = x->right;
    TreeNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Get height of a node
int Tree::height(TreeNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

// Get balance factor of a node
int Tree::balanceFactor(TreeNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

// Menu-driven method to interact with the tree
void Tree::create() {
    int choice, value;
    while (true) {
        cout << "\n--- AVL Tree Menu ---\n";
        cout << "1. Insert Node\n";
        cout << "2. Display In-Order Traversal\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key to insert: ";
                cin >> value;
                insert(value);
                cout << "Node inserted successfully.\n";
                break;
            case 2:
                cout << "In-Order Traversal: ";
                inOrder(root);
                cout << endl;
                break;
            case 3:
                cout << "Exiting...\n";
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

int main() {
    Tree tree;
    tree.create();
    return 0;
}

