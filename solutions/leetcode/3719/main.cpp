// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/longest-balanced-subarray-i/submissions/1914309661
struct Segment {
    struct Node {
        int cnt, x;
        Node():cnt(0),x(0) { }
        void add() {
            if(cnt == 0) x = 1;
            ++ cnt;
        }
        void remove() {
            -- cnt;
            if(cnt == 0) x = 0;
        }
        void update(int x) {
            if(x > 0) add();
            else remove();
        }
    };
    vector<Node> tree;
    int siz;
    Segment(int N = 1 << 17) {
        for(siz = 1; siz < N; siz <<= 1);
        tree.resize(siz << 1);
    }
    void update(int idx, int x) {
        tree[idx += siz].update(x);
        while(idx >>= 1) tree[idx] = merge(tree[idx << 1], tree[idx << 1 | 1]);
    }
    int query() { return tree[1].x; }
    Node merge(Node a, Node b) {
        Node ret;
        ret.x = a.x + b.x;
        return ret;
    }
};

class Solution {
public:
    int longestBalanced(vector<int>& nums) {
        int N = (int)nums.size();
        int ans = 0;
        Segment oseg(1e5 + 1), eseg(1e5 + 1);
        for(int i = 0; i < N; ++i) {
            for(int j = i; j < N; ++j) {
                if(nums[j] & 1) oseg.update(nums[j], 1);
                else eseg.update(nums[j], 1);
                if(oseg.query() == eseg.query()) ans = max(ans, j - i + 1);
            }
            for(int j = i; j < N; ++j) {
                if(nums[j] & 1) oseg.update(nums[j], -1);
                else eseg.update(nums[j], -1);
            }
        }
        return ans;
    }
};

/* Solution Description
*/
