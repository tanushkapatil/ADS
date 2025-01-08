#include<iostream>
using namespace std;

class TreeNode {
    public:
        int data;
        TreeNode *left, *right;

        TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

class Tree {
    public:
        TreeNode *root;
        Tree(); 
        void insert(int value);
        void insert(TreeNode*& root, int value); // Recursive helper function
        void inOrder(TreeNode* root);
};

Tree::Tree() { 
    root = nullptr; 
}

void Tree::insert(TreeNode*& root, int value) {
    if (root == nullptr) {
        root = new TreeNode(value);
    } else if (value < root->data) {
        insert(root->left, value);
    } else {
        insert(root->right, value);
    }
}

void Tree::insert(int value) {
    insert(root, value);
}

void Tree::inOrder(TreeNode* root) {
    if (root != nullptr) {
        inOrder(root->left);
        cout << root->data << " ";
        inOrder(root->right);
    }
}

int main() {
    Tree tree;
    int choice, value;

    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Insert a node into the tree\n";
        cout << "2. Display in-order traversal\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter the value to insert: ";
                cin >> value;
                tree.insert(value);
                cout << "Value inserted successfully.\n";
                break;
            case 2:
                cout << "In-order traversal: ";
                tree.inOrder(tree.root); 
                cout << "\n";
                break;
            case 3:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while(choice != 3); 

    return 0;
}



