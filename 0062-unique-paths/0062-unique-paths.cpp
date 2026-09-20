#include <iostream>
#include <vector>

using namespace std;

// Recursion => TC: O(2^m * 2^n), SC: O(m+n)
int solve(int i, int j) {
    if (i == 0 || j == 0)
        return 1;

    if (i < 0 || j < 0)
        return 0;

    int up = solve(i - 1, j);
    int left = solve(i, j - 1);

    return up + left;
}

int uniquePathsRecursively(int m, int n) { return solve(m - 1, n - 1); }

// Memoization => TC: O(m*n), SC: O(m*n) + O(m+n)
int solve(int i, int j, vector<vector<int>> &dp) {
    if (i == 0 || j == 0)
        return 1;

    if (i < 0 || j < 0)
        return 0;

    if (dp[i][j] != -1)
        return dp[i][j];

    int up = solve(i - 1, j, dp);
    int left = solve(i, j - 1, dp);

    return dp[i][j] = up + left;
}

int uniquePathsMemoized(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, -1));
    return solve(m - 1, n - 1, dp);
}

// Tabulation => TC: O(m*n), SC: O(m*n)
int uniquePathsTabulated(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, 0));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 1;
            else
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }

    return dp[m - 1][n - 1];
}

// Space Optimization => TC: O(m*n), SC: O(n)
int uniquePathsOptimized(int m, int n) {
    vector<int> prev(n, 0);

    for (int i = 0; i < m; i++) {
        vector<int> curr(n, 0);
        for (int j = 0; j < n; j++) {
            if (i == 0 || j == 0)
                curr[j] = 1;
            else
                curr[j] = prev[j] + curr[j - 1];
        }
        prev = curr;
    }

    return prev[n - 1];
}

int main() {
    int m, n;
    cout << "Enter the number of rows (m): ";
    cin >> m;
    cout << "Enter the number of columns (n): ";
    cin >> n;

    cout << "Unique Paths (Recursion): " << uniquePathsRecursively(m, n)
         << endl;
    cout << "Unique Paths (Memoization): " << uniquePathsMemoized(m, n) << endl;
    cout << "Unique Paths (Tabulation): " << uniquePathsTabulated(m, n) << endl;
    cout << "Unique Paths (Space Optimization): " << uniquePathsOptimized(m, n)
         << endl;
         
    return 0;
}
