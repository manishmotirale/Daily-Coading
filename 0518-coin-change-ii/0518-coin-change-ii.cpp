#include <iostream>
#include <vector>

using namespace std;

// Recursion => TC = O(2^n), SC = O(n)
int solveRec(int i, int tar, vector<int> &coins) {
    if (i == 0) {
        if (tar % coins[i] == 0) {
            return 1;
        } else {
            return 0;
        }
    }

    int notTake = solveRec(i - 1, tar, coins);
    int take = 0;

    if (coins[i] <= tar) {
        take = solveRec(i, tar - coins[i], coins);
    }

    return take + notTake;
}

int countRec(vector<int> &coins, int sum) {
    int n = coins.size();
    return solveRec(n - 1, sum, coins);
}

// Memoization => TC = O(n * tar), SC = O(n * tar) + O(n)
int solveMemo(int i, int tar, vector<int> &coins, vector<vector<int>> &dp) {
    if (i == 0) {
        if (tar % coins[i] == 0) {
            return 1;
        } else {
            return 0;
        }
    }

    if (dp[i][tar] != -1) {
        return dp[i][tar];
    }

    int notTake = solveMemo(i - 1, tar, coins, dp);
    int take = 0;

    if (coins[i] <= tar) {
        take = solveMemo(i, tar - coins[i], coins, dp);
    }

    return take + notTake;
}

int countMemo(vector<int> &coins, int sum) {
    int n = coins.size();
    vector<vector<int>> dp(n, vector<int>(sum + 1, -1));

    return solveMemo(n - 1, sum, coins, dp);
}

// Tabulation => TC = O(n * tar), SC = O(n * tar)
int countTab(vector<int> &coins, int sum) {
    int n = coins.size();
    vector<vector<int>> dp(n, vector<int>(sum + 1, 0));

    for (int tar = 0; tar <= sum; tar++) {
        if (tar % coins[0] == 0) {
            dp[0][tar] = 1;
        }
    }

    for (int i = 1; i < n; i++) {
        for (int tar = 0; tar <= sum; tar++) {
            int notTake = dp[i - 1][tar];
            int take = 0;

            if (coins[i] <= tar) {
                take = dp[i][tar - coins[i]];
            }

            dp[i][tar] = take + notTake;
        }
    }

    return dp[n - 1][sum];
}

// Space Optimization => TC = O(n * tar), SC = O(tar)
int countSpaceOpt(vector<int> &coins, int sum) {
    int n = coins.size();
    vector<int> prev(sum + 1, 0), curr(sum + 1, 0);

    for (int tar = 0; tar <= sum; tar++) {
        if (tar % coins[0] == 0) {
            prev[tar] = 1;
        }
    }

    for (int i = 1; i < n; i++) {
        for (int tar = 0; tar <= sum; tar++) {
            int notTake = prev[tar];
            int take = 0;

            if (coins[i] <= tar) {
                take = curr[tar - coins[i]];
            }

            curr[tar] = take + notTake;
        }
        prev = curr;
    }

    return prev[sum];
}

// Space Optimization with long long to avoid overflow => TC = O(n * tar), SC =
// O(tar)
int changeDifferent(int amount, vector<int> &coins) {
    int n = coins.size();

    vector<long long> prev(amount + 1, 0);
    vector<long long> curr(amount + 1, 0);

    for (int tar = 0; tar <= amount; tar++) {
        if (tar % coins[0] == 0) {
            prev[tar] = 1;
        }
    }

    for (int i = 1; i < n; i++) {
        for (int tar = 0; tar <= amount; tar++) {

            long long notTake = prev[tar];
            long long take = 0;

            if (coins[i] <= tar) {
                take = curr[tar - coins[i]];
            }

            if (take > INT_MAX - notTake) // Avoid overflow
                curr[tar] = INT_MAX;
            else
                curr[tar] = take + notTake; // Use long long to avoid overflow
        }
        prev = curr;
    }
    return (int)prev[amount];
}

int main() {
    vector<int> coins = {1, 2, 5};
    int sum = 5;

    cout << "Number of ways (Recursion): " << countRec(coins, sum) << endl;
    cout << "Number of ways (Memoization): " << countMemo(coins, sum) << endl;
    cout << "Number of ways (Tabulation): " << countTab(coins, sum) << endl;
    cout << "Number of ways (Space Optimization): " << countSpaceOpt(coins, sum)
         << endl;

    return 0;
}
