#include<bits/stdc++.h>
using namespace std;

int main() {
    int a, b, c, d;
    long long k;
    cin >> a >> b >> c >> d >> k;
    if(a == a * b - c) {
        cout << a;
    } else if(k > d) {
        cout << ((a * b - c <= a) ? 0 : d);
    } else {
        for(int i = 1; i <= k; i++) {
            a = min(d, max(a * b - c, 0));
        }
        cout << a << endl;
    }
    return 0;
}