#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// Recursion => TC: O(2^(n*m)) SC: O(n+m) -> recursion stack

int solveRec(int i, int j, vector<vector<int>> &triangle) {
    if (i == triangle.size() - 1) {
        return triangle[i][j];
    }

    int down = solveRec(i + 1, j, triangle);
    int dia = solveRec(i + 1, j + 1, triangle);

    return triangle[i][j] + min(down, dia);
}

int minimumTotalRec(vector<vector<int>> &triangle) {
    return solveRec(0, 0, triangle);
}

// Memoization => TC: O(n*m) SC: O(n*m) + O(n+m)
int solveMemo(int i, int j, vector<vector<int>> &triangle,
              vector<vector<int>> &dp) {
    if (i == triangle.size() - 1) {
        return triangle[i][j];
    }

    if (dp[i][j] != -1)
        return dp[i][j];

    int down = solveMemo(i + 1, j, triangle, dp);
    int dia = solveMemo(i + 1, j + 1, triangle, dp);

    return dp[i][j] = triangle[i][j] + min(down, dia);
}

int minimumTotalMemo(vector<vector<int>> &triangle) {
    int n = triangle.size();

    vector<vector<int>> dp(n, vector<int>(n, -1));
    return solveMemo(0, 0, triangle, dp);
}

// Tabulation => TC: O(n*m) SC: O(n*m)
int minimumTotalTab(vector<vector<int>> &triangle) {
    int n = triangle.size();

    vector<vector<int>> dp(n, vector<int>(n, 0));

    // Copy the last row
    for (int j = 0; j < n; j++) {
        dp[n - 1][j] = triangle[n - 1][j];
    }

    // Bottom-up
    for (int i = n - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            dp[i][j] = triangle[i][j] + min(dp[i + 1][j], dp[i + 1][j + 1]);
        }
    }

    return dp[0][0];
}

// Space Optimization => TC: O(n*m) SC: O(m)
int minimumTotalSpa ceOpt(vector<vector<int>> &triangle) {
    int n = triangle.size();

    vector<int> front(n, 0), curr(n, 0);

    // Copy the last row
    for (int j = 0; j < n; j++) {
        front[j] = triangle[n - 1][j];
    }

    // Bottom-up
    for (int i = n - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            curr[j] = triangle[i][j] + min(front[j], front[j + 1]);
        }
        front = curr;
    } 
 
    return front[0];
}

int main() {
    vector<vector<int>> triangle = {{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}};

    cout << "Minimum Path Sum (Recursion): " << minimumTotalRec(triangle)
         << endl;
    cout << "Minimum Path Sum (Memoization): " << minimumTotalMemo(triangle)
         << endl;
    cout << "Minimum Path Sum (Tabulation): " << minimumTotalTab(triangle)
         << endl;
    cout << "Minimum Path Sum (Space Optimization): "
         << minimumTotalSpaceOpt(triangle) << endl;

    return 0;
}
