// create : done
// insert : done
// traversal ----
    // inorder : done
    // preorder
    // postorder
// clone
// mirror
// delete ----
    // leaf node : done
    // internal node : done
    // intermediate node : done

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
    TreeNode* current = root;
    TreeNode* prev = nullptr;

    while (current) {
        if (current->data == key) {
            if (current->left == nullptr && current->right == nullptr) {
                if (prev == nullptr) {
                    delete current;
                    this->root = nullptr;
                } else {
                    if (prev->data > key) {
                        prev->left = nullptr;
                    } else {
                        prev->right = nullptr;
                    }
                    delete current;
                }
                return;
            }
            /*if (current->left == nullptr || current->right == nullptr) {
                if(current->right && current->left == nullptr) {
                    prev->right = current->right;
                    delete current;
                }
                if(current->left && current->right == nullptr) {
                    prev->left = current->left;
                    delete current;
                }
            }*/
            if (current->left == nullptr && current->right != nullptr) {
                if (prev == nullptr) {
                    root = current->right;
                } else {
                    if (prev->left == current) {
                        prev->left = current->right;
                    } else {
                        prev->right = current->right;
                    }
                }
                delete current;
                return;
            } 
            else if (current->left != nullptr && current->right == nullptr) {
                if (prev == nullptr) {
                    root = current->left;
                } else {
                    if (prev->left == current) {
                        prev->left = current->left;
                    } else {
                        prev->right = current->left;
                    }
                }
                delete current;
                return;
            }

            if (current->left && current->right){
                TreeNode* successorParent = current;
                TreeNode* successor = current->right;
                while (successor->left != nullptr) {
                    successorParent = successor;
                    successor = successor->left;
                }
                current->data = successor->data;
                if (successorParent->left == successor) {
                    successorParent->left = successor->right;
                } 
                else {
                    successorParent->right = successor->right;
                }
                delete successor;
                return;
            }
        } else if (key > current->data) {
            prev = current;
            current = current->right;
        } else {
            prev = current;
            current = current->left;
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
