// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/length-of-longest-fibonacci-subsequence/submissions/1557629672
class Solution {
public:
    int lenLongestFibSubseq(vector<int>& arr) {
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        int maxLen = 0;

        for (int curr = 2; curr < n; curr++) {
            int start = 0, end = curr - 1;
            while (start < end) {
                int pairSum = arr[start] + arr[end];
                if (pairSum > arr[curr]) {
                    end--;
                } else if (pairSum < arr[curr]) {
                    start++;
                } else {
                    dp[end][curr] = dp[start][end] + 1;
                    maxLen = max(dp[end][curr], maxLen);
                    end--;
                    start++;
                }
            }
        }
        return maxLen == 0 ? 0 : maxLen + 2;
    }
};

/* Solution Description
*/
