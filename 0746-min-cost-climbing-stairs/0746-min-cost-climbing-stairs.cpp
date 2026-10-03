class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();

        int first = 0;  // dp[i - 2]
        int second = 0; // dp[i - 1]

        int result = second;

        for (int i = 2; i <= n; i++) {
            result = min(second + cost[i - 1], first + cost[i - 2]);

            first = second;
            second = result;
        }

        return result;
    }
};