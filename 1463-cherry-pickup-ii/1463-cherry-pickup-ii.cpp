#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// Recursion => TC = O(2^N), SC = O(N)
int solveRec(int i, int j1, int j2, vector<vector<int>> &grid) {
    int n = grid.size(), m = grid[0].size();
    if (j1 < 0 || j1 >= m || j2 < 0 || j2 >= m) {
        return -1e9;
    }
    if (i == n - 1) {
        if (j1 == j2)
            return grid[i][j1];
        else
            return grid[i][j1] + grid[i][j2];
    }

    int maxi = -1e9;

    for (int dj1 = -1; dj1 <= 1; dj1++) {
        for (int dj2 = -1; dj2 <= 1; dj2++) {

            int value;

            if (j1 == j2) {
                value = grid[i][j1] + solveRec(i + 1, j1 + dj1, j2 + dj2, grid);
            } else {
                value = grid[i][j1] + grid[i][j2] +
                        solveRec(i + 1, j1 + dj1, j2 + dj2, grid);
            }

            maxi = max(maxi, value);
        }
    }

    return maxi;
}

int cherryPickupRec(vector<vector<int>> &grid) {
    return solveRec(0, 0, grid[0].size() - 1, grid);
}

// Memoization => TC = O(N*M*M*9), SC = O(N*M*M) + O(N)
int solveMemo(int i, int j1, int j2, vector<vector<int>> &grid,
              vector<vector<vector<int>>> &dp) {

    int n = grid.size();
    int m = grid[0].size();

    if (j1 < 0 || j1 >= m || j2 < 0 || j2 >= m) {
        return -1e9;
    }

    if (i == n - 1) {
        if (j1 == j2)
            return grid[i][j1];

        return grid[i][j1] + grid[i][j2];
    }

    if (dp[i][j1][j2] != -1)
        return dp[i][j1][j2];

    int maxi = -1e9;

    for (int dj1 = -1; dj1 <= 1; dj1++) {
        for (int dj2 = -1; dj2 <= 1; dj2++) {

            int value;

            if (j1 == j2) {
                value = grid[i][j1] +
                        solveMemo(i + 1, j1 + dj1, j2 + dj2, grid, dp);
            } else {
                value = grid[i][j1] + grid[i][j2] +
                        solveMemo(i + 1, j1 + dj1, j2 + dj2, grid, dp);
            }

            maxi = max(maxi, value);
        }
    }

    return dp[i][j1][j2] = maxi;
}

int cherryPickupMemo(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();

    vector<vector<vector<int>>> dp(n,
                                   vector<vector<int>>(m, vector<int>(m, -1)));

    return solveMemo(0, 0, m - 1, grid, dp);
}

// Tabulation => TC = O(N*M*M*9), SC = O(N*M*M)
int cherryPickupTab(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();

    vector<vector<vector<int>>> dp(n,
                                   vector<vector<int>>(m, vector<int>(m, 0)));

    for (int j1 = 0; j1 < m; j1++) {
        for (int j2 = 0; j2 < m; j2++) {
            if (j1 == j2)
                dp[n - 1][j1][j2] = grid[n - 1][j1];
            else
                dp[n - 1][j1][j2] = grid[n - 1][j1] + grid[n - 1][j2];
        }
    }

    for (int i = n - 2; i >= 0; i--) {
        for (int j1 = 0; j1 < m; j1++) {
            for (int j2 = 0; j2 < m; j2++) {

                int maxi = -1e9;

                for (int dj1 = -1; dj1 <= 1; dj1++) {
                    for (int dj2 = -1; dj2 <= 1; dj2++) {
                        int nextJ1 = j1 + dj1;
                        int nextJ2 = j2 + dj2;

                        if (nextJ1 < 0 || nextJ1 >= m || nextJ2 < 0 ||
                            nextJ2 >= m)
                            continue;

                        int value;

                        if (j1 == j2) {
                            value = grid[i][j1] + dp[i + 1][nextJ1][nextJ2];
                        } else {
                            value = grid[i][j1] + grid[i][j2] +
                                    dp[i + 1][nextJ1][nextJ2];
                        }

                        maxi = max(maxi, value);
                    }
                }

                dp[i][j1][j2] = maxi;
            }
        }
    }

    return dp[0][0][m - 1];
}

// Space Optimization => TC = O(N*M*M*9), SC = O(M*M)
int cherryPickupSO(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();

    vector<vector<int>> front(m, vector<int>(m, 0));
    vector<vector<int>> curr(m, vector<int>(m, 0));

    for (int j1 = 0; j1 < m; j1++) {
        for (int j2 = 0; j2 < m; j2++) {
            if (j1 == j2)
                front[j1][j2] = grid[n - 1][j1];
            else
                front[j1][j2] = grid[n - 1][j1] + grid[n - 1][j2];
        }
    }

    for (int i = n - 2; i >= 0; i--) {
        for (int j1 = 0; j1 < m; j1++) {
            for (int j2 = 0; j2 < m; j2++) {

                int maxi = -1e9;

                for (int dj1 = -1; dj1 <= 1; dj1++) {
                    for (int dj2 = -1; dj2 <= 1; dj2++) {
                        int nextJ1 = j1 + dj1;
                        int nextJ2 = j2 + dj2;

                        if (nextJ1 < 0 || nextJ1 >= m || nextJ2 < 0 ||
                            nextJ2 >= m)
                            continue;

                        int value;

                        if (j1 == j2) {
                            value = grid[i][j1] + front[nextJ1][nextJ2];
                        } else {
                            value = grid[i][j1] + grid[i][j2] +
                                    front[nextJ1][nextJ2];
                        }

                        maxi = max(maxi, value);
                    }
                }

                curr[j1][j2] = maxi;
            }
        }
        front = curr;
    }

    return front[0][m - 1];
}

int main() {
    vector<vector<int>> grid = {{3, 1, 1}, {2, 5, 1}, {1, 5, 5}, {2, 1, 1}};
    cout << "Maximum cherries collected (Recursion): " << cherryPickupRec(grid)
         << endl;
    cout << "Maximum cherries collected (Memoization): "
         << cherryPickupMemo(grid) << endl;
    cout << "Maximum cherries collected (Tabulation): " << cherryPickupTab(grid)
         << endl;
    cout << "Maximum cherries collected (Space Optimization): "
         << cherryPickupSO(grid) << endl;
    return 0;
}
