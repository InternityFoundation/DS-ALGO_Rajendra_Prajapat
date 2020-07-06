#include <bits/stdc++.h>
using namespace std;

int p = 1000007;

string checkit(string s, int n, int length, vector<int>& v)
{
    if (length == 0) {
        return "";
    }
    unordered_map<int, vector<int> > mp;
    long long int P = 0;
    string ans = "";
    for (int i = 0; i < length; i++) {
        P = ((P * 26) % p + (s[i] - 'a')) % p;
    }
    mp[P].push_back(0);
    for (int i = length; i < n; i++) {

        P = (P - (long long)v[length - 1] * (s[i - length] - 'a') % p + p) % p;

        P = (P * 26 + s[i] - 'a') % p;

        if (mp.find(P) != mp.end()) {
            for (auto it : mp[P]) {
                string str = s.substr(i - length + 1, length);
                string temp = s.substr(it, length);
                if (temp.compare(str) == 0) {
                    ans = temp;
                    return ans;
                }
            }
        }
        else {
            mp[P].push_back(i - length + 1);
        }
    }
    return ans;
}

string Find(string S)
{
    int n = S.length();
    if (n == 0) {
        return "";
    }
    vector<int> power(n + 2, 1);
    power[0] = 1;
    for (int i = 1; i < n; i++) {
        power[i] = (power[i - 1] * 26) % p;
    }
    int l = 0, h = n;
    string f = "", temp;
    while (l <= h) {
        int mid = l + (h - l) / 2;
        string s = checkit(S, n, mid, power);
        if (s.length() == 0) {
            h = mid - 1;
        }
        else {
            l = mid + 1;
            if (s.length() > f.length()) {
                f = s;
            }
        }
    }
    return f;
}

int main()
{
    string x;
    cin >> x;
    cout << Find(x) << endl;
}