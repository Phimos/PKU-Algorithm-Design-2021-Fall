#include <iostream>
using namespace std;

int arr[50010];
int lsum[50010], rsum[50010];
int lmax[50010], rmax[50010];

#define INT_MIN -2147483648

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t, n;
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 1; i <= n; ++i) {
            cin >> arr[i];
        }

        lsum[0] = 0;
        lmax[0] = INT_MIN;
        for (int i = 1; i <= n; ++i) {
            lsum[i] = lsum[i - 1] > 0 ? lsum[i - 1] + arr[i] : arr[i];
            lmax[i] = max(lmax[i - 1], lsum[i]);
        }

        rsum[n + 1] = 0;
        rmax[n + 1] = INT_MIN;
        for (int i = n; i >= 1; --i) {
            rsum[i] = rsum[i + 1] > 0 ? rsum[i + 1] + arr[i] : arr[i];
            rmax[i] = max(rmax[i + 1], rsum[i]);
        }

        int ans = INT_MIN;
        for (int i = 1; i < n; ++i) {
            ans = max(ans, lmax[i] + rmax[i + 1]);
        }
        cout << ans << endl;
    }
    return 0;
}