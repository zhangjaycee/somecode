/*
by jc 20181024
tag: tree, dfs, traverse
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        int max = 0;
        traverse(root, max);
        return max;
    }
    int traverse(TreeNode* root, int &max) {
        if (!root) return 0;
        TreeNode *l = root->left;
        TreeNode *r = root->right;
        int nl = traverse(l, max);
        int nr = traverse(r, max);
        int n = nl + nr + (l != NULL) + (r != NULL);
        if (n > max) max = n;
        return std::max(nl + (l != NULL), nr + (r != NULL));
    }
};

class Solution2 {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        int dia = 0;
        traverse(root, dia);
        return dia;
    }
     int traverse(TreeNode* root, int &dia) {
        if (!root) return 0;
        int nl = traverse(root->left, dia);
        int nr = traverse(root->right, dia);
        int n = nl + nr;
        if (n > dia) dia = n;
        return max(nl, nr) + 1;
    }
};
