// Authored by: tony9402
// Co-authored by: -
// Link: https://leetcode.com/problems/check-if-grid-can-be-cut-into-sections/submissions/1584999866
class Solution {
public:
    bool cal(const vector<pair<int, int>> &V) {
        int ret = 0, sum = 0, updated = 0;
        for(int i = 0; i < (int)V.size(); ++i) {
            sum -= V[i].second;
            updated += V[i].second;
            if(V[i].second && updated && sum == 0) ++ ret;
            sum += V[i].first;
            updated += V[i].first;
        }
        return ret > 2;
    }
    bool checkValidCuts(int N, vector<vector<int>>& rectangles) {
        vector<pair<int, int>> X, Y;
        vector<int> Cx, Cy;
        for(int i = 0; i < (int)rectangles.size(); ++i) {
            auto &V = rectangles[i];
            Cx.push_back(V[0]); Cx.push_back(V[2]);
            Cy.push_back(V[1]); Cy.push_back(V[3]);
        }
        sort(Cx.begin(), Cx.end()); sort(Cy.begin(), Cy.end());
        X.resize(Cx.size()); Y.resize(Cy.size());
        for(int i = 0; i < (int)rectangles.size(); ++i) {
            auto &V = rectangles[i];
            V[0] = lower_bound(Cx.begin(), Cx.end(), V[0]) - Cx.begin();
            V[2] = lower_bound(Cx.begin(), Cx.end(), V[2]) - Cx.begin();
            V[1] = lower_bound(Cy.begin(), Cy.end(), V[1]) - Cy.begin();
            V[3] = lower_bound(Cy.begin(), Cy.end(), V[3]) - Cy.begin();
            ++ X[V[0]].first; ++ X[V[2]].second;
            ++ Y[V[1]].first; ++ Y[V[3]].second;
        }
        return cal(X) || cal(Y);
    }
};

/* Solution Description
*/
