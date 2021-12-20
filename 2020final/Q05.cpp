#include <algorithm>
#include <iostream>

using namespace std;

#define maxn 20010

pair<int, int> nums[maxn];
int n;

int arr[maxn];

void init() {
    memset(arr, 0, sizeof(arr));
}

int lowbit(int x) {
    return x & (-x);
}

void add(int x, int k = 1) {
    while (x < maxn) {
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
    while (cin >> n, n) {
        int x;
        for (int i = 0; i < n; ++i) {
            cin >> x;
            nums[i] = make_pair(x, i + 1);
        }
        sort(nums, nums + n);
        init();
        int r = n - 1;
        int result = 0;
        for (int l = n - 1; l >= 0; --l) {
            if (nums[l].first < nums[r].first) {
                for (int i = l + 1; i <= r; ++i) {
                    add(nums[i].second);
                }
                r = l;
            }
            result += getsum(nums[l].second);
        }
        cout << result << endl;
    }
}