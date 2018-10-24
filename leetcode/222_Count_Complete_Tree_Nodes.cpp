/***
    by zjc 20181018
***/

/*
Given a complete binary tree, count the number of nodes.

Note:

Definition of a complete binary tree from Wikipedia:
In a complete binary tree every level, except possibly the last, is completely filled, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.

Example:

Input: 
    1
   / \
  2   3
 / \  /
4  5 6

Output: 6
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
    int countNodes(TreeNode* root) {
        return count(root);
    }
    int count(TreeNode* root) {
        if (NULL == root) return 0;
        int a, b;
        a = 1;
        b = 1;
        TreeNode* l = root->left;
        TreeNode* r = root->right;
		// decrease traverseing nodes by detecting full binary trees
		// because we can directly calculate the node number of full bianry trees
		// are (pow(2, a) - 1)
        while (l) {
            a++;
            l = l->left;
        }
        while (r) {
            b++;
            r = r->right;
        }
        if (a == b) return pow(2, a) - 1; // full binary tree
        return 1 + count(root->left) + count(root->right); // not full, go down next tier
    }
};
