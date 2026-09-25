class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();

        vector<vector<int>> dp(n, vector<int>(m, 0));

        // First row
        for (int j = 0; j < m; j++) {
            dp[0][j] = matrix[0][j];
        }

        // Fill from top to bottom
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < m; j++) {

                int up = dp[i - 1][j];

                int ld = 1e9;
                if (j - 1 >= 0) {
                    ld = dp[i - 1][j - 1];
                }

                int rd = 1e9;
                if (j + 1 < m) {
                    rd = dp[i - 1][j + 1];
                }

                dp[i][j] = matrix[i][j] + min(up, min(ld, rd));
            }
        }

        // Minimum value in the last row
        int ans = 1e9;

        for (int j = 0; j < m; j++) {
            ans = min(ans, dp[n - 1][j]);
        }

        return ans;
    }
};