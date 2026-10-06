#include <iostream>
#include <vector>
using namespace std;

// Recursion => TC: O(2^N) SC: O(N)
// recursion stack
int findWaysRec(vector<int> &arr, int i, int tar) {

    if (i == 0) {
        if (arr[0] == 0 && tar == 0)
            return 2;

        if (tar == 0 || tar == arr[0])
            return 1;

        return 0;
    }

    int notTake = findWaysRec(arr, i - 1, tar);
    int take = 0;

    if (arr[i] <= tar)
        take = findWaysRec(arr, i - 1, tar - arr[i]);

    return notTake + take;
}

int totalWaysRec(vector<int> &arr, int target) {
    int totalSum = 0;

    for (auto &it : arr)
        totalSum += it;

    if (totalSum - target < 0 || (totalSum - target) % 2)
        return 0;

    int tar = (totalSum - target) / 2;

    return findWaysRec(arr, arr.size() - 1, tar);
}

// Memoization => TC: O(N*tar) SC: O(N*tar) + O(N)

int findWaysMemo(vector<int> &arr, int i, int tar, vector<vector<int>> &dp) {

    if (i == 0) {
        if (arr[0] == 0 && tar == 0)
            return 2;

        if (tar == 0 || tar == arr[0])
            return 1;

        return 0;
    }

    if (dp[i][tar] != -1)
        return dp[i][tar];

    int notTake = findWaysMemo(arr, i - 1, tar, dp);
    int take = 0;

    if (arr[i] <= tar)
        take = findWaysMemo(arr, i - 1, tar - arr[i], dp);

    return dp[i][tar] = notTake + take;
}

int totalWaysMemo(vector<int> &arr, int target) {
    int totalSum = 0;

    for (auto &it : arr)
        totalSum += it;

    if (totalSum - target < 0 || (totalSum - target) % 2)
        return 0;

    int tar = (totalSum - target) / 2;

    vector<vector<int>> dp(arr.size(), vector<int>(tar + 1, -1));

    return findWaysMemo(arr, arr.size() - 1, tar, dp);
}

// Tabulation => TC: O(N*tar) SC: O(N*tar)

int totalWaysTab(vector<int> &arr, int target) {
    int n = arr.size();
    int totalSum = 0;

    for (auto &it : arr)
        totalSum += it;

    if (totalSum - target < 0 || (totalSum - target) % 2)
        return 0;

    int tar = (totalSum - target) / 2;

    vector<vector<int>> dp(n, vector<int>(tar + 1, 0));

    // Base case
    if (arr[0] == 0)
        dp[0][0] = 2;
    else
        dp[0][0] = 1;

    if (arr[0] != 0 && arr[0] <= tar)
        dp[0][arr[0]] = 1;

    // DP
    for (int i = 1; i < n; i++) {
        for (int sum = 0; sum <= tar; sum++) {

            int notTake = dp[i - 1][sum];
            int take = 0;

            if (arr[i] <= sum)
                take = dp[i - 1][sum - arr[i]];

            dp[i][sum] = notTake + take;
        }
    }

    return dp[n - 1][tar];
}

// Space Optimization => TC: O(N*tar) SC: O(tar)
int totalWaysSpace(vector<int> &arr, int target) {
    int n = arr.size();
    int totalSum = 0;

    for (auto &it : arr)
        totalSum += it;

    if (totalSum - target < 0 || (totalSum - target) % 2)
        return 0;

    int tar = (totalSum - target) / 2;

    vector<int> prev(tar + 1, 0), curr(tar + 1, 0);

    // Base case
    if (arr[0] == 0)
        prev[0] = 2;
    else
        prev[0] = 1;

    if (arr[0] != 0 && arr[0] <= tar)
        prev[arr[0]] = 1;

    // DP
    for (int i = 1; i < n; i++) {
        for (int sum = 0; sum <= tar; sum++) {

            int notTake = prev[sum];
            int take = 0;

            if (arr[i] <= sum)
                take = prev[sum - arr[i]];

            curr[sum] = notTake + take;
        }
        prev = curr;
    }

    return prev[tar];
}

int main() {
    vector<int> arr = {1, 1, 2, 3};
    int target = 1;

    cout << "Total ways (Recursion): " << totalWaysRec(arr, target) << endl;

    cout << "Total ways (Memoization): " << totalWaysMemo(arr, target) << endl;

    cout << "Total ways (Tabulation): " << totalWaysTab(arr, target) << endl;

    cout << "Total ways (Space Optimization): " << totalWaysSpace(arr, target)
         << endl;

    return 0;
}
