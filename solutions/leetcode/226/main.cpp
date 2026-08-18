// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/invert-binary-tree/submissions/1414667965
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
    TreeNode* invertTree(TreeNode* root) {
        if(root == nullptr) return nullptr;
        invertTree(root->left); invertTree(root->right);
        swap(root->left, root->right);
        return root;
    }
};

/* Solution Description
*/
