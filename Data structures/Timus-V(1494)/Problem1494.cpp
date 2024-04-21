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
    std::stack<int> st;
    for(int i = 1; i <= n; i++) {
        st.push(i);
        while(!st.empty() && balls[p] == st.top()) {
            p++;
            st.pop();
        }
    }
    while(p < n) {
        if(balls[p] == st.top()) {
            p++;
            st.pop();
        } else {
            break;
        }
    }
    (st.empty()) ? std::cout << "Not a proof" : std::cout << "Cheater";
    return 0;
}
