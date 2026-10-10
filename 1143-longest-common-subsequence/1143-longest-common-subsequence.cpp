class Solution {
public:
    int solveMemo(string& s1, string& s2, int i, int j,
                  vector<vector<int>>& dp) {
        if (i < 0 || j < 0) {
            return 0;
        }
        if (dp[i][j] != -1) {
            return dp[i][j];
        }

        if (s1[i] == s2[j]) {
            return 1 + solveMemo(s1, s2, i - 1, j - 1, dp);
        } else {
            int sub1 = solveMemo(s1, s2, i - 1, j, dp);
            int sub2 = solveMemo(s1, s2, i, j - 1, dp);

            return dp[i][j] = max(sub1, sub2);
        }
    }
    int longestCommonSubsequence(string text1, string text2) {
        int n = text1.size();
        int m = text2.size();

        vector<vector<int>> dp(n, vector<int>(m, -1));
        return solveMemo(text1, text2, n - 1, m - 1, dp);
    }
};