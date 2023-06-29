#include <iostream>
#include <vector>

bool isMatch(const std::string& s, const std::string& p) {
    int m = s.length();
    int n = p.length();

    // Create a 2D table to store the matching results
    std::vector<std::vector<bool>> dp(m + 1, std::vector<bool>(n + 1, false));

    // An empty pattern matches an empty string
    dp[0][0] = true;

    // Handle patterns with '*' as the first character
    for (int j = 1; j <= n; j++) {
        if (p[j - 1] == '*') {
            dp[0][j] = dp[0][j - 2];
        }
    }

    // Fill the table based on the pattern and input string
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s[i - 1] == p[j - 1] || p[j - 1] == '.') {
                dp[i][j] = dp[i - 1][j - 1];
            } else if (p[j - 1] == '*') {
                dp[i][j] = dp[i][j - 2];
                if (p[j - 2] == '.' || p[j - 2] == s[i - 1]) {
                    dp[i][j] = dp[i][j] || dp[i - 1][j];
                }
            } else {
                dp[i][j] = false;
            }
        }
    }

    return dp[m][n];
}

int main() {
    std::string s = "aa";
    std::string p = "a";
    std::cout << std::boolalpha << isMatch(s, p) << std::endl;  // Output: false

    s = "aa";
    p = "a*";
    std::cout << std::boolalpha << isMatch(s, p) << std::endl;  // Output: true

    s = "ab";
    p = ".*";
    std::cout << std::boolalpha << isMatch(s, p) << std::endl;  // Output: true

    return 0;
}
