class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        int n = points.size();

        if (n <= 2)
            return n;

        int ans = 0;

        for (int i = 0; i < n; i++) {
            unordered_map<string, int> slopeCnt;
            int samePt = 0;
            int localMax = 0;

            for (int j = i + 1; j < n; j++) {
                int dx = points[j][0] - points[i][0];
                int dy = points[j][1] - points[i][1];

                // Duplicate point
                if (dx == 0 && dy == 0) {
                    samePt++;
                    continue;
                }

                // Normalize vertical/horizontal/general slopes
                if (dx == 0) {
                    dy = 1;
                } else if (dy == 0) {
                    dx = 1;
                } else {
                    int g = gcd(abs(dx), abs(dy));
                    dx /= g;
                    dy /= g;

                    // Keep dx positive
                    if (dx < 0) {
                        dx = -dx;
                        dy = -dy;
                    }
                }

                string key = to_string(dy) + "_" + to_string(dx);

                slopeCnt[key]++;
                localMax = max(localMax, slopeCnt[key]);
            }

            // +1 for points[i], +samePt for duplicates
            ans = max(ans, localMax + samePt + 1);
        }

        return ans;
    }
};