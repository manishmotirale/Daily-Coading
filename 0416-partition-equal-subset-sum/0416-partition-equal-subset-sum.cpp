#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// APPROACH 1: MINIMUM SUBSET SUM DIFFERENCE

// ---------- Recursion ----------
// TC: O(2^n * target), SC: O(target)
bool solveRec(int index, int target, vector<int> &arr) {
    if (target == 0)
        return true;

    if (index == 0)
        return arr[0] == target;

    bool notTake = solveRec(index - 1, target, arr);

    bool take = false;
    if (arr[index] <= target)
        take = solveRec(index - 1, target - arr[index], arr);

    return take || notTake;
}

int minDifferenceRec(vector<int> &arr) {
    int n = arr.size();
    int totalSum = 0;

    for (int i = 0; i < n; i++)
        totalSum += arr[i];

    int target = totalSum / 2;

    for (int s1 = target; s1 >= 0; s1--) {
        if (solveRec(n - 1, s1, arr))
            return totalSum - 2 * s1;
    }

    return totalSum;
}

// ---------- Memoization ----------
// TC: O(n * target), SC: O(n * target)
bool solveMemo(int index, int target, vector<int> &arr,
               vector<vector<int>> &dp) {
    if (target == 0)
        return true;

    if (index == 0)
        return arr[0] == target;

    if (dp[index][target] != -1)
        return dp[index][target];

    bool notTake = solveMemo(index - 1, target, arr, dp);

    bool take = false;
    if (arr[index] <= target)
        take = solveMemo(index - 1, target - arr[index], arr, dp);

    return dp[index][target] = take || notTake;
}

int minDifferenceMemo(vector<int> &arr) {
    int n = arr.size();
    int totalSum = 0;

    for (int i = 0; i < n; i++)
        totalSum += arr[i];

    int target = totalSum / 2;

    vector<vector<int>> dp(n, vector<int>(target + 1, -1));

    for (int s1 = target; s1 >= 0; s1--) {
        if (solveMemo(n - 1, s1, arr, dp))
            return totalSum - 2 * s1;
    }

    return totalSum;
}

// ---------- Tabulation ----------
// TC: O(n * target), SC: O(n * target)
int minDifferenceTab(vector<int> &arr) {
    int n = arr.size();
    int totalSum = 0;

    for (int i = 0; i < n; i++)
        totalSum += arr[i];

    int target = totalSum / 2;

    vector<vector<bool>> dp(n, vector<bool>(target + 1, false));

    for (int i = 0; i < n; i++)
        dp[i][0] = true;

    if (arr[0] <= target)
        dp[0][arr[0]] = true;

    for (int i = 1; i < n; i++) {
        for (int tar = 1; tar <= target; tar++) {

            bool notTake = dp[i - 1][tar];

            bool take = false;
            if (arr[i] <= tar)
                take = dp[i - 1][tar - arr[i]];

            dp[i][tar] = take || notTake;
        }
    }

    for (int s1 = target; s1 >= 0; s1--) {
        if (dp[n - 1][s1])
            return totalSum - 2 * s1;
    }

    return totalSum;
}

// ---------- Space Optimization ----------
// TC: O(n * target), SC: O(target)
int minDifferenceSpace(vector<int> &arr) {
    int n = arr.size();
    int totalSum = 0;

    for (int i = 0; i < n; i++)
        totalSum += arr[i];

    int target = totalSum / 2;

    vector<bool> prev(target + 1, false);
    vector<bool> curr(target + 1, false);

    prev[0] = true;
    curr[0] = true;

    if (arr[0] <= target)
        prev[arr[0]] = true;

    for (int i = 1; i < n; i++) {
        for (int tar = 1; tar <= target; tar++) {

            bool notTake = prev[tar];

            bool take = false;
            if (arr[i] <= tar)
                take = prev[tar - arr[i]];

            curr[tar] = take || notTake;
        }

        prev = curr;
    }

    for (int s1 = target; s1 >= 0; s1--) {
        if (prev[s1])
            return totalSum - 2 * s1;
    }

    return totalSum;
}

// APPROACH 2: EQUAL PARTITION

