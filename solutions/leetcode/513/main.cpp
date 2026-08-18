// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/find-bottom-left-tree-value/submissions/1188228560
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
    int findBottomLeftValue(TreeNode* root) {
        int mxdep = -1, ans = 0;
        function<void(TreeNode*, int)> dfs = [&](TreeNode *cur, int dep) -> void {
            if(cur == nullptr) return;
            if(mxdep < dep) {
                mxdep = dep;
                ans = cur->val;
            }
            dfs(cur->left, dep + 1);
            dfs(cur->right, dep + 1);
        };
        dfs(root, 0);
        return ans;
    }
};

/* Solution Description
*/
