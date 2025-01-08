#include<iostream>
using namespace std;

class TreeNode {
    public:
        int data;
        TreeNode *left, *right;

        TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

