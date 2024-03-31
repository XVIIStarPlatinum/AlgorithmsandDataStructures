#include<iostream>

int main() {
    int n, k, curDist = 1, maxDist;
    std::cin >> n >> k;
    int stall[n];
    for(int i = 0; i < n; i++){
        std::cin >> stall[i];
    }
    maxDist = stall[n - 1] - stall[0] + 1;
    while(maxDist - 1 > curDist){
        int mid = (curDist + maxDist) / 2;
        int last = stall[0];
        int cows = 1;
        for(int i = 0; i < n; i++) {
            if(mid <= stall[i] - last) {
                last = stall[i];
                cows++;
            }
        }
        (cows >= k) ? curDist = mid : maxDist = mid;
    }
    std::cout << curDist;
    return 0;
}
