// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/find-elements-in-a-contaminated-binary-tree/submissions/1550196415
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
class FindElements {
public:
    vector<int> exists;
    FindElements(TreeNode* root) {
        exists.resize(1000001);
        root->val = 0;
        function<void(TreeNode*)> dfs = [&](TreeNode *cur) -> void {
            if(cur->val < exists.size()) exists[cur->val] = 1;
            if(cur->left) {
                cur->left->val = 2 * cur->val + 1;
                dfs(cur->left);
            }
            if(cur->right) {
                cur->right->val = 2 * cur->val + 2;
                dfs(cur->right);
            }
        };
        dfs(root);
    }

    bool find(int target) {
        return exists[target];
    }
};

/**
 * Your FindElements object will be instantiated and called as such:
 * FindElements* obj = new FindElements(root);
 * bool param_1 = obj->find(target);
 */

/* Solution Description
*/
