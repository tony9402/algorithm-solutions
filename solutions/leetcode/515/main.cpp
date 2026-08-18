// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/find-largest-value-in-each-tree-row/submissions/1082720795
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
    vector<int> largestValues(TreeNode* root) {
        vector<int> deps;
        function<void(TreeNode*, int)> dfs = [&](TreeNode *cur, int dep) -> void {
            if(cur == nullptr) return;
            if(deps.size() <= dep) deps.push_back(INT_MIN);
            deps[dep] = max(deps[dep], cur->val);
            if(cur->left) dfs(cur->left, dep + 1);
            if(cur->right) dfs(cur->right, dep + 1);
        };
        dfs(root, 0);
        return deps;
    }
};

/* Solution Description
*/
