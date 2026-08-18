// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/angle-between-hands-of-a-clock/submissions/2037161152
class Solution {
public:
    double angleClock(int hour, int minutes) {
        if(hour == 12) hour = 0;
        double angle1 = 6 * minutes; // 분침
        double angle2 = hour * 30. + 0.5 * minutes; // 시침
        double mx = max(angle1, angle2), mn = min(angle1, angle2);
        return min(mx - mn, 360 - mx + mn);
    }
};

/* Solution Description
*/
