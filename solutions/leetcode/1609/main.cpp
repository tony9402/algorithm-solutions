// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/even-odd-tree/submissions/1189214289?envType=daily-question&envId=2024-02-29
class Solution {
public:
    array<int, 100000> chk;
    bool isEvenOddTree(TreeNode* root, int dep = 0) {
        if(root == nullptr) return true;
        if(chk[dep] == 0 && dep % 2) chk[dep] = INT_MAX;
        if(1 - dep % 2 != root->val % 2) return false;
        if( dep & 1 && chk[dep] <= root->val) return false;
        if(~dep & 1 && chk[dep] >= root->val) return false;
        chk[dep] = root->val;
        return isEvenOddTree(root->left, dep + 1) && isEvenOddTree(root->right, dep + 1);
    }
};

/* Solution Description
현재 노드에서 왼쪽 오른쪽 자식을 순서대로 재귀적으로 보면서 짝수 번째 레벨에 존재하는 값이 증가하는지, 홀수 번째 레벨에 존재하는 값들은 감소하는지 확인하면 된다.  
*/