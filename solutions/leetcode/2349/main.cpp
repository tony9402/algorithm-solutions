// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/design-a-number-container-system/submissions/1536861674
class NumberContainers {
private:
    unordered_map<int, int> idx;
    unordered_map<int, set<int>> nums;
public:
    NumberContainers() {}
    void change(int index, int number) {
        if(idx.find(index) != idx.end()) {
            int pn = idx[index];
            nums[pn].erase(index);
            if(nums[pn].empty()) nums.erase(pn);
        }
        nums[idx[index] = number].insert(index);
    }

    int find(int number) {
        return nums.count(number) == 0 ? -1 : *nums[number].begin();
    }
};

/**
 * Your NumberContainers object will be instantiated and called as such:
 * NumberContainers* obj = new NumberContainers();
 * obj->change(index,number);
 * int param_2 = obj->find(number);
 */

/* Solution Description
*/
