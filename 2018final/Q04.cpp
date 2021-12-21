#include <cstring>
#include <iostream>
using namespace std;
#define maxn 128
#define maxm 10010

int n, m;
int w[maxn], v[maxn];
int dp[maxm];

int main() {
    cin >> m >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> w[i] >> v[i];
    }
    fill(dp, dp + m + 1, INT_MIN);
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = m; j - w[i] >= 0; --j) {
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
    }
    int maxval = 0;
    for (int i = 0; i <= m; ++i) {
        maxval = max(maxval, dp[i]);
    }
    cout << maxval << endl;
}