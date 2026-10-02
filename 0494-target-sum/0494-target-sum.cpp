#include <iostream>
#include <vector>
using namespace std;

// Function to count the number of subsets with a given difference

// Recursion => TC: O(2^N)  SC: O(N)
int mod = 1e9 + 7;

int findWaysRec(int i, int tar, vector<int> &arr) {
    if (i == 0) {
        if (tar == 0 && arr[0] == 0)
            return 2;

        if (tar == 0 || tar == arr[0])
            return 1;

        return 0;
    }

    int notTake = findWaysRec(i - 1, tar, arr);

    int take = 0;
    if (arr[i] <= tar)
        take = findWaysRec(i - 1, tar - arr[i], arr);

    return (notTake + take) % mod;
}

int countPartitionsRec(vector<int> &arr, int diff) {
    int totalSum = 0;

    for (auto &it : arr)
        totalSum += it;

    if (totalSum - diff < 0 || (totalSum - diff) % 2)
        return 0;

    int tar = (totalSum - diff) / 2;
    int n = arr.size();

    return findWaysRec(n - 1, tar, arr);
}

// Memoization => TC: O(N * tar)  SC: O(N * tar) + O(N)
int findWaysMemo(int i, int tar, vector<int> &arr, vector<vector<int>> &dp) {
    if (i == 0) {
        if (tar == 0 && arr[0] == 0)
            return 2;

        if (tar == 0 || tar == arr[0])
            return 1;

        return 0;
    }

    if (dp[i][tar] != -1)
        return dp[i][tar];

    int notTake = findWaysMemo(i - 1, tar, arr, dp);

    int take = 0;
    if (arr[i] <= tar)
        take = findWaysMemo(i - 1, tar - arr[i], arr, dp);

    return dp[i][tar] = (notTake + take) % mod;
}

int countPartitionsMemo(vector<int> &arr, int diff) {
    int totalSum = 0;

    for (auto &it : arr)
        totalSum += it;

    if (totalSum - diff < 0 || (totalSum - diff) % 2)
        return 0;

    int tar = (totalSum - diff) / 2;
    int n = arr.size();

    vector<vector<int>> dp(n, vector<int>(tar + 1, -1));

    return findWaysMemo(n - 1, tar, arr, dp);
}

// Tabulation => TC: O(N * tar)  SC: O(N * tar)
int countPartitionsTab(vector<int> &arr, int diff) {
    int totalSum = 0;

    for (auto &it : arr)
        totalSum += it;

    if (totalSum - diff < 0 || (totalSum - diff) % 2)
        return 0;

    int tar = (totalSum - diff) / 2;
    int n = arr.size();

    vector<vector<int>> dp(n, vector<int>(tar + 1, 0));

    if (arr[0] == 0)
        dp[0][0] = 2;
    else
        dp[0][0] = 1;

    if (arr[0] != 0 && arr[0] <= tar)
        dp[0][arr[0]] = 1;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= tar; j++) {
            int notTake = dp[i - 1][j];

            int take = 0;
            if (arr[i] <= j)
                take = dp[i - 1][j - arr[i]];

            dp[i][j] = (notTake + take) % mod;
        }
    }

    return dp[n - 1][tar];
}

// Space Optimization => TC: O(N * tar)  SC: O(tar)
int countPartitionsSO(vector<int> &arr, int diff) {
    int totalSum = 0;

    for (auto &it : arr)
        totalSum += it;

    if (totalSum - diff < 0 || (totalSum - diff) % 2)
        return 0;

    int tar = (totalSum - diff) / 2;
    int n = arr.size();

    vector<int> prev(tar + 1, 0), curr(tar + 1, 0);

    if (arr[0] == 0)
        prev[0] = 2;
    else
        prev[0] = 1;

    if (arr[0] != 0 && arr[0] <= tar)
        prev[arr[0]] = 1;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= tar; j++) {
            int notTake = prev[j];

            int take = 0;
            if (arr[i] <= j)
                take = prev[j - arr[i]];

            curr[j] = (notTake + take) % mod;
        }
        prev = curr;
    }

    return prev[tar];
}

int main() {
    vector<int> arr = {1, 2, 3, 4};
    int diff = 3;

    cout << countPartitionsRec(arr, diff) << endl;
    cout << countPartitionsMemo(arr, diff) << endl;
    cout << countPartitionsTab(arr, diff) << endl;
    cout << countPartitionsSO(arr, diff) << endl;
}
