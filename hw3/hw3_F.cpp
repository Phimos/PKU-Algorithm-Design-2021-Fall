#include <algorithm>
#include <iostream>
using namespace std;

bool dp[101][101][45000];
int weight[101];
int main() {
    int n;
    cin >> n;
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> weight[i];
        sum += weight[i];
    }
    dp[0][0][0] = true;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            for (int w = 0; w <= 450 * j; ++w) {
                if (dp[i - 1][j][w]) {
                    dp[i][j][w] = true;
                    dp[i][j + 1][w + weight[i]] = true;
                }
            }
        }
    }
    for (int w = (sum >> 1); w >= 0; --w) {
        if (dp[n][n >> 1][w] || dp[n][(n + 1) >> 1][w]) {
            cout << w << ' ' << sum - w << endl;
            return 0;
        }
    }
    return 0;
}