// ---------- Recursion ----------
// TC: O(2^n * target), SC: O(target)
bool equalRec(int index, int target, vector<int> &arr) {
    if (target == 0)
        return true;

    if (index == 0)
        return arr[0] == target;

    bool notTake = equalRec(index - 1, target, arr);

    bool take = false;
    if (arr[index] <= target)
        take = equalRec(index - 1, target - arr[index], arr);

    return take || notTake;
}

bool canPartitionRec(vector<int> &arr) {
    int n = arr.size();
    int totalSum = 0;

    for (int i = 0; i < n; i++)
        totalSum += arr[i];

    if (totalSum % 2 != 0)
        return false;

    return equalRec(n - 1, totalSum / 2, arr);
}

// ---------- Memoization ----------
// TC: O(n * target), SC: O(n * target)
bool equalMemo(int index, int target, vector<int> &arr,
               vector<vector<int>> &dp) {
    if (target == 0)
        return true;

    if (index == 0)
        return arr[0] == target;

    if (dp[index][target] != -1)
        return dp[index][target];

    bool notTake = equalMemo(index - 1, target, arr, dp);

    bool take = false;
    if (arr[index] <= target)
        take = equalMemo(index - 1, target - arr[index], arr, dp);

    return dp[index][target] = take || notTake;
}

bool canPartitionMemo(vector<int> &arr) {
    int n = arr.size();
    int totalSum = 0;

    for (int i = 0; i < n; i++)
        totalSum += arr[i];

    if (totalSum % 2 != 0)
        return false;

    int target = totalSum / 2;

    vector<vector<int>> dp(n, vector<int>(target + 1, -1));

    return equalMemo(n - 1, target, arr, dp);
}

// ---------- Tabulation ----------
// TC: O(n * target), SC: O(n * target)
bool canPartitionTab(vector<int> &arr) {
    int n = arr.size();
    int totalSum = 0;

    for (int i = 0; i < n; i++)
        totalSum += arr[i];

    if (totalSum % 2 != 0)
        return false;

    int target = totalSum / 2;

    vector<vector<bool>> dp(n, vector<bool>(target + 1, false));

    for (int i = 0; i < n; i++)
        dp[i][0] = true;

    if (arr[0] <= target)
        dp[0][arr[0]] = true;

    for (int i = 1; i < n; i++) {
        for (int tar = 1; tar <= target; tar++) {

            bool notTake = dp[i - 1][tar];

            bool take = false;
            if (arr[i] <= tar)
                take = dp[i - 1][tar - arr[i]];

            dp[i][tar] = take || notTake;
        }
    }

    return dp[n - 1][target];
}

// ---------- Space Optimization ----------
// TC: O(n * target), SC: O(target)
bool canPartitionSpace(vector<int> &arr) {
    int n = arr.size();
    int totalSum = 0;

    for (int i = 0; i < n; i++)
        totalSum += arr[i];

    if (totalSum % 2 != 0)
        return false;

    int target = totalSum / 2;

    vector<bool> prev(target + 1, false);
    vector<bool> curr(target + 1, false);

    prev[0] = true;
    curr[0] = true;

    if (arr[0] <= target)
        prev[arr[0]] = true;

    for (int i = 1; i < n; i++) {
        for (int tar = 1; tar <= target; tar++) {

            bool notTake = prev[tar];

            bool take = false;
            if (arr[i] <= tar)
                take = prev[tar - arr[i]];

            curr[tar] = take || notTake;
        }

        prev = curr;
    }

    return prev[target];
}

// MAIN
int main() {
    vector<int> arr = {1, 5, 11, 5};

    cout << "APPROACH 1: MINIMUM DIFFERENCE\n";
    cout << "Recursion: " << minDifferenceRec(arr) << endl;
    cout << "Memoization: " << minDifferenceMemo(arr) << endl;
    cout << "Tabulation: " << minDifferenceTab(arr) << endl;
    cout << "Space Optimization: " << minDifferenceSpace(arr) << endl;

    cout << "\nAPPROACH 2: EQUAL PARTITION\n";
    cout << "Recursion: " << canPartitionRec(arr) << endl;
    cout << "Memoization: " << canPartitionMemo(arr) << endl;
    cout << "Tabulation: " << canPartitionTab(arr) << endl;
    cout << "Space Optimization: " << canPartitionSpace(arr) << endl;

    return 0;
}
