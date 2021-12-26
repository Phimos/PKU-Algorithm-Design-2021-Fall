#include <iostream>
using namespace std;

#define maxn 10010
typedef long long LL;

LL cost[maxn], yogurt[maxn];

int main() {
    LL n, s;
    cin >> n >> s;
    for (int i = 0; i < n; ++i)
        cin >> cost[i] >> yogurt[i];
    LL mincost = 10000;
    LL ans = 0;
    for (int i = 0; i < n; ++i) {
        mincost += s;
        mincost = min(mincost, cost[i]);
        ans += mincost * yogurt[i];
    }
    cout << ans << endl;
}
