class Solution {
public:
    int solveMemo(int i, int tar, vector<int>& coins, vector<vector<int>>& dp) {
        if (i == 0) {
            if (tar % coins[0] == 0)
                return tar / coins[0];
            else
                return 1e9;
        }

        if (dp[i][tar] != -1)
            return dp[i][tar];

        int nottake = solveMemo(i - 1, tar, coins, dp);
        int take = 1e9;

        if (tar >= coins[i]) {
            take = 1 + solveMemo(i, tar - coins[i], coins, dp);
        }
        return dp[i][tar] = min(take, nottake);
    }

    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();

        vector<vector<int>> dp(n, vector<int>(amount + 1, -1));
        int ans = solveMemo(n - 1, amount, coins, dp);

        if (ans >= 1e9)
            return -1;

        return ans;
    }
};