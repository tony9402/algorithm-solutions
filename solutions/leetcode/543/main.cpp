// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/diameter-of-binary-tree/submissions/1187327313
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
    pair<int, int> dfs(TreeNode* root) {
        if(root == nullptr) return make_pair(0, 0);
        pair<int, int> L = dfs(root->left);
        pair<int, int> R = dfs(root->right);
        int cur = L.first + R.first + 1;
        return make_pair(max(L.first, R.first) + 1, max({cur, L.second, R.second}));
    }
    int diameterOfBinaryTree(TreeNode* root) {
        return dfs(root).second - 1;
    }
};

/* Solution Description
*/
