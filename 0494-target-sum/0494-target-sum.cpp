class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int n = nums.size();
        int sum = 0;

        for (int x : nums)
            sum += x;

        if (abs(target) > sum)
            return 0;

        if ((sum + target) % 2 != 0)
            return 0;

        int newTarget = (sum + target) / 2;

        vector<vector<int>> dp(n, vector<int>(newTarget + 1, 0));

        if (nums[0] == 0)
            dp[0][0] = 2;
        else {
            dp[0][0] = 1;

            if (nums[0] <= newTarget)
                dp[0][nums[0]] = 1;
        }

        for (int i = 1; i < n; i++) {
            for (int j = 0; j <= newTarget; j++) {
                int notPick = dp[i - 1][j];

                int pick = 0;
                if (nums[i] <= j)
                    pick = dp[i - 1][j - nums[i]];

                dp[i][j] = pick + notPick;
            }
        }

        return dp[n - 1][newTarget];
    }
};