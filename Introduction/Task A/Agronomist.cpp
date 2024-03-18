#include <bits/stdc++.h>
using namespace std;

int main() {
    int maxLeft, maxRight, curLeft, curRight, n, cur, prev, eq;
    maxLeft = maxRight = curLeft = curRight = 1, prev = eq = 0;
    cin >> n;
    while(n--){
        cin >> cur;
        if(cur == prev){
            eq++;
            if(eq == 3) {
                if(maxRight - maxLeft < curRight - curLeft) {
                    maxLeft = curLeft;
                    maxRight = curRight;
                }
                curLeft = curRight - 1;
                eq--;
            }
        } else {
            prev = cur;
            eq = 1;
        }
        curRight++;
    }
    if(maxRight - maxLeft < curRight - curLeft) {
        maxLeft = curLeft;
        maxRight = curRight;
    }
    cout << maxLeft << " " << --maxRight << "\n";
    return 0;
}