// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/binary-tree-level-order-traversal/submissions/745917700
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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> answer;
        queue<TreeNode*> Q;
        if(root) Q.push(root);
        while(!Q.empty()) {
            vector<int> currentLevel;
            int qsize = Q.size();
            while(qsize--) {
                auto cur = Q.front(); Q.pop();
                currentLevel.push_back(cur->val);
                if(cur->left) Q.push(cur->left);
                if(cur->right) Q.push(cur->right);
            }
            answer.push_back(currentLevel);
        }
        return answer;
    }
};

/* Solution Description
*/
