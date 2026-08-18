// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/minimum-number-of-operations-to-sort-a-binary-tree-by-level/submissions/1486106208
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
    int minimumOperations(TreeNode* root) {
        int ans = 0;
        queue<TreeNode*> Q({root});
        while(!Q.empty()) {
            int qs = Q.size();
            vector<int> V;
            while(~--qs) {
                TreeNode* cur = Q.front(); Q.pop();
                V.push_back(cur->val);
                if(cur->left) Q.push(cur->left);
                if(cur->right) Q.push(cur->right);
            }
            vector<int> idx(V.size()); iota(idx.begin(), idx.end(), 0);
            sort(idx.begin(), idx.end(), [&](int a, int b) -> bool {
                return V[a] < V[b];
            });
            int cnt = 0;
            for(int i = 0; i < idx.size(); ++i) {
                while(i != idx[i]) swap(idx[i], idx[idx[i]]), ++ cnt;
            }
            ans += cnt;
        }
        return ans;
    }
};

/* Solution Description
*/
