#include <cmath>
#include <cstring>
#include <iostream>
#include <unordered_map>
using namespace std;

unordered_map<int, int> code;
int price[110];
int item[110];
int dp[10000];

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0);

    int b;
    cin >> b;
    int c, k, p;  // code, number of items, price
    int s;        // number of special offers
    int target = 0;
    for (int i = 0; i < b; ++i) {
        cin >> c >> k >> p;
        code[c] = i;
        item[i] = powl(6, i);
        price[i] = p;
        target += powl(6, i) * k;
    }
    int n, icode;
    cin >> s;
    for (int i = 0; i < s; ++i) {
        cin >> n;
        icode = 0;
        for (int j = 0; j < n; ++j) {
            cin >> c >> k;
            icode += powl(6, code[c]) * k;
        }
        cin >> p;
        item[b + i] = icode;
        price[b + i] = p;
    }

    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;

    s = s + b;
    for (int i = 0; i <= target; ++i) {
        for (int j = 0; j < s; ++j) {
            if (i - item[j] >= 0) {
                dp[i] = min(dp[i], dp[i - item[j]] + price[j]);
            }
        }
    }
    cout << dp[target] << endl;

    return 0;
}