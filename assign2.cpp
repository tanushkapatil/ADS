#include <iostream>
using namespace std;

struct TreeNode {
    int player_id;
    int score;
    TreeNode* left;
    TreeNode* right;
    int height;

    TreeNode(int id, int sc) {
        player_id = id;
        score = sc;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

class Tree {
public:
    TreeNode* root;

    Tree();

    void insert(int player_id, int score);
    TreeNode* insert(TreeNode* root, int player_id, int score);

    void preOrder(TreeNode* root);

    TreeNode* rightRotate(TreeNode* y);
    TreeNode* leftRotate(TreeNode* x);

    int height(TreeNode* node);
    int balanceFactor(TreeNode* node);

    TreeNode* minValueNode(TreeNode* node);
    TreeNode* deleteNode(TreeNode* root, int player_id);

    void create();
};

Tree::Tree() { root = nullptr; }

void Tree::insert(int player_id, int score) {
    root = insert(root, player_id, score);
}

TreeNode* Tree::insert(TreeNode* root, int player_id, int score) {
    if (root == nullptr) {
        return new TreeNode(player_id, score);
    }

    if (score < root->score) {
        root->left = insert(root->left, player_id, score);
    } else {
        root->right = insert(root->right, player_id, score);
    }

    root->height = max(height(root->left), height(root->right)) + 1;
    int balance = balanceFactor(root);

    if (balance > 1 && score < root->left->score) {
        return rightRotate(root);
    }
    if (balance < -1 && score > root->right->score) {
        return leftRotate(root);
    }
    if (balance > 1 && score > root->left->score) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && score < root->right->score) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

TreeNode* Tree::deleteNode(TreeNode* root, int player_id) {
    if (root == nullptr) return root;

    if (player_id < root->player_id) {
        root->left = deleteNode(root->left, player_id);
    } else if (player_id > root->player_id) {
        root->right = deleteNode(root->right, player_id);
    } else {
        if ((root->left == nullptr) || (root->right == nullptr)) {
            TreeNode* temp = root->left ? root->left : root->right;

            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }

            delete temp;
        } else {
            TreeNode* temp = minValueNode(root->right);
            root->player_id = temp->player_id;
            root->score = temp->score;
            root->right = deleteNode(root->right, temp->player_id);
        }
    }

    if (root == nullptr) return root;

    root->height = max(height(root->left), height(root->right)) + 1;

    int balance = balanceFactor(root);

    if (balance > 1 && balanceFactor(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && balanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && balanceFactor(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && balanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void Tree::preOrder(TreeNode* root) {
    if (root != nullptr) {
        cout << "Player ID: " << root->player_id << " - Score: " << root->score << endl;
        preOrder(root->right);  // Displaying leaderboard in descending order
        preOrder(root->left);
    }
}

TreeNode* Tree::rightRotate(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

TreeNode* Tree::leftRotate(TreeNode* x) {
    TreeNode* y = x->right;
    TreeNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int Tree::height(TreeNode* node) {
    return node ? node->height : 0;
}

int Tree::balanceFactor(TreeNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

TreeNode* Tree::minValueNode(TreeNode* node) {
    TreeNode* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

void Tree::create() {
    int choice, player_id, score;
    while (true) {
        cout << "\n--- Multiplayer Game System ---\n";
        cout << "1. Register Player\n";
        cout << "2. Display Leaderboard\n";
        cout << "3. Remove Player\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Player ID and Score: ";
                cin >> player_id >> score;
                insert(player_id, score);
                cout << "Player Registered Successfully.\n";
                break;
            case 2:
                cout << "Leaderboard:\n";
                preOrder(root);
                break;
            case 3:
                cout << "Enter Player ID to Remove: ";
                cin >> player_id;
                root = deleteNode(root, player_id);
                cout << "Player Removed Successfully.\n";
                break;
            case 4:
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
