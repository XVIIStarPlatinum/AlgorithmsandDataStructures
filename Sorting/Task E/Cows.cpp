#include<iostream>
using namespace std;

bool checkPlace(int n, int k, const int arr[], int min){
    int last = 0;
    int placed = 1;
    for(int i = 1; i < n; i++){
        if(arr[i] - arr[last] >= min){
            placed++;
            last = i;
            if(placed >= k) break;
        }
    }
    return placed >= k;
}
int main() {
    int n, k, curDist = 1;
    cin >> n >> k;
    int stall[n];
    for(int i = 0; i < n; i++){
        cin >> stall[i];
    }
    int maxDist = stall[n - 1] - stall[0];
    while(curDist < maxDist - 1){
        int m = (curDist + maxDist) / 2;
        (checkPlace(n, k, stall, m)) ? curDist = m : maxDist = m;
    }
    (checkPlace(n, k, stall, maxDist)) ? cout << maxDist : cout << curDist;
    return 0;
}