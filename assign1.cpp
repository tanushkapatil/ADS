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

