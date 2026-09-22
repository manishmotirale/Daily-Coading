#include <climits>
#include <iostream>
#include <vector>
using namespace std;

// Recursion => TC: O(2^(n+m)) SC: O(n+m) -> recursion stack
int solveRec(int i, int j, vector<vector<int>> &grid) {

    // Starting cell
    if (i == 0 && j == 0)
        return grid[0][0];

    // Invalid path
    if (i < 0 || j < 0)
        return 1e9;

    // Move Up
    int up = solveRec(i - 1, j, grid);

    // Move Left
    int left = solveRec(i, j - 1, grid);

    // Current cell + minimum path
    return grid[i][j] + min(up, left);
}

int minPathSumRec(vector<vector<int>> &grid) {

    int n = grid.size();
    int m = grid[0].size();

    return solveRec(n - 1, m - 1, grid);
}

// Memoization => TC: O(n*m) SC: O(n*m) + O(n+m)
int solveMemo(int i, int j, vector<vector<int>> &grid,
              vector<vector<int>> &dp) {

    // Starting cell
    if (i == 0 && j == 0)
        return grid[0][0];

    // Invalid path
    if (i < 0 || j < 0)
        return 1e9;

    // Already calculated
    if (dp[i][j] != -1)
        return dp[i][j];

    // Move Up
    int up = solveMemo(i - 1, j, grid, dp);

    // Move Left
    int left = solveMemo(i, j - 1, grid, dp);

    // Store answer
    return dp[i][j] = grid[i][j] + min(up, left);
}

int minPathSumMemo(vector<vector<int>> &grid) {

    int n = grid.size();
    int m = grid[0].size();

    vector<vector<int>> dp(n, vector<int>(m, -1));

    return solveMemo(n - 1, m - 1, grid, dp);
}

// Tabulation => TC: O(n*m) SC: O(n*m)
int minPathSumTab(vector<vector<int>> &grid) {

    int n = grid.size();
    int m = grid[0].size();

    vector<vector<int>> dp(n, vector<int>(m, 0));

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < m; j++) {

            if (i == 0 && j == 0) {
                dp[i][j] = grid[i][j];
                continue;
            }

            int up = 1e9;
            if (i > 0)
                up = dp[i - 1][j];

            int left = 1e9;
            if (j > 0)
                left = dp[i][j - 1];

            dp[i][j] = grid[i][j] + min(up, left);
        }
    }

    return dp[n - 1][m - 1];
}

// Space Optimization => TC: O(n*m) SC: O(m)
int minPathSumSpaceOpt(vector<vector<int>> &grid) {

    int n = grid.size();
    int m = grid[0].size();

    // Stores previous row
    vector<int> prev(m, 0);

    for (int i = 0; i < n; i++) {
        // Stores current row
        vector<int> curr(m, 0);
        for (int j = 0; j < m; j++) {

            // Starting cell
            if (i == 0 && j == 0) {
                curr[j] = grid[i][j];
                continue;
            }

            // From Up
            int up = 1e9;
            if (i > 0)
                up = prev[j];

            // From Left
            int left = 1e9;
            if (j > 0)
                left = curr[j - 1];

            // Current cell + minimum previous path
            curr[j] = grid[i][j] + min(up, left);
        }

        // Current row becomes previous row
        prev = curr;
    }

    return prev[m - 1];
}

int main() {

    vector<vector<int>> grid = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};

    cout << "Minimum Path Sum (Recursion): " << minPathSumRec(grid) << endl;

    cout << "Minimum Path Sum (Memoization): " << minPathSumMemo(grid) << endl;

    cout << "Minimum Path Sum (Tabulation): " << minPathSumTab(grid) << endl;

    cout << "Minimum Path Sum (Space Optimization): "
         << minPathSumSpaceOpt(grid) << endl;

    return 0;
}
