// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/two-sum/submissions/1514672271
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int N = (int)nums.size();
        vector<int> idx(N); iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(), [&](int u, int v) -> bool {
            return nums[u] < nums[v];
        });
        vector<int> answer;
        for(int i = 0; i < N; ++i) {
            int x = target - nums[idx[i]];
            int l = 0, r = N - 1;
            while(l <= r) {
                int mid = (l + r) / 2;
                if(nums[idx[mid]] < x) l = mid + 1;
                else r = mid - 1;
            }
            if(l < N && idx[l] == idx[i]) ++l;
            if(l < N && nums[idx[l]] == x) {
                answer.push_back(idx[l]);
                answer.push_back(idx[i]);
                break;
            }
        }
        return answer;
    }
};

/* Solution Description
원래 인덱스 배열을 값의 오름차순으로 정렬한 뒤, 각 원소마다 합이 target이 되기 위해 필요한 값을 이분 탐색한다.
찾은 위치가 현재 원소와 같으면 다음 위치를 확인해 같은 원소를 두 번 사용하는 경우를 피한다.
정렬에 O(N log N), 각 원소의 이분 탐색에 O(N log N)이 들고 인덱스 배열에 O(N)의 추가 공간을 사용한다.
*/
