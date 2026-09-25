#include <iostream>
#include <vector>
using namespace std;

// Recursion => TC: O(3^(n * m)) SC: O(n)
int solveRec(int i, int j, vector<vector<int>> &matrix) {
    int m = matrix[0].size();

    // Invalid column
    if (j < 0 || j >= m)
        return 1e9;

    // First row
    if (i == 0)
        return matrix[i][j];

    int up = solveRec(i - 1, j, matrix);
    int ld = solveRec(i - 1, j - 1, matrix);
    int rd = solveRec(i - 1, j + 1, matrix);

    return matrix[i][j] + min(up, min(ld, rd));
}

int minFallingPathSumRec(vector<vector<int>> &matrix) {
    int n = matrix.size();
    int m = matrix[0].size();

    int curr = 1e9;

    // End at every cell in the last row
    for (int j = 0; j < m; j++) {
        curr = min(curr, solveRec(n - 1, j, matrix));
    }

    return curr;
}

// Memoization => TC: O(n * m) SC: O(n * m)
int solveMem(int i, int j, vector<vector<int>> &matrix,
             vector<vector<int>> &dp) {
    int m = matrix[0].size();

    // Invalid column
    if (j < 0 || j >= m)
        return 1e9;

    // First row
    if (i == 0)
        return matrix[i][j];

    if (dp[i][j] != -1)
        return dp[i][j];

    int up = solveMem(i - 1, j, matrix, dp);
    int ld = solveMem(i - 1, j - 1, matrix, dp);
    int rd = solveMem(i - 1, j + 1, matrix, dp);

    return dp[i][j] = matrix[i][j] + min(up, min(ld, rd));
}

int minFallingPathSumMem(vector<vector<int>> &matrix) {
    int n = matrix.size();
    int m = matrix[0].size();

    vector<vector<int>> dp(n, vector<int>(m, -1));

    int curr = 1e9;

    // End at every cell in the last row
    for (int j = 0; j < m; j++) {
        curr = min(curr, solveMem(n - 1, j, matrix, dp));
    }

    return curr;
}

// Tabulation => TC: O(n * m) SC: O(n * m)
int minFallingPathSumTab(vector<vector<int>> &matrix) {
    int n = matrix.size();
    int m = matrix[0].size();

    vector<vector<int>> dp(n, vector<int>(m, 0));

    // First row
    for (int j = 0; j < m; j++) {
        dp[0][j] = matrix[0][j];
    }

    // Fill from top to bottom
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m; j++) {

            int up = dp[i - 1][j];

            int ld = 1e9;
            if (j - 1 >= 0) {
                ld = dp[i - 1][j - 1];
            }

            int rd = 1e9;
            if (j + 1 < m) {
                rd = dp[i - 1][j + 1];
            }

            dp[i][j] = matrix[i][j] + min(up, min(ld, rd));
        }
    }

    // Minimum value in the last row
    int ans = 1e9;

    for (int j = 0; j < m; j++) {
        ans = min(ans, dp[n - 1][j]);
    }

    return ans;
}

// Space Optimization => TC: O(n * m) SC: O(m)
int minFallingPathSumSpaceOpt(vector<vector<int>> &matrix) {
    int n = matrix.size();
    int m = matrix[0].size();

    vector<int> prev(m, 0);

    // First row
    for (int j = 0; j < m; j++) {
        prev[j] = matrix[0][j];
    }

    // Fill from top to bottom
    for (int i = 1; i < n; i++) {
        vector<int> curr(m, 0);
        for (int j = 0; j < m; j++) {

            int up = prev[j];

            int ld = 1e9;
            if (j - 1 >= 0) {
                ld = prev[j - 1];
            }

            int rd = 1e9;
            if (j + 1 < m) {
                rd = prev[j + 1];
            }

            curr[j] = matrix[i][j] + min(up, min(ld, rd));
        }
        prev = curr;
    }

    // Minimum value in the last row
    int ans = 1e9;

    for (int j = 0; j < m; j++) {
        ans = min(ans, prev[j]);
    }

    return ans;
}

int main() {
    vector<vector<int>> matrix = {{2, 1, 3}, {6, 5, 4}, {7, 8, 9}};

    cout << "Minimum Falling Path Sum (Recursion): "
         << minFallingPathSumRec(matrix) << endl;
    cout << "Minimum Falling Path Sum (Memoization): "
         << minFallingPathSumMem(matrix) << endl;
    cout << "Minimum Falling Path Sum (Tabulation): "
         << minFallingPathSumTab(matrix) << endl;
    cout << "Minimum Falling Path Sum (Space Optimization): "
         << minFallingPathSumSpaceOpt(matrix) << endl;

    return 0;
}
