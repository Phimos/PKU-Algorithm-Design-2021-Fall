#include <cstring>
#include <iostream>
using namespace std;
#define maxn 32
#define maxm 512

int n, m;
int pos[maxm];
int cumsum[maxm];
int dp[maxn][maxm];

int main() {
    cin >> m >> n;
    for (int i = 1; i <= m; ++i) {
        cin >> pos[i];
        cumsum[i] = cumsum[i - 1] + pos[i];
    }
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= m; ++i) {
        dp[1][i] =
            (cumsum[i] - cumsum[(i + 1) >> 1]) - (cumsum[i >> 1] - cumsum[0]);
    }
    for (int i = 2; i <= n; ++i) {
        for (int j = i; j <= m; ++j) {
            for (int k = i - 1; k < j; ++k) {
                dp[i][j] =
                    min(dp[i][j], dp[i - 1][k] +
                                      (cumsum[j] - cumsum[(j + k + 1) >> 1]) -
                                      (cumsum[(j + k) >> 1] - cumsum[k]));
            }
        }
    }
    cout << dp[n][m] << endl;
}
