// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/distribute-elements-into-two-arrays-ii/submissions/1193197357
struct Segment {
    vector<int> tree;
    int siz;

    Segment(int N = 1 << 17) {
        for(siz = 1; siz <= N; siz <<= 1);
        tree.resize(siz << 1);
    }
    void update(int idx) {
        tree[idx += siz] ++;
        while(idx >>= 1) tree[idx] = merge(tree[idx << 1], tree[idx << 1 | 1]);
    }
    int query(int l, int r, int s, int e, int pos) {
        if(s <= l && r <= e) return tree[pos];
        if(e < l || r < s) return 0;
        int mid = (l + r) / 2;
        return merge(query(l, mid, s, e, pos << 1), query(mid + 1, r, s, e, pos << 1 | 1));
    }
    int query(int s, int e) { return query(0, siz - 1, s, e, 1); }
    int merge(int a, int b) { return a + b; }
};

class Solution {
public:
    vector<int> resultArray(vector<int>& nums) {
        vector<int> compress = nums;
        sort(compress.begin(), compress.end());
        compress.erase(unique(compress.begin(), compress.end()), compress.end());
        int K = compress.size(), N = nums.size();
        for(int &x: nums) x = lower_bound(compress.begin(), compress.end(), x) - compress.begin();
        Segment seg1(K + 1), seg2(K + 1);
        vector<int> V, W, answer;
        V.push_back(compress[nums[0]]); W.push_back(compress[nums[1]]);
        seg1.update(nums[0]); seg2.update(nums[1]);
        for(int i = 2; i < N; ++i) {
            int L = seg1.query(nums[i] + 1, K);
            int R = seg2.query(nums[i] + 1, K);
            if(L == R) {
                if(V.size() > W.size()) W.push_back(compress[nums[i]]), seg2.update(nums[i]);
                else V.push_back(compress[nums[i]]), seg1.update(nums[i]);
            }
            else if(L > R) {
                V.push_back(compress[nums[i]]);
                seg1.update(nums[i]);
            }
            else {
                W.push_back(compress[nums[i]]);
                seg2.update(nums[i]);
            }
        }
        for(const int &x: V) answer.push_back(x);
        for(const int &x: W) answer.push_back(x);
        return answer;
    }
};

/* Solution Description
*/
