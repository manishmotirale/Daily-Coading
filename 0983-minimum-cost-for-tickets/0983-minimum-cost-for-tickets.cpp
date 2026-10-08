class Solution {
public:
    int solve(vector<int>& days, vector<int>& costs, int i, vector<int>& dp) {
        if (i >= days.size()) {
            return 0;
        }

        if (dp[i] != -1) {
            return dp[i];
        }

        // 1-day ticket
        int j = i;
        while (j < days.size() && days[j] < days[i] + 1) {
            j++;
        }

        int oneDay = costs[0] + solve(days, costs, j, dp);

        // 7-day ticket
        j = i;
        while (j < days.size() && days[j] < days[i] + 7) {
            j++;
        }

        int sevenDay = costs[1] + solve(days, costs, j, dp);

        // 30-day ticket
        j = i;
        while (j < days.size() && days[j] < days[i] + 30) {
            j++;
        }

        int thirtyDay = costs[2] + solve(days, costs, j, dp);

        return dp[i] = min(oneDay, min(sevenDay, thirtyDay));
    }

    int mincostTickets(vector<int>& days, vector<int>& costs) {
        int n = days.size();
        vector<int> dp(n, -1);

        return solve(days, costs, 0, dp);
    }
};