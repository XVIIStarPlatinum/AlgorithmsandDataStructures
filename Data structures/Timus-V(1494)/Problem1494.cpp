#include <array>
#include <iostream>
#include <set>
#include <stack>
#include <unordered_set>

int main() {
    int n, p = 0;
    std::cin >> n;
    int balls[n];
    for(int i = 0; i < n; ++i) {
        std::cin >> balls[i];
    }
    std::stack<int> cue;
    for(int i = 1; i <= n; i++) {
        cue.push(i);
        while(!cue.empty() && balls[p] == cue.top()) {
            p++;
            cue.pop();
        }
    }
    while(p < n) {
        if(balls[p] == cue.top()) {
            p++;
            cue.pop();
        } else {
            break;
        }
    }
    (cue.empty()) ? std::cout << "Not a proof" : std::cout << "Cheater";
    return 0;
}
