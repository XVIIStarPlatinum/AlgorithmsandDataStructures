#include<bits/stdc++.h>
using namespace std;

int main(){
    int n, eq, maxLeft, maxRight, curLeft, curRight;
    eq = maxLeft = maxRight = curLeft = curRight = 0;
    cin >> n;
    int x[n];
    for(int i = 0; i < n; i++){
        cin >> x[i];
        if(x[i] == x[i - 1]){
            eq++;
            if(eq == 3){
                maxLeft = (curRight - curLeft > maxRight - maxLeft) ? curLeft: maxLeft;
                maxRight = (curRight - curLeft > maxRight - maxLeft) ? curRight : maxRight;
                curLeft = i - 1;
                eq = 2;
            }
        } else {
            eq = 1;
        }
        curRight = i;
    }
    maxLeft = (curRight - curLeft > maxRight - maxLeft) ? curLeft : maxLeft;
    maxRight = (curRight - curLeft > maxRight - maxLeft) ? curRight : maxRight;
    cout << maxLeft + 1 << " " << maxRight + 1 << "\n";
    return 0;
}