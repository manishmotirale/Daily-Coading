#include <iostream>
#include <vector>
using namespace std;

// Recursion => TC: O(2^(m*n)), SC: O(m+n)
int solve(vector<vector<int>> &grid, int i, int j) {
    if (i == 0 || j == 0)
        return 1;
    if (i >= 0 && j >= 0 && grid[i][j] == -1)
        return 0;
    if (i < 0 || j < 0)
        return 0;

    return solve(grid, i - 1, j) + solve(grid, i, j - 1);
}
int uniquePathsRec(vector<vector<int>> &grid) {
    int m = grid.size();
    int n = grid[0].size();

    return solve(grid, m - 1, n - 1);
}

// Memoization => TC: O(m*n), SC: O(m*n) + O(m+n)
int solve(vector<vector<int>> &grid, int i, int j, vector<vector<int>> &dp) {
    if (i == 0 || j == 0)
        return 1;
    if (i >= 0 && j >= 0 && grid[i][j] == -1)
        return 0;
    if (i < 0 || j < 0)
        return 0;

    if (dp[i][j] != -1)
        return dp[i][j];

    return dp[i][j] = solve(grid, i - 1, j) + solve(grid, i, j - 1);
}
int uniquePathsMemo(vector<vector<int>> &grid) {
    int m = grid.size();
    int n = grid[0].size();

    vector<vector<int>> dp(m, vector<int>(n, -1));

    return solve(grid, m - 1, n - 1, dp);
}

// Tabulation => TC: O(m*n), SC: O(m*n)
int uniquePathsTab(vector<vector<int>> &grid) {
    int m = grid.size();
    int n = grid[0].size();

    vector<vector<int>> dp(m, vector<int>(n, 0));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            // Obstacle
            if (grid[i][j] == 1) {
                dp[i][j] = 0;
            }
            // Starting cell
            else if (i == 0 && j == 0) {
                dp[i][j] = 1;
            } else {
                if (i > 0)
                    dp[i][j] += dp[i - 1][j];

                if (j > 0)
                    dp[i][j] += dp[i][j - 1];
            }
        }
    }

    return dp[m - 1][n - 1];
}

// Space Optimization => TC: O(m*n), SC: O(n)
int uniquePathsSpace(vector<vector<int>> &grid) {
    int m = grid.size();
    int n = grid[0].size();

    vector<int> prev(n, 0);

    for (int i = 0; i < grid.size(); i++) {
        vector<int> curr(n, 0);
        for (int j = 0; j < grid[0].size(); j++) {
            if (i == 0 && j == 0)
                curr[j] = 1;
            else if (grid[i][j] == -1)
                curr[j] = 0;
            else {
                int up = 0, left = 0;
                if (i > 0)
                    up = prev[j];
                if (j > 0)
                    left = curr[j - 1];
                curr[j] = up + left;
            }
        }
        prev = curr;
    }
    return prev[n - 1];
}

int main() {
    vector<vector<int>> grid = {{0, 0, 0}, {0, -1, 0}, {0, 0, 0}};

    cout << uniquePathsSpace(grid) << endl;
    cout << uniquePathsRec(grid) << endl;
    cout << uniquePathsMemo(grid) << endl;
    cout << uniquePathsTab(grid) << endl;
    return 0;
}
