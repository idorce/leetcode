#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 图、树、堆、栈、链表、哈希表、记忆搜索、动态规划、指针法、并查集等

class DP {
   public:
    // 5. Longest Palindromic Substring
    string longestPalindrome(string s) {
        // dp[i][j] == 1 means s[i:j+1] is palindromic.
        // dp[i][j] = dp[i + 1][j - 1] && s[i] == s[j],
        // dp[i][i + 1] = dp[i][i - 1] = 1.

        int tmp_len, max_len = 1, start_index = 0, i, j;
        vector<int> dp(s.size(), 1);
        for (i = s.size() - 2; i >= 0; --i) {
            for (j = s.size() - 1; j > i; --j) {
                dp[j] = dp[j - 1] && s[i] == s[j];
                // Check for longest.
                if (dp[j]) {
                    tmp_len = j - i + 1;
                    if (tmp_len > max_len) {
                        max_len = tmp_len;
                        start_index = i;
                    }
                }
            }
        }
        return s.substr(start_index, max_len);
    }

    // 10. Regular Expression Matching
    bool isMatch(string s, string p) {
        // dp[i][j] == 1 means s [0:i] matchs p [0:j].
        //
        //                    |-    dp[i][j - 2]                                              (zero) -|
        //             |- OR -|  |- dp[i - 1][j]                        , p[j - 2] == '.' -|          |- p[j - 1] == '*'
        // dp[i][j] = -|      |- |- dp[i - 1][j] && s[i - 1] == p[j - 2], p[j - 2] != '.' -|- (more) -|
        //             |- dp[i - 1][j - 1]                        ,                                      p[j - 1] == '.'
        //             |- dp[i - 1][j - 1] && s[i - 1] == p[j - 1],                                      p[j - 1] == 'a' to 'z' (p[j - 1] != '.')
        int i, j;
        vector<vector<bool>> dp(2, vector<bool>(p.size() + 1, false));
        // First column all false, since empty p does not match non-empty s.
        dp[0][0] = true;  // When s and p are both empty, true.
        // First row is NOT all true: p matchs empty s iff
        for (j = 2; j <= p.size(); ++j)
            dp[0][j] = p[j - 1] == '*' && dp[0][j - 2];
        for (i = 1; i <= s.size(); ++i) {
            for (j = 1; j <= p.size(); ++j) {
                if (p[j - 1] != '*')
                    dp[1][j] = dp[0][j - 1] &&
                               (p[j - 1] == '.' || p[j - 1] == s[i - 1]);
                else
                    dp[1][j] = dp[1][j - 2] ||  // zero
                               (dp[0][j] && (p[j - 2] == '.' ||
                                             p[j - 2] == s[i - 1]));  // more
            }
            dp[0] = dp[1];
        }
        // dp[0][p.size()] does not work when s is empty.
        return dp[0][p.size()];
    }

    // 32. Longest Valid Parentheses
    int longestValidParentheses(string s) {
        // "()(())" is also valid.
        // https://leetcode.com/problems/longest-valid-parentheses/discuss
        // Stack method: /14126; DP method: /14133.
        int i, max_len = 0, left;
        vector<int> dp(s.size(), 0);
        for (i = 1; i < s.size(); ++i) {
            if (s[i] == ')') {
                if (s[i - 1] == '(') {
                    dp[i] = (i >= 2) ? (dp[i - 2] + 2) : 2;
                    max_len = max(max_len, dp[i]);
                } else {  // s[i - 1] == ')'
                    left = i - dp[i - 1] - 1;
                    if (left >= 0 && s[left] == '(') {
                        dp[i] = dp[i - 1] + 2 + ((left > 0) ? dp[left - 1] : 0);
                        max_len = max(max_len, dp[i]);
                    }
                }
            }
        }
        return max_len;
    }

    // 44. Wildcard Matching
    bool isMatch(string s, string p) {
        int i, j;
        vector<vector<int>> dp(2, vector<int>(p.size() + 1, 0));
        dp[0][0] = 1;
        for (j = 1; j <= p.size(); ++j)
            dp[0][j] = dp[0][j - 1] && p[j - 1] == '*';
        for (i = 1; i <= s.size(); ++i) {
            for (j = 1; j <= p.size(); ++j) {
                if (p[j - 1] != '*')
                    dp[1][j] = dp[0][j - 1] &&
                               (p[j - 1] == s[i - 1] || p[j - 1] == '?');
                else
                    dp[1][j] = dp[0][j] || dp[1][j - 1];
            }
            dp[0] = dp[1];
        }
        return dp[0][p.size()];
    }

    // 62. Unique Paths
    int uniquePaths(int m, int n) {
        int i, j;
        vector<vector<int>> dp{vector<int>(n, 1), vector<int>(n, 0)};
        dp[1][0] = 1;
        for (i = 1; i < m; ++i) {
            for (j = 1; j < n; ++j)
                dp[1][j] = dp[0][j] + dp[1][j - 1];
            dp[0] = dp[1];
        }
        return dp[0][n - 1];
    }

    // # 63 Unique Paths II
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        
    }

    // # 64 Minimum Path Sum

    // # 70 Climbing Stairs

    // # 72 Edit Distance

    // # 85 Maximal Rectangle

    // # 87 Scramble String

    // # 91 Decode Ways

    // # 95 Unique Binary Search Trees II

    // # 96 Unique Binary Search Trees

    // # 97 Interleaving String

    // # 115 Distinct Subsequences

    // # 120 Triangle

    // # 121 Best Time to Buy and Sell Stock

    // # 123 Best Time to Buy and Sell Stock III

    // # 132 Palindrome Partitioning II

    // # 139 Word Break

    // # 140 Word Break II

    // -------------------------------------------------------------------------

    // # 152 Maximum Product Subarray

    // # 174 Dungeon Game

    // # 188 Best Time to Buy and Sell Stock IV

    // # 198 House Robber

    // # 213 House Robber II

    // # 221 Maximal Square

    // # 256 Paint House

    // # 264 Ugly Number II

    // # 265 Paint House II

    // # 276 Paint Fence

    // # 279 Perfect Squares

    // # 300 Longest Increasing Subsequence

    // -------------------------------------------------------------------------
};

int main() {
    cout << DP().longestValidParentheses("()(())") << endl;
    return 0;
}