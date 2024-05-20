#include <algorithm>
#include <iostream>
#include <vector>
/*
 * TODO: переписать задачку на алгоритм Прима
 */
std::vector<int> dsu(1488);

int disjoint_set(int v) {
    if(v == dsu[v]) {
        return v;
    } else {
        return (dsu[v] = disjoint_set(dsu[v]));
    }
}

void dsu_merge(int a, int b) {
    a = disjoint_set(a), b = disjoint_set(b);
    if(a != b) {
        dsu[a] = b;
    }
}

int main() {
    int n, m, max = 0;
    std::cin >> n >> m;
    std::vector<std::pair<int, std::pair<int, int>>> network(m);
    std::vector<std::pair<int, int>> result;
    for(int i = 0; i < m; ++i) {
        std::cin >> network[i].second.first >> network[i].second.second >> network[i].first;
    }
    std::sort(network.begin(), network.end());
    dsu.resize(n);
    for(int i = 0; i < n; ++i) {
        dsu[i] = i;
    }
    for(int i = 0; i < m; ++i) {
        int a = network[i].second.first, b = network[i].second.second, l = network[i].first;
        if(disjoint_set(a) != disjoint_set(b)) {
            max = std::max(max, l);
            result.push_back(network[i].second);
            dsu_merge(a, b);
        }
    }
    std::cout << max << "\n" << result.size() << "\n";
    for(auto & i : result) {
        std::cout << i.first << " " << i.second << "\n";
    }
    return 0;
}
