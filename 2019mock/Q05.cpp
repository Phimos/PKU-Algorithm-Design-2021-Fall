#include <iostream>
#include <map>
using namespace std;
#define maxn 500010
typedef long long LL;

pair<int, int> nums[maxn];
int arr[maxn];

int lowbit(int x) {
    return x & (-x);
}

LL getsum(int x) {
    LL sum = 0;
    for (; x > 0; x -= lowbit(x))
        sum += arr[x];
    return sum;
}

void add(int x, int k = 1) {
    for (; x < maxn; x += lowbit(x))
        arr[x] += k;
}

int main() {
    int n, v;
    while (cin >> n, n) {
        for (int i = 1; i <= n; ++i) {
            cin >> v;
            nums[i].first = v;
            nums[i].second = i;
        }
        sort(nums + 1, nums + n + 1);
        memset(arr, 0, sizeof(arr));
        LL ans = 0;
        int r = n;
        for (int l = n; l > 0; --l) {
            if (nums[l].first < nums[r].first) {
                for (int i = l + 1; i <= r; ++i) {
                    add(nums[i].second);
                }
                r = l;
            }
            ans += getsum(nums[l].second);
        }
        cout << ans << endl;
    }
}
