class Solution {
public:
    bool solveMemo(int index, int target, vector<int>& nums,
                   vector<vector<int>>& dp) {
        // Target achieved
        if (target == 0)
            return true;

        // Only one element left
        if (index == 0)
            return nums[0] == target;

        // Already calculated
        if (dp[index][target] != -1)
            return dp[index][target];

        // Don't take current element
        bool notTake = solveMemo(index - 1, target, nums, dp);
        // Take current element
        bool take = false;

        if (nums[index] <= target) {
            take = solveMemo(index - 1, target - nums[index], nums, dp);
        }
        return dp[index][target] = take || notTake;
    }

    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        int totalSum = 0;

        // Calculate total sum
        for (int i = 0; i < n; i++) {
            totalSum += nums[i];
        }

        // Equal partition is impossible
        // if total sum is odd
        if (totalSum % 2 != 0)
            return false;

        int target = totalSum / 2;

        // dp[index][target]
        vector<vector<int>> dp(n, vector<int>(target + 1, -1));
        // Can we make target using the array?
        return solveMemo(n - 1, target, nums, dp);
    }
};