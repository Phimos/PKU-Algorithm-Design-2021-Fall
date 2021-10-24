#pragma GCC optimize(2)

#include <iostream>
#include <queue>
using namespace std;

struct Median {
    priority_queue<int, vector<int>, less<int>> max_heap;
    priority_queue<int, vector<int>, greater<int>> min_heap;
    Median() {}

    void push(int x) {
        if (max_heap.size() == min_heap.size()) {
            if (max_heap.empty() || x < min_heap.top()) {
                max_heap.push(x);
            } else {
                max_heap.push(min_heap.top());
                min_heap.pop();
                min_heap.push(x);
            }
        } else {
            if (x < max_heap.top()) {
                min_heap.push(max_heap.top());
                max_heap.pop();
                max_heap.push(x);
            } else {
                min_heap.push(x);
            }
        }
    }
    int query() { return max_heap.top(); }
    void del() {
        max_heap.pop();
        if (max_heap.size() < min_heap.size()) {
            max_heap.push(min_heap.top());
            min_heap.pop();
        }
    }
};

int main() {
    int n, t, x;
    char op;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        Median median = Median();
        for (int i = 0; i < n; i++) {
            scanf("%c", &op);
            scanf("%c", &op);
            if (op == 'I') {
                scanf("%d", &x);
                median.push(x);
            } else if (op == 'Q') {
                cout << median.query() << endl;
            } else {
                median.del();
            }
        }
    }
}