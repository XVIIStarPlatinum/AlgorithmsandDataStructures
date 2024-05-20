#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>

std::vector<int> lca_vert, lca_dfs_list, lca_position, lca_tree;
std::vector<char> lca_dfs_used;
std::unordered_map<int, int> indices;

void lca_dfs(const std::vector<std::vector<int>> &history, int v, int h = 1) {
    lca_dfs_used[v] = true;
    lca_vert[v] = h;
    lca_dfs_list.push_back(v);
    for (auto i = history[v].begin(); i != history[v].end(); ++i) {
        if (!lca_dfs_used[*i]) {
            lca_dfs(history, *i, h + 1);
            lca_dfs_list.push_back(v);
        }
    }
}

void lca_build_tree(int i, int l, int r) {
    if (l == r) {
        lca_tree[i] = lca_dfs_list[l];
    } else {
        int mid = (l + r) / 2;
        lca_build_tree(i + i, l, mid);
        lca_build_tree(i + i + 1, mid + 1, r);
        (lca_vert[lca_tree[2 * i]] < lca_vert[lca_tree[2 * i + 1]]) ? lca_tree[i] = lca_tree[2 * i] : lca_tree[i] = lca_tree[i + i + 1];
    }
}

void lca_preface(const std::vector<std::vector<int>> &history, int root) {
    int n = (int) history.size();
    lca_vert.resize(n);
    lca_dfs_list.reserve(n * 2);
    lca_dfs_used.assign(n, 0);

    lca_dfs(history, root);

    int m = (int) lca_dfs_list.size();
    lca_tree.assign(lca_dfs_list.size() * 4 + 1, -1);
    lca_build_tree(1, 0, m - 1);

    lca_position.assign(n, -1);
    for (int i = 0; i < m; ++i) {
        int v = lca_dfs_list[i];
        if (lca_position[v] == -1) {
            lca_position[v] = i;
        }
    }
}

int lca_tree_min(int i, int l, int r, int sl, int sr) {
    if (sl == l && sr == r) {
        return lca_tree[i];
    }
    int s_mid = (sl + sr) / 2;
    if (r <= s_mid) {
        return lca_tree_min(2 * i, l, r, sl, s_mid);
    }
    if (l > s_mid) {
        return lca_tree_min(2 * i + 1, l, r, s_mid + 1, sr);
    }
    int ans1 = lca_tree_min(2 * i, l, s_mid, sl, s_mid);
    int ans2 = lca_tree_min(2 * i + 1, s_mid + 1, r, s_mid + 1, sr);
    if(lca_vert[ans1] < lca_vert[ans2]){
        return ans1;
    } else {
        return ans2;
    }
}

int lca(int a, int b) {
    int left = lca_position[a], right = lca_position[b];
    if (left > right) {
        std::swap(left, right);
    }
    return lca_tree_min(1, left, right, 0, (int) lca_dfs_list.size() - 1);
}

int main() {
    int n, l;
    std::cin >> n;
    int maxValue = 0;
    std::unordered_multimap<int, int> milestones;
    for (int i = 0; i < n; i++) {
        int a, b;
        std::cin >> a >> b;
        maxValue = std::max(b, std::max(maxValue, a));
        milestones.emplace(b, a);
    }
    std::vector<std::vector<int>> history(maxValue + 2);
    int root = maxValue + 1;
    auto itr = milestones.begin();
    while (!milestones.empty()) {
        std::vector<int> children;
        int parent = (*itr).first;
        if (parent == -1) {
            parent = maxValue + 1;
        }
        while (itr != milestones.end()) {
            int child = (*itr).second;
            children.push_back(child);
            milestones.erase(itr);
            if (parent == -1) {
                parent = maxValue + 1;
            }
            itr = milestones.find(parent);
            if (parent == maxValue + 1){
                parent = -1;
            }
        }
        if (parent == -1) {
            parent = maxValue + 1;
        }
        history[parent] = children;
        indices.emplace(parent, history.size() - 1);
        itr = milestones.begin();
    }
    lca_preface(history, root);
    std::cin >> l;
    for (int i = 0; i < l; i++) {
        int a, b, v;
        std::cin >> a >> b;
        v = lca(a, b);
        if (v == a) {
            std::cout << 1 << std::endl;
        } else if (v == b) {
            std::cout << 2 << std::endl;
        } else {
            std::cout << 0 << std::endl;
        }
    }
    return 0;
}
