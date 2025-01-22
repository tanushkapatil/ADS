// create
// insert
// traversal:
    // inorder
    // preorder
    // postorder
// clone
// mirror
// delete:
    // leaf node
    // internal node
    // intermediate node

#include <iostream>
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
    void insert(TreeNode*& root, int value);
    void inOrder(TreeNode* root);
    void preOrder(TreeNode* root);
    void postOrder(TreeNode* root);
    void deleteNode(TreeNode* root, int key);
    void create();
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

void Tree::preOrder(TreeNode* root) {
    if (root != nullptr) {
        cout << root->data << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

void Tree::postOrder(TreeNode* root) {
    if (root != nullptr) {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->data << " ";
    }
}

void Tree::deleteNode(TreeNode* root, int key) {
    TreeNode* temp = root;
    TreeNode* temp1 = nullptr;

    while (temp) {
        if (temp->data == key) {
            if (temp->left == nullptr && temp->right == nullptr) {
                if (temp1 == nullptr) {
                    delete temp;
                    this->root = nullptr;
                } else {
                    if (temp1->data > key) {
                        temp1->left = nullptr;
                    } else {
                        temp1->right = nullptr;
                    }
                    delete temp;
                }
                return;
            }
        } else if (key > temp->data) {
            temp1 = temp;
            temp = temp->right;
        } else {
            temp1 = temp;
            temp = temp->left;
        }
    }
    
}

void Tree::create() {
    int choice, value;
    do {
        cout << "\n--- Tree Operations ---\n";
        cout << "1. Insert multiple nodes into the tree\n";
        cout << "2. Insert a single node into the tree\n";
        cout << "3. Display in-order traversal\n";
        cout << "4. Display pre-order traversal\n";
        cout << "5. Display post-order traversal\n";
        cout << "6. Delete a node from the tree\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int n;
                cout << "How many nodes to insert? ";
                cin >> n;
                for (int i = 0; i < n; i++) {
                    cout << "Enter value " << (i + 1) << ": ";
                    cin >> value;
                    insert(value);
                }
                cout << "Nodes inserted successfully.\n";
                break;
            }
            case 2:
                cout << "Enter value to insert: ";
                cin >> value;
                insert(value);
                cout << "Node inserted successfully.\n";
                break;
            case 3:
                cout << "In-order traversal: ";
                inOrder(root);
                cout << "\n";
                break;
            case 4:
                cout << "Pre-order traversal: ";
                preOrder(root);
                cout << "\n";
                break;
            case 5:
                cout << "Post-order traversal: ";
                postOrder(root);
                cout << "\n";
                break;
            case 6:
                cout << "Enter value to delete: ";
                cin >> value;
                deleteNode(root, value);
                cout << "Node deleted successfully.\n";
                break;
            case 7:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);
}

int main() {
    Tree tree;
    tree.create();

    return 0;
}
