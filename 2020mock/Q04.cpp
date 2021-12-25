#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    string a, b;
    while (cin >> a >> b) {
        vector<vector<int>> dp(a.length() + 1, vector<int>(b.length() + 1, 0));
        for (int i = 1; i <= a.length(); ++i) {
            for (int j = 1; j <= b.length(); ++j) {
                dp[i][j] = max(max(dp[i - 1][j], dp[i][j - 1]),
                               dp[i - 1][j - 1] + (a[i - 1] == b[j - 1]));
            }
        }
        cout << dp[a.length()][b.length()] << endl;
    }
    return 0;
}
