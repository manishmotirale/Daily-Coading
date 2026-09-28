class Solution {
public:
    bool canPartition(vector<int>& nums) {

        int sum = 0;
        int n = nums.size();

        // Calculate total sum
        for (int i = 0; i < n; i++) {
            sum += nums[i];
        }

        // If total sum is odd,
        // equal partition is impossible
        if (sum % 2 != 0)
            return false;

        // Each subset must have sum = sum / 2
        int target = sum / 2;

        // dp[i][tar] means:
        // Can we make sum 'tar' using elements from 0 to i?
        vector<vector<bool>> dp(n, vector<bool>(target + 1, false));

        // Sum 0 is always possible
        // by taking nothing
        dp[0][0] = true;

        // Take the first element
        if (nums[0] <= target)
            dp[0][nums[0]] = true;

        // Start from second element
        for (int i = 1; i < n; i++) {

            for (int tar = 0; tar <= target; tar++) {

                // Don't take nums[i]
                bool notTake = dp[i - 1][tar];

                // Take nums[i]
                bool take = false;

                if (nums[i] <= tar)
                    take = dp[i - 1][tar - nums[i]];

                dp[i][tar] = take || notTake;
            }
        }

        return dp[n - 1][target];
    }
};