#include <iostream>
#include <string>
using namespace std;

int main() {
    string in_str;
    string s = "";
    while (getline(cin, in_str)) {
        s += in_str + "\n";
    }
    bool in_comment = false, in_string = false;

    int idx = 0;
    string ans = "";
    while (idx < s.length()) {
        if (!in_comment && !in_string) {
            if (idx < s.length() - 1 && s[idx] == '/' && s[idx + 1] == '*') {
                in_comment = true;
                idx += 2;
            } else if (s[idx] == '"') {
                in_string = true;
                cout << s[idx++];
            } else {
                cout << s[idx++];
            }
        } else if (in_comment) {
            if (idx < s.length() - 1 && s[idx] == '*' && s[idx + 1] == '/') {
                in_comment = false;
                idx += 2;
            } else {
                ++idx;
            }
        } else if (in_string) {
            if (s[idx] == '\\') {
                cout << s[idx++];
                cout << s[idx++];
            } else if (s[idx] == '"') {
                in_string = false;
                cout << s[idx++];
            } else {
                cout << s[idx++];
            }
        }
    }
    return 0;
}