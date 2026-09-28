#include <iostream>
#include <vector>
using namespace std;

// Recursion => TC = O(2^n), SC = O(n)
bool solveRec(int i, int sum, vector<int> &arr) {
    // Target achieved
    if (sum == 0) return true;
    // Only one element is left
    if (i == 0) return arr[0] == sum;

    // Don't take arr[i]
    bool notTake = solveRec(i - 1, sum, arr);
    // Take arr[i]
    bool take = false;
    if (arr[i] <= sum)
        take = solveRec(i - 1, sum - arr[i], arr);

    return take || notTake;
}

bool equalPartitionRec(vector<int> &arr) {
    int sum = 0;
    int n = arr.size();

    for (int i = 0; i < n; i++) sum += arr[i];

    // Odd sum cannot be divided into two equal parts
    if (sum % 2 != 0) return false;
    
    int target = sum / 2;

    return solveRec(n - 1, target, arr);
}

// Memoization => TC = O(n * sum), SC = O(n * sum) + O(n)
bool solveMemo(int i, int sum, vector<int> &arr, vector<vector<int>> &dp) {
    // Target achieved
    if (sum == 0) return true;
    // Only one element is left
    if (i == 0) return arr[0] == sum;

    // Already calculated
    if (dp[i][sum] != -1) return dp[i][sum];

    // Don't take arr[i]
    bool notTake = solveMemo(i - 1, sum, arr, dp);
    // Take arr[i]
    bool take = false;
    if (arr[i] <= sum) take = solveMemo(i - 1, sum - arr[i], arr, dp);

    return dp[i][sum] = take || notTake;
}

bool equalPartitionMemo(vector<int> &arr) {
    int sum = 0;
    int n = arr.size();

    // Calculate total sum first
    for (int i = 0; i < n; i++) sum += arr[i];
    
    // Odd sum cannot be divided into two equal parts
    if (sum % 2 != 0) return false;

    int target = sum / 2;
    // Create DP after calculating target
    vector<vector<int>> dp(n, vector<int>(target + 1, -1));

    return solveMemo(n - 1, target, arr, dp);
}

// Tabulation => TC = O(n * sum), SC = O(n * sum)
bool equalPartitionTab(vector<int> &arr) {
    int sum = 0;
    int n = arr.size();

    for (int i = 0; i < n; i++) sum += arr[i];

    // Odd sum cannot be divided into two equal parts
    if (sum % 2 != 0) return false;
    int target = sum / 2;

    vector<vector<bool>> dp(n, vector<bool>(target + 1, false));
    // Target 0 is always possible
    dp[0][0] = true;
    // First element
    if (arr[0] <= target) dp[0][arr[0]] = true;

    // Remaining elements
    for (int i = 1; i < n; i++) {
        for (int tar = 0; tar <= target; tar++) {
            // Don't take arr[i]
            bool notTake = dp[i - 1][tar];
            // Take arr[i]
            bool take = false;

            if (arr[i] <= tar)
                take = dp[i - 1][tar - arr[i]];

            dp[i][tar] = take || notTake;
        }
    }
    return dp[n - 1][target];
}

// Space Optimization => TC = O(n * sum),SC = O(sum)
bool equalPartitionSpaceOpt(vector<int> &arr) {
    int sum = 0;
    int n = arr.size();

    for (int i = 0; i < n; i++) sum += arr[i];
    // Odd sum cannot be divided into two equal parts
    if (sum % 2 != 0) return false;

    int target = sum / 2;

    // We only need target + 1 space
    vector<bool> prev(target + 1, false);
    vector<bool> curr(target + 1, false);

    // Target 0 is always possible
    prev[0] = true;
    // Target 0 is always possible
    curr[0] = true;

    // First element
    if (arr[0] <= target)
        prev[arr[0]] = true;

    // Remaining elements
    for (int i = 1; i < n; i++) {
        for (int tar = 1; tar <= target; tar++) {
            // Don't take arr[i]
            bool notTake = prev[tar];
            // Take arr[i]
            bool take = false;

            if (arr[i] <= tar)
                take = prev[tar - arr[i]];

            curr[tar] = take || notTake;
        }
        prev = curr;
    }
    return prev[target];
}

int main() {
    vector<int> arr = {1, 5, 11, 5};

    cout << "Using Recursion: " << equalPartition(arr) << endl;

    cout << "Using Memoization: " << equalPartitionMemo(arr) << endl;

    cout << "Using Tabulation: " << equalPartitionTab(arr) << endl;

    cout << "Using Space Optimization: " << equalPartitionSpaceOpt(arr) << endl;

    return 0;
}
