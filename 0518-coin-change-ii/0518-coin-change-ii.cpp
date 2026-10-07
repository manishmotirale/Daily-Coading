class Solution {
public:
    int change(int amount, vector<int>& coins) {
        int n = coins.size();

        vector<long long> prev(amount + 1, 0);
        vector<long long> curr(amount + 1, 0);

        for (int tar = 0; tar <= amount; tar++) {
            if (tar % coins[0] == 0) {
                prev[tar] = 1;
            }
        }

        for (int i = 1; i < n; i++) {
            for (int tar = 0; tar <= amount; tar++) {

                long long notTake = prev[tar];
                long long take = 0;

                if (coins[i] <= tar) {
                    take = curr[tar - coins[i]];
                }

                if (take > INT_MAX - notTake)
                    curr[tar] = INT_MAX;
                else
                    curr[tar] = take + notTake;
            }

            prev = curr;
        }

        return (int)prev[amount];
    }
};