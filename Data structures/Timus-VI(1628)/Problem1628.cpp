#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

static int m, n, k;

bool horizontal_comparator(std::pair<int, int> p1, std::pair<int, int> p2) {
    if (p1.first < p2.first) {
        return true;
    } else if (p1.first > p2.first) {
        return false;
    } else {
        return p1.second < p2.second;
    }
}

bool vertical_comparator(std::pair<int, int> p1, std::pair<int, int> p2) {
    if(p1.second < p2.second) {
        return true;
    } else if(p1.second > p2.second) {
        return false;
    } else {
        return p1.first < p2.first;
    }
}

int main() {
    std::cin >> m >> n >> k;
    std::vector<std::pair<int, int>> occupied_days;
    for (int i = 0; i < m + 2; i++) {
        occupied_days.emplace_back(i, 0);
        occupied_days.emplace_back(i, n + 1);
    }
    for (int i = 1; i < n + 1; i++) {
        occupied_days.emplace_back(0, i);
        occupied_days.emplace_back(m + 1, i);
    }
    for (int i = 0; i < k; i++) {
        int x, y;
        std::cin >> x >> y;
        occupied_days.emplace_back((x), (y));
    }
    std::unordered_set<int> one_days;
    int weeks = 0;
    std::sort(occupied_days.begin(), occupied_days.end(), horizontal_comparator);
    for (int i = 1; i < occupied_days.size(); i++) {
        std::pair<int, int> prev = occupied_days[i - 1];
        std::pair<int, int> curr = occupied_days[i];
        if (curr.first == prev.first) {
            int dist = curr.second - prev.second - 1;
            if (dist == 1) {
                one_days.emplace(curr.first * n + curr.second - 1);
            } else if (dist > 1) {
                weeks++;
            }
        }
    }
    std::sort(occupied_days.begin(), occupied_days.end(), vertical_comparator);
    for (int i = 1; i < occupied_days.size(); i++) {
        std::pair<int, int> prev = occupied_days[i - 1];
        std::pair<int, int> curr = occupied_days[i];
        if (curr.second == prev.second) {
            int dist = curr.first - prev.first - 1;
            if (dist == 1) {
                auto item = one_days.find((curr.first - 1) * n + curr.second);
                if (item != one_days.end()) {
                    weeks++;
                }
            } else if (dist > 1) {
                weeks++;
            }
        }
    }
    std::cout << weeks;
    return 0;
}
