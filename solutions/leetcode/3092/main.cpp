// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/most-frequent-ids/submissions/1212247756
class Solution {
public:
    vector<long long> mostFrequentIDs(vector<int>& nums, vector<int>& freq) {
        priority_queue<pair<long long, int>> pq;
        vector<long long> cnt(100001);
        int N = (int)nums.size();
        vector<long long> answer;
        for(int i = 0; i < N; ++i) {
            cnt[nums[i]] += freq[i];
            pq.emplace(cnt[nums[i]], nums[i]);
            while(!pq.empty() && cnt[pq.top().second] != pq.top().first) pq.pop();
            answer.push_back(pq.top().first);
        }
        return answer;
    }
};

/* Solution Description
*/
