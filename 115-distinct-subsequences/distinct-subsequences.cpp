#include <string>
#include <vector>

class Solution {
public:
    int numDistinct(std::string s, std::string t) {
        int m = s.length();
        int n = t.length();

        if (m < n) return 0;


        std::vector<unsigned long long> dp(n + 1, 0);
        dp[0] = 1;

        for (int i = 1; i <= m; ++i) {
            for (int j = n; j >= 1; --j) {
                if (s[i - 1] == t[j - 1]) {
                    dp[j] += dp[j - 1];
                }
            }
        }

        return static_cast<int>(dp[n]);
    }
};