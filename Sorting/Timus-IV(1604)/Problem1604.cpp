#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

class comparable {
public:
    bool operator()(const std::pair<int, int> a, const std::pair<int, int> b) {
        if(a.first != b.first) {
            return a.first < b.first;
        }
        return a.second > b.second;
    }
};
int main() {
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, comparable> p_queue;
    int k;
    std::cin >> k;
    for(int i = 1; i <= k; ++i) {
        int x;
        std::cin >> x;
        p_queue.emplace(x, i);
    }
    while(!p_queue.empty()) {
        std::pair<int, int> top = p_queue.top();
        p_queue.pop();
        std::cout << top.second << " ";
        if(!p_queue.empty()) {
            std::pair<int, int> second_top = p_queue.top();
            p_queue.pop();
            std::cout << second_top.second << " ";
            if(second_top.first > 1) {
                p_queue.emplace(second_top.first - 1, second_top.second);
            }
        }
        if(top.first > 1) {
            p_queue.emplace(top.first - 1, top.second);
        }
    }
    return 0;
}
