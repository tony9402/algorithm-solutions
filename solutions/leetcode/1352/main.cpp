// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/product-of-the-last-k-numbers/submissions/1543041708
class ProductOfNumbers {
public:
    vector<int> tree;
    int N, siz, last;
    ProductOfNumbers() {
        N = 40000; last = 0;
        for(siz = 1; siz < N; siz <<= 1);
        tree.resize(siz << 1, 1);
    }

    // 0이 있어서 a / b하면 안됨.
    // 쉬운 풀이 -> 쿼리마다 logN -> 세그 트리
    // 0을 구분을 두고 0 보다 더 많이 연산을 해야하면 어자피 0임
    // 아 몰랑 세그 써 ~
    void add(int num) {
        int idx = last + siz;
        tree[idx] = num;
        while(idx >>= 1) tree[idx] = tree[idx << 1] * tree[idx << 1 | 1];
        ++ last;
    }

    int getProduct(int k) {
        int l = last - k, r = last - 1;
        int lret = 1, rret = 1;
        for(l += siz, r += siz; l <= r; l >>= 1, r >>= 1) {
            if(l & 1) lret *= tree[l ++];
            if(~r & 1) rret *= tree[r --];
        }
        return lret * rret;
    }
};

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */

/* Solution Description
*/
