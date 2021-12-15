#include <cstring>
#include <iostream>
using namespace std;

int cards[100];
int dp[100][100];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> cards[i];
    }

    memset(dp, 0x3f3f3f3f, sizeof(dp));
    for (int i = 0; i < n; ++i) {
        dp[i][i] = 0;
    }
    for (int i = 1; i < n; ++i) {
        dp[i - 1][i] = 0;
    }
    for (int d = 2; d < n; ++d) {
        for (int i = 0; i + d < n; ++i) {
            for (int j = i + d; j < n; ++j) {
                for (int k = i + 1; k < j; ++k) {
                    dp[i][j] =
                        min(dp[i][j], dp[i][k] + dp[k][j] +
                                          cards[i] * cards[k] * cards[j]);
                }
            }
        }
    }
    cout << dp[0][n - 1] << endl;
    return 0;
}