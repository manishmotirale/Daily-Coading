#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// Recursion => TC = O(2^n), SC = O(n)
int solveRec(int i, int tar, vector<int> &coins) {
    if (i == 0) {
        if (tar % coins[i] == 0) {
            return tar / coins[i];
        } else {
            return 1e9;
        }
    }

    int nottake = solveRec(i - 1, tar, coins);

    int take = INT_MAX;
    if (tar >= coins[i]) {
        take = 1 + solveRec(i, tar - coins[i], coins);
    }

    return min(take, nottake);
}

int minCoinsRec(vector<int> &coins, int sum) {
    int n = coins.size();

    int ans = solveRec(n - 1, sum, coins);

    if (ans >= 1e9)
        return -1;

    return ans;
}

// Memoization => TC = O(n*sum), SC = O(n*sum) + O(n)
int solveMemo(int i, int tar, vector<int> &coins, vector<vector<int>> &dp) {
    if (i == 0) {
        if (tar % coins[i] == 0) {
            return tar / coins[i];
        } else {
            return 1e9;
        }
    }

    if (dp[i][tar] != -1)
        return dp[i][tar];

    int nottake = solveMemo(i - 1, tar, coins, dp);

    int take = INT_MAX;
    if (tar >= coins[i]) {
        take = 1 + solveMemo(i, tar - coins[i], coins, dp);
    }

    return dp[i][tar] = min(take, nottake);
}

int minCoinsMemo(vector<int> &coins, int sum) {
    int n = coins.size();

    vector<vector<int>> dp(n, vector<int>(sum + 1, -1));
    int ans = solveMemo(n - 1, sum, coins, dp);

    if (ans >= 1e9)
        return -1;

    return ans;
}

// Tabulation => TC = O(n*sum), SC = O(n*sum)
int minCoinsTab(vector<int> &coins, int sum) {
    int n = coins.size();

    vector<vector<int>> dp(n, vector<int>(sum + 1, 0));

    for (int tar = 0; tar <= sum; tar++) {
        if (tar % coins[0] == 0) {
            dp[0][tar] = tar / coins[0];
        } else {
            dp[0][tar] = 1e9;
        }
    }

    for (int i = 1; i < n; i++) {
        for (int tar = 0; tar <= sum; tar++) {
            int nottake = dp[i - 1][tar];

            int take = INT_MAX;
            if (tar >= coins[i]) {
                take = 1 + dp[i][tar - coins[i]];
            }

            dp[i][tar] = min(take, nottake);
        }
    }

    if (dp[n - 1][sum] >= 1e9)
        return -1;

    return dp[n - 1][sum];
}

// Space Optimization => TC = O(n*sum), SC = O(sum)
int minCoinsSpace(vector<int> &coins, int sum) {
    int n = coins.size();

    vector<int> prev(sum + 1, 0), curr(sum + 1, 0);

    for (int tar = 0; tar <= sum; tar++) {
        if (tar % coins[0] == 0) {
            prev[tar] = tar / coins[0];
        } else {
            prev[tar] = 1e9;
        }
    }

    for (int i = 1; i < n; i++) {
        for (int tar = 0; tar <= sum; tar++) {
            int nottake = prev[tar];

            int take = INT_MAX;
            if (tar >= coins[i]) {
                take = 1 + prev[tar - coins[i]];
            }

            curr[tar] = min(take, nottake);
        }
    }

    if (curr[sum] >= 1e9)
        return -1;

    return curr[sum];
}

int main() {
    vector<int> coins = {1, 2, 5};
    int sum = 11;

    cout << "Minimum coins (Recursion): " << minCoinsRec(coins, sum) << endl;

    cout << "Minimum coins (Memoization): " << 
    minCoinsMemo(coins, sum) << endl;
    
    cout << "Minimum coins (Tabulation): " << minCoinsTab(coins, sum) << endl;
    
    cout << "Minimum coins (Space Optimization): " << minCoinsSpace(coins, sum)
         << endl;

    return 0;
}
