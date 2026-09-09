class Solution {
public:
    long long countCommas(long long n) {
        long long totalCommas = 0;
        long long threshold = 1000LL;

        // Up to 10^15 per the constraints
        while (threshold <= n) {
            totalCommas += (n - threshold + 1);
            if (threshold > 1000000000000000LL / 1000LL) {
                break; // Prevent 64-bit signed integer overflow
            }
            threshold *= 1000LL;
        }

        return totalCommas;
    }
};