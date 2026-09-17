class Solution {
public:
    vector<int> grayCode(int n) {
        if (n == 0) return {0};
        
        // Get the sequence for n-1
        vector<int> prev = grayCode(n - 1);
        int offset = 1 << (n - 1); // 2^(n-1)
        vector<int> res = prev;
        
        // Append the reversed prev sequence with the offset added
        for (int i = prev.size() - 1; i >= 0; --i) {
            res.push_back(prev[i] + offset);
        }
        
        return res;
    }
};