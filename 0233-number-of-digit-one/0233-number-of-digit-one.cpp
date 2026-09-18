class Solution {
public:
    int countDigitOne(int n) {
        long long ans = 0;
        for (long long m = 1; m <= n; m *= 10) {
            long long high = n / (m * 10);
            long long curr = (n / m) % 10;
            long long low = n % m;

            if (curr == 0) {
                ans += high * m;
            } else if (curr == 1) {
                ans += high * m + low + 1;
            } else {
                ans += (high + 1) * m;
            }
        }
        return (int)ans;
    }
};