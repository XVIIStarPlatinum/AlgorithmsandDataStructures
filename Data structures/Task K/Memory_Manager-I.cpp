#include <iostream>
#include <map>
#include <vector>

std::map<int,int> blocks_ends;
std::multimap<int,int> blocks_sz_start;

void remove_by_sz(const std::map<int, int>::iterator& it){
    auto it_sizes = blocks_sz_start.find(it -> second - it -> first);
    while (it_sizes -> second != it -> first) it_sizes++;
    blocks_sz_start.erase(it_sizes);
    blocks_ends.erase(it);
}
void remove(const std::multimap<int, int>::iterator& it){
    blocks_ends.erase(it -> second);
    blocks_sz_start.erase(it);
}

void insert(const std::pair<int, int>& p){
    blocks_ends.insert(p);
    blocks_sz_start.insert({p.second - p.first, p.first});
}


int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    n++;
    std::vector<std::pair<int,int>> memory_table(m,{0,0});
    insert({1,n});
    for (int i = 0; i < m; ++i) {
        int query;
        std::cin >> query;
        if(query < 0){
            query *= -1;
            query--;
            if(memory_table[query].first < 0) continue;
            int start_orig = memory_table[query].first,
            sz_orig = memory_table[query].second,
            end_orig = start_orig + sz_orig;
            auto after_block = blocks_ends.lower_bound(end_orig),
            before_block = (after_block != blocks_ends.begin()) ? prev(after_block) : blocks_ends.end();
            if(after_block != blocks_ends.end() && after_block -> first == end_orig) {
                if(before_block != blocks_ends.end() && before_block -> second == start_orig) {
                    int new_start = before_block -> first;
                    int new_end = after_block -> second;
                    remove_by_sz(before_block);
                    remove_by_sz(after_block);
                    insert({new_start,new_end});
                } else {
                    int new_end = after_block -> second;
                    remove_by_sz(after_block);
                    insert({start_orig,new_end});
                }
            } else {
                if(before_block != blocks_ends.end() && before_block -> second ==start_orig) {
                    int new_start = before_block -> first;
                    remove_by_sz(before_block);
                    insert({new_start,end_orig});
                } else {
                    insert({start_orig,end_orig});
                }
            }
        } else {
            auto it = blocks_sz_start.lower_bound(query);
            if(it == blocks_sz_start.end()) {
                memory_table[i] = std::make_pair(-1,query);
                std::cout << -1 << std::endl;
            } else {
                std::cout << it -> second << std::endl;
                int new_start = it -> second + query;
                int new_end = it -> first + it -> second;
                memory_table[i] = std::make_pair(it -> second, query);
                remove(it);
                insert({new_start,new_end});
            }
        }
    }
    return 0;
}