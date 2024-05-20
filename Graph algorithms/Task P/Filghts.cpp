#include <algorithm>
#include <iostream>
#include <vector>

void dfs(int v, std::vector<std::vector<int>>& pulkovo, std::vector<bool>& used, int x) {
    used[v] = true;
    for(int i = 0; i < pulkovo.size(); ++i) {
        if(!used[i] && pulkovo[v][i] <= x) {
            dfs(i, pulkovo, used, x);
        }
    }
}

void dfs_inverse(int v, std::vector<std::vector<int>>& pulkovo, std::vector<bool>& used, int x) {
    used[v] = true;
    for(int i = 0; i < pulkovo.size(); ++i) {
        if(!used[i] && pulkovo[i][v] <= x) {
            dfs_inverse(i, pulkovo, used, x);
        }
    }
}

bool check_graph(int x, std::vector<std::vector<int>> &pulkovo) {
    std::vector<bool> used(pulkovo.size(), false);
    dfs(0, pulkovo, used, x);

    for(int i = 0; i < pulkovo.size(); ++i) {
        if(!used[i]) {
            return false;
        }
    }
    std::vector<bool> used_inverse(pulkovo.size(), false);
    dfs_inverse(0, pulkovo, used_inverse, x);
    for(int i = 0; i < pulkovo.size(); ++i) {
        if(!used_inverse[i]) {
            return false;
        }
    }
    return true;
}

int binary_search_graph(int left, int right, std::vector<std::vector<int>>& pulkovo) {
    while(right - left > 1) {
        int mid = (left + right) / 2;
        if(check_graph(mid, pulkovo)) {
            right = mid;
        } else {
            left = mid;
        }
    }
    return right;
}

int main() {
    int n, max, left = -1, right;
    std::cin >> n;
    std::vector<std::vector<int>> pulkovo(n, std::vector<int>(n, 0));
    for(auto &row : pulkovo) {
        for(auto &cell : row) {
            std::cin >> cell;
            max = std::max(cell, max);
        }
    }
    right = max + 1;
    std::cout << binary_search_graph(left, right, pulkovo);
    return 0;
}