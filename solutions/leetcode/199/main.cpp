// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/binary-tree-right-side-view/submissions/744037873
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
    void dfs(vector<int> &answer, TreeNode* cur, int dep) {
        if(cur == NULL) return;
        if(answer.size() < dep) answer.emplace_back(cur->val);
        if(cur->right) dfs(answer, cur->right, dep + 1);
        if(cur->left) dfs(answer, cur->left, dep + 1);
    }
    vector<int> rightSideView(TreeNode* root) {
        vector<int> answer;
        dfs(answer, root, 1);
        return answer;
    }
};

/* Solution Description
*/
