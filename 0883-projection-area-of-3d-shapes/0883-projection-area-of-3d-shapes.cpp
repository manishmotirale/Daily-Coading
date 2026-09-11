class Solution {
public:
    int projectionArea(vector<vector<int>>& grid) {
        int n = grid.size();
        int topArea = 0;
        int frontArea = 0;
        int sideArea = 0;

        for (int i = 0; i < n; ++i) {
            int maxRow = 0;
            int maxCol = 0;
            for (int j = 0; j < n; ++j) {
                // Top view: count non-zero cells
                if (grid[i][j] > 0) {
                    topArea++;
                }
                // Side view: max in row i
                maxRow = max(maxRow, grid[i][j]);
                // Front view: max in column j
                maxCol = max(maxCol, grid[j][i]);
            }
            sideArea += maxRow;
            frontArea += maxCol;
        }

        return topArea + frontArea + sideArea;
    }
};