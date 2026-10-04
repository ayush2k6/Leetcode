class Solution {
public:
    bool checkValidString(string s) {
        int cmin = 0; // Minimum possible open parentheses count
        int cmax = 0; // Maximum possible open parentheses count

        for (char c : s) {
            if (c == '(') {
                cmin++;
                cmax++;
            } else if (c == ')') {
                cmin--;
                cmax--;
            } else if (c == '*') {
                cmin--; // Treat '*' as ')'
                cmax++; // Treat '*' as '('
            }

            // More ')' than '(' even if all '*' were '('
            if (cmax < 0) {
                return false;
            }

            // cmin cannot be negative; '*' can always be empty string ""
            if (cmin < 0) {
                cmin = 0;
            }
        }

        return cmin == 0;
    }
};