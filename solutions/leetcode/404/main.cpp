// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/sum-of-left-leaves/submissions/1232190822
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int sumOfLeftLeaves(TreeNode* root, bool left = false) {
        if(root == nullptr) return 0;
        int ret = 0;
        if(left && root->left == nullptr && root->right == nullptr) ret = root->val;
        return ret + sumOfLeftLeaves(root->left, true) + sumOfLeftLeaves(root->right);
    }
};

/* Solution Description
*/
