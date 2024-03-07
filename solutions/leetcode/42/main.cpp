// Authored by : pill27211
// Co-authored by : -
// Link : https://leetcode.com/problems/trapping-rain-water/submissions/1195685828
class Solution
{
public:
    int trap(vector<int>& height)
    {
        int n(height.size()); // int n = height.size(); 와 동일

        auto pre(height); // vector<int> pre = height; 와 동일
	    for (int i(1); i < n; i++)
			pre[i] = max(pre[i - 1], height[i]);

        auto suf(height); // vector<int> suf = height; 와 동일
	    for (int i(n - 2); i >= 0; i--)
		    suf[i] = max(suf[i + 1], height[i]);

	    int ans{}; // int ans = 0; 와 동일 (https://en.cppreference.com/w/cpp/language/value_initialization)
	    for (int i(1); i < n - 1; i++)
		    ans += max(0, min(pre[i - 1], suf[i + 1]) - height[i]);

        return ans;
    }
};

/* Solution Description
i번째 지점에 쌓일 수 있는 물의 양은, 결국 height[i]와 min(i의 왼쪽에서 가장 높은 지점의 높이, i의 오른쪽에서 가장 높은 지점의 높이)의 차이로 결정된다.
따라서 지점의 높이의 최댓값을 저장하는 접두사, 접미사 배열을 두고 양 끝을 제외한 지점들을 순회하며 답을 계산해주면 된다.

generalization : i번째 지점에 물이 쌓일 수 없다는 것은 min(pre[i - 1], suf[i + 1]) < height[i] 이므로, 음수가 더해지는 것을 막기 위해 0과의 최댓값을 취해준다.
Time Complexity: O(N)
*/
