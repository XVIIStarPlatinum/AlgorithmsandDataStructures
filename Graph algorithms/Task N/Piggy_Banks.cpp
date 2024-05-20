#include <iostream>
#include <vector>

void dfs(int v, bool* broken, std::vector<std::vector<int>>* graph) {
    broken[v] = true;
    for(int piggy : (*graph)[v]) {
        if(!broken[piggy]) {
            dfs(piggy, broken, graph);
        }
    }
}

int main() {
    int n, piggy, result = 0;
    std::cin >> n;
    std::vector<std::vector<int>> pigs(n);
    bool broken[n];
    for(int i = 0; i < n; ++i) {
        std::cin >> piggy;
        pigs[piggy - 1].push_back(i);
        pigs[i].push_back(piggy - 1);
        broken[i] = false;
    }

    for(int i = 0; i < n; ++i) {
        if(!broken[i]) {
            ++result;
            dfs(i, broken, &pigs);
        }
    }
    std::cout << result << "\n";
}
