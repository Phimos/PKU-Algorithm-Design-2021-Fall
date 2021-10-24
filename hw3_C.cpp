#include <cstring>
#include <iostream>
#include <unordered_map>
using namespace std;

unordered_map<char, int> id{{'A', 0}, {'C', 1}, {'G', 2}, {'T', 3}, {'-', 4}};
int score[5][5] = {{5, -1, -2, -1, -3},
                   {-1, 5, -3, -2, -4},
                   {-2, -3, 5, -2, -2},
                   {-1, -2, -2, 5, -1},
                   {-3, -4, -2, -1, 0}};

int dp[101][101];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int alen, blen;
        string a, b;
        cin >> alen >> a >> blen >> b;
        dp[0][0] = 0;
        for (int i = 1; i <= alen; ++i)
            dp[i][0] = dp[i - 1][0] + score[id[a[i - 1]]][4];
        for (int i = 1; i <= blen; ++i)
            dp[0][i] = dp[0][i - 1] + score[4][id[b[i - 1]]];
        for (int i = 1; i <= alen; ++i) {
            for (int j = 1; j <= blen; ++j) {
                dp[i][j] = dp[i - 1][j - 1] + score[id[a[i - 1]]][id[b[j - 1]]];
                dp[i][j] = max(dp[i][j], dp[i - 1][j] + score[id[a[i - 1]]][4]);
                dp[i][j] = max(dp[i][j], dp[i][j - 1] + score[4][id[b[j - 1]]]);
            }
        }
        cout << dp[alen][blen] << endl;
    }
    return 0;
}