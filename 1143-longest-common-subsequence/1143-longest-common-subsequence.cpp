#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// Recursion => TC: O(2^n * 2^m), SC: O(n + m)
int solveRec(string &s1, string &s2, int i, int j) {
    if (i < 0 || j < 0) {
        return 0;
    }

    if (s1[i] == s2[j]) {
        return 1 + solveRec(s1, s2, i - 1, j - 1);
    } else {
        int sub1 = solveRec(s1, s2, i - 1, j);
        int sub2 = solveRec(s1, s2, i, j - 1);

        return max(sub1, sub2);
    }
}

int longestCommonSubsequenceRec(string text1, string text2) {
    int n = text1.size();
    int m = text2.size();

    return solveRec(text1, text2, n - 1, m - 1);
}

// Memoization => TC: O(n * m), SC: O(n * m) + O(n + m)
int solveMemo(string &s1, string &s2, int i, int j, vector<vector<int>> &dp) {
    if (i < 0 || j < 0) {
        return 0;
    }
    if (dp[i][j] != -1) {
        return dp[i][j];
    }

    if (s1[i] == s2[j]) {
        return 1 + solveMemo(s1, s2, i - 1, j - 1, dp);
    } else {
        int sub1 = solveMemo(s1, s2, i - 1, j, dp);
        int sub2 = solveMemo(s1, s2, i, j - 1, dp);

        return dp[i][j] = max(sub1, sub2);
    }
}

int longestCommonSubsequenceMemo(string text1, string text2) {
    int n = text1.size();
    int m = text2.size();

    vector<vector<int>> dp(n, vector<int>(m, -1));
    return solveMemo(text1, text2, n - 1, m - 1, dp);
}

// Tabulation => TC: O(n * m), SC: O(n * m)
int longestCommonSubsequenceTab(string text1, string text2) {
    int n = text1.size();
    int m = text2.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 0; i <= n; i++) {
        dp[i][0] = 0;
    }
    for (int j = 0; j <= m; j++) {
        dp[0][j] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {

            if (text1[i - 1] == text2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[n][m];
}

// Space Optimization => TC: O(n * m), SC: O(2 * m)
int longestCommonSubsequenceSpace(string text1, string text2) {
    int n = text1.size();
    int m = text2.size();

    vector<int> prev(m + 1, 0), curr(m + 1, 0);

    for (int j = 0; j <= m; j++) {
        prev[j] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {

            if (text1[i - 1] == text2[j - 1]) {
                curr[j] = 1 + prev[j - 1];
            } else {
                curr[j] = max(prev[j], curr[j - 1]);
            }
        }
        prev = curr;
    }
    return prev[m];
}

// Two Vectors => One Vector
// TC: O(n * m), SC: O(m)
int longestCommonSubsequenceOneVector(string text1, string text2) {
    int n = text1.size();
    int m = text2.size();

    vector<int> prev(m + 1, 0);

    for (int j = 0; j <= m; j++) {
        prev[j] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {

            if (text1[i - 1] == text2[j - 1]) {
                prev[j] = 1 + prev[j - 1];
            } else {
                prev[j] = max(prev[j], prev[j - 1]);
            }
        }
    }
    return prev[m];
}

int main() {
    vector<int> text1 = "abcde";
    vector<int> text2 = "ace";

    cout << "Longest Common Subsequence (Recursion): "
         << longestCommonSubsequenceRec(text1, text2) << endl;

    cout << "Longest Common Subsequence (Memoization): "
         << longestCommonSubsequenceMemo(text1, text2) << endl;

    cout << "Longest Common Subsequence (Tabulation): "
         << longestCommonSubsequenceTab(text1, text2) << endl;

    cout << "Longest Common Subsequence (Space Optimization): "
         << longestCommonSubsequenceSpace(text1, text2) << endl;

    cout << "Longest Common Subsequence (One Vector): "
         << longestCommonSubsequenceOneVector(text1, text2) << endl;

    return 0;
}
