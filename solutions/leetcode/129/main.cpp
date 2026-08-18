// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/sum-root-to-leaf-numbers/submissions/1232611147
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
    int sumNumbers(TreeNode* root) {
        int ret = 0;
        queue<pair<TreeNode*, int>> Q;
        Q.push(make_pair(root, root->val));
        while(!Q.empty()) {
            auto cur = Q.front(); Q.pop();
            auto L = cur.first->left; auto R = cur.first->right;
            if(L) Q.emplace(L, cur.second * 10 + L->val);
            if(R) Q.emplace(R, cur.second * 10 + R->val);
            if(!L && !R) ret += cur.second;
        }
        return ret;
    }
};

/* Solution Description
*/
