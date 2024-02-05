#include <bits/stdc++.h>
#include <iostream>
using namespace std;

int kadanes(const int* x, size_t a){
    int maxSum = (x[0] < 0) ? 0 : x[0], curSum = 0;
    for (int i = 0; i < a; i++){
        curSum = max(curSum, 0);
        curSum += x[i];
        maxSum = max(maxSum, curSum);
    }
    return maxSum;
}
int main() {
    int a;
    cin >> a;
    int x[a];
    for(int i = 0; i < a; i++){
        cin >> x[i];
    }
    cout << kadanes(x, a) << endl;
    return 0;
}