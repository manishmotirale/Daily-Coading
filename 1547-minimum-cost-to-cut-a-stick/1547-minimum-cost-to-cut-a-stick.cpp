class Solution {
public:
    int minCost(int n, vector<int>& cuts) {
        sort(cuts.begin(), cuts.end());

        cuts.insert(cuts.begin(), 0);
        cuts.push_back(n);

        int N = cuts.size();

        vector<vector<int>> dp(N, vector<int>(N, 0));

        for (int len = 2; len < N; len++) {
            for (int i = 0; i + len < N; i++) {
                int j = i + len;
                int cost = INT_MAX;

                for (int k = i + 1; k < j; k++) {
                    int totalCost = cuts[j] - cuts[i]
                                  + dp[i][k]
                                  + dp[k][j];

                    cost = min(cost, totalCost);
                }

                dp[i][j] = (cost == INT_MAX) ? 0 : cost;
            }
        }

        return dp[0][N - 1];
    }
};
