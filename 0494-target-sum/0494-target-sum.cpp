class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int n = nums.size();
        int totalSum = 0;

        for (auto& it : nums)
            totalSum += it;

        if (totalSum - target < 0 || (totalSum - target) % 2)
            return 0;

        int tar = (totalSum - target) / 2;

        vector<int> prev(tar + 1, 0), curr(tar + 1, 0);

        // Base case
        if (nums[0] == 0)
            prev[0] = 2;
        else
            prev[0] = 1;

        if (nums[0] != 0 && nums[0] <= tar)
            prev[nums[0]] = 1;

        // DP
        for (int i = 1; i < n; i++) {
            for (int sum = 0; sum <= tar; sum++) {

                int notTake = prev[sum];
                int take = 0;

                if (nums[i] <= sum)
                    take = prev[sum - nums[i]];

                curr[sum] = notTake + take;
            }
            prev = curr;
        }
        return prev[tar];
    }
};