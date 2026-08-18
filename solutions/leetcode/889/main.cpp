// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/construct-binary-tree-from-preorder-and-postorder-traversal/submissions/1552829006
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
    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        int N = (int)preorder.size();
        vector<int> ridx(N + 1);
        for(int i = 0; i < N; ++i) ridx[postorder[i]] = i;
        int idx = 0;
        function<TreeNode*(int,int)> dfs = [&](int l, int r) -> TreeNode* {
            if(l > r || idx >= N) return nullptr;
            TreeNode *cur = new TreeNode(preorder[idx ++]);
            if(l == r) return cur;
            int x = ridx[preorder[idx]];
            cur->left = dfs(l, x);
            cur->right = dfs(x + 1, r - 1);
            return cur;
        };
        return dfs(0, N - 1);
    }
};

/* Solution Description
*/
