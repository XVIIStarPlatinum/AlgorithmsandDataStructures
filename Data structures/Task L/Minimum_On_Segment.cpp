#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

void sliding_window_min(std::vector<int> vec, int N, int K) {
    std::deque<int> window(K);
    int i;
    for (i = 0; i < K; ++i) {
        while ((!window.empty()) && vec[i] <= vec[window.back()]) {
            window.pop_back();
        }
        window.push_back(i);
    }
    for (; i < N; ++i) {
        std::cout << vec[window.front()] << " ";
        while ((!window.empty()) && window.front() <= i - K) {
            window.pop_front();
        }
        while ((!window.empty()) && vec[i] <= vec[window.back()]) {
            window.pop_back();
        }
        window.push_back(i);
    }
    std::cout << vec[window.front()];
}
int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> numbers;
    for (int i = 0; i < n; i++) {
        int num;
        std::cin >> num;
        numbers.push_back(num);
    }
    sliding_window_min(numbers, n, k);
    return 0;
}