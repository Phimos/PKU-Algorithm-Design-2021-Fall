#include <iostream>
using namespace std;

int dp[128][128];
int w[128];
int cumsum[128];
int n;

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
        cumsum[i] = cumsum[i - 1] + w[i];
    }

    for (int i = 1; i <= n; ++i) {
        cout << cumsum[i] << endl;
    }

    for (int i = 1; i <= n; ++i) {
        dp[i][i] = 0;
    }

    for (int l = 2; l <= n; ++l) {
        for (int i = 1; i + l <= n + 1; ++i) {
            int j = i + l - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k <= j; ++k) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + cumsum[j] -
                                             cumsum[i - 1]);
            }
        }
    }
    cout << dp[1][n] << endl;
}
