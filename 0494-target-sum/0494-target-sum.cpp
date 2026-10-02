class Solution {
public:
    int mod = 1e9 + 7;
    int findTargetSumWays(vector<int>& nums, int target) {
        int totalSum = 0;

        for (auto& it : nums)
            totalSum += it;

        if (totalSum - target < 0 || (totalSum - target) % 2)
            return 0;

        int tar = (totalSum - target) / 2;
        int n = nums.size();

        vector<int> prev(tar + 1, 0), curr(tar + 1, 0);

        if (nums[0] == 0)
            prev[0] = 2;
        else
            prev[0] = 1;

        if (nums[0] != 0 && nums[0] <= tar)
            prev[nums[0]] = 1;

        for (int i = 1; i < n; i++) {
            for (int j = 0; j <= tar; j++) {
                int notTake = prev[j];

                int take = 0;
                if (nums[i] <= j)
                    take = prev[j - nums[i]];

                curr[j] = (notTake + take) % mod;
            }
            prev = curr;
        }

        return prev[tar];
    }
};