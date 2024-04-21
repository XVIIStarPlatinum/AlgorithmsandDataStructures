#include <iostream>
#include <list>
#include <queue>
#include <set>
#include <unordered_set>

int main() {
    const int max_p = 500000;
    int n, k, p, tact = 0;
    std::unordered_set<int> on_the_floor;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::less<>> cars;

    std::cin >> n >> k >> p;

    int input[p];
    std::list<int> nodes[n];

    for (int i = 0; i < p; ++i) {
        std::cin >> input[i];
        nodes[--input[i]].push_back(i);
    }

    for (int i = 0; i < p; ++i) {
        nodes[input[i]].pop_front();
        if(on_the_floor.find(input[i]) == on_the_floor.end()) {
            tact++;
//            std::cout << i << " снять машинку " << input[i] + 1 << " ";
            if(on_the_floor.size() >= k) {
//                std::cout << "поднять машинку " << cars.top().second + 1;
                on_the_floor.erase(cars.top().second);
                cars.pop();
            }
            on_the_floor.insert(input[i]);
//            std::cout << std::endl;
        }
        int priority;
        if(nodes[input[i]].empty()) {
            priority = max_p;
        } else {
            priority = nodes[input[i]].front();
        }
        cars.emplace(priority, input[i]);
    }
    std::cout << tact;
    return 0;
}
