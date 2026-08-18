// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/lowest-common-ancestor-of-deepest-leaves/submissions/1596777257
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
    TreeNode* lcaDeepestLeaves(TreeNode* root) {
        return dfs(root).first;
    }
    pair<TreeNode*, int> dfs(TreeNode* x) {
        if(x == nullptr) return {nullptr, 0};
        auto L = dfs(x->left);
        auto R = dfs(x->right);
        if(L.second > R.second) return {L.first, L.second + 1};
        if(L.second < R.second) return {R.first, R.second + 1};
        return {x, L.second + 1};
    };
};

/* Solution Description
*/
