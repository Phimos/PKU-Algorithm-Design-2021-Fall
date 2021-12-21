#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    string s;
    while (cin >> s) {
        cout << s << endl;

        stack<char> stk;
        string unmatch(s.length(), ' ');
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] == '(') {
                stk.push(i);
            } else if (s[i] == ')') {
                if (stk.empty()) {
                    unmatch[i] = '?';
                } else {
                    stk.pop();
                }
            }
        }
        while (!stk.empty()) {
            unmatch[stk.top()] = '$';
            stk.pop();
        }
        cout << unmatch << endl;
    }
}