/*
by jc 20181024
tag: tree, dfs, traverse
*/


/*
Given a binary tree, find the length of the longest path where each node in the path has the same value. This path may or may not pass through the root.

Note: The length of path between two nodes is represented by the number of edges between them.

Example 1:

Input:

              5
             / \
            4   5
           / \   \
          1   1   5
Output:

2
Example 2:

Input:

              1
             / \
            4   5
           / \   \
          4   4   5
Output:

2
Note: The given binary tree has not more than 10000 nodes. The height of the tree is not more than 1000.
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
    int longestUnivaluePath(TreeNode* root) {
        int max_v = 0;
        dfs(root, max_v);
        return max_v;
    }
    int dfs(TreeNode* root, int &max_v) {
        if (!root) return 0;
        int l = root->left ? dfs(root->left, max_v) : 0;
        int r = root->right ? dfs(root->right, max_v) : 0;
        int v = 0;
        int v_l, v_r;
        if (root->left && root->left->val == root->val)
            v_l = l + 1;
        else
            v_l = 0;
        if (root->right && root->right->val == root->val)
            v_r = r + 1;
        else
            v_r = 0;
        v = v_r + v_l;
        if (v > max_v) max_v = v;
        return max(v_r, v_l);
    }
};
