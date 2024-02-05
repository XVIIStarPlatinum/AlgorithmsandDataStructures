#include<bits/stdc++.h>
#include<iostream>
using namespace std;

int main(){
    int a, b, c, d, k, tmp = 0;
    cin >> a >> b >> c >> d >> k;
    for(int i = 1; i <= k; i++) {
        tmp = (a * b - c);
        tmp = max(tmp, 0);
        tmp = min(d, tmp);
        if(tmp == a) break;
        a = tmp;
    }
    cout << tmp << endl;
    return 0;
}