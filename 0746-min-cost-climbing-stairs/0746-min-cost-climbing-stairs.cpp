#include <iostream>
#include <vector>
using namespace std;

// Recursion => TC: O(2^n), SC: O(n)
int solveRec(vector<int> &cost, int n) {
    if (n <= 1) {
        return 0;
    }
    
    return min(solveRec(cost, n - 1) + cost[n - 1],
               solveRec(cost, n - 2) + cost[n - 2]);
}

int minCostClimbingStairsRecursion(vector<int> &cost, int n) {
    return solveRec(cost, n);
}

// Memoization => TC: O(n), SC: O(n)
int solveMemo(vector<int> &cost, int n, vector<int> &dp) {
    if (n <= 1) {
        return 0;
    }

    if (dp[n] != -1) {
        return dp[n];
    }

    return dp[n] = min(solveMemo(cost, n - 1, dp) + cost[n - 1],
                       solveMemo(cost, n - 2, dp) + cost[n - 2]);
}

int minCostClimbingStairsMemoization(vector<int> &cost, int n) {
    vector<int> dp(n + 1, -1);
    return solveMemo(cost, n, dp);
}

// Tabulation => TC: O(n), SC: O(n)
int minCostClimbingStairsTab(vector<int> &cost) {
    int n = cost.size();

    vector<int> dp(n + 1);

    dp[0] = 0;
    dp[1] = 0;

    for (int i = 2; i <= n; i++) {
        dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
    }

    return dp[n];
}

// Optimized => TC: O(n), SC: O(1)
int minCostClimbingStairsOptimized(vector<int> &cost) {
    int n = cost.size();

    int prev2 = 0; // dp[i - 2]
    int prev1 = 0; // dp[i - 1]

    int result = prev1;

    for (int i = 2; i <= n; i++) {
        result = min(prev1 + cost[i - 1], prev2 + cost[i - 2]);

        prev2 = prev1;
        prev1 = result;
    }

    return result;
}

int main() {
    vector<int> cost = {10, 15, 20};
    cout << "Minimum cost to climb stairs: "
         << minCostClimbingStairsRecursion(cost, cost.size()) << endl;

    cout << "Minimum cost to climb stairs: "
         << minCostClimbingStairsMemoization(cost, cost.size()) << endl;

    cout << "Minimum cost to climb stairs: " << minCostClimbingStairsTab(cost)
         << endl;
    cout << "Minimum cost to climb stairs: "
         << minCostClimbingStairsOptimized(cost) << endl;

    return 0;
}
