#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

#define ll long long
int arr[200010];
pair<int, int> raw[200010];

int lowbit(int x) {
    return x & (-x);
}

void add(int x, int k) {
    while (x <= 200005) {
        arr[x] += k;
        x += lowbit(x);
    }
}

int getsum(int x) {
    int sum = 0;
    while (x > 0) {
        sum += arr[x];
        x -= lowbit(x);
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    while (cin >> n, n) {
        memset(arr, 0, sizeof(arr));
        int tmp;
        for (int i = 0; i < n; ++i) {
            cin >> tmp;
            raw[i] = make_pair(tmp, i + 1);
        }
        sort(raw, raw + n);
        int l = n - 2, r = n - 1;
        ll ans = 0;
        while (l >= 0) {
            while (raw[r].first > (raw[l].first << 1)) {
                add(raw[r].second, 1);
                --r;
            }
            ans += (ll)getsum(raw[l].second);
            --l;
        }
        cout << ans << endl;
    }
    return 0;
}