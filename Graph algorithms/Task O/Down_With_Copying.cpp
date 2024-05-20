#include <iostream>
#include <vector>

bool bipartite_dfs(std::vector<std::vector<int>>& classroom, int table, std::vector<int>& depth) {
    for(auto itr : classroom[table]) {
        if(depth[itr] == -1) {
            depth[itr] = 1 - depth[table];
            if(!bipartite_dfs(classroom, itr, depth)) {
                return false;
            }
        } else if(depth[itr] == depth[table]) {
            return false;
        }
    }
    return true;
}

int main() {
    int n, m, copier, provider;
    bool result = true;
    std::cin >> n >> m;
    std::vector<std::vector<int>> students(n);
    for(int i = 0; i < m; ++i) {
        std::cin >> copier >> provider;
        students[copier - 1].push_back(provider - 1);
        students[provider - 1].push_back(copier - 1);
    }
    std::vector<int> depth(n, -1);
    for(int i = 0; i < n; ++i) {
        if(depth[i] == -1) {
            depth[i] = 1;
            if(!bipartite_dfs(students, i, depth)) {
                result = false;
            }
        }
    }
    (result) ? std::cout << "YES" : std::cout << "NO";
}
