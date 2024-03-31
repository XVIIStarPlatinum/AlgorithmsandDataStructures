#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

struct pumpkin{
    int x;
    int y;
    int i;
};
bool comparator(const pumpkin a, const pumpkin b) {
    if(atan2(a.y, a.x) != atan2(b.y, b.x)) {
        return atan2(b.y, b.x) > atan2(a.y, a.x);
    }
    return pow(b.x, 2) + pow(b.y, 2) > pow(a.x, 2) + pow(a.y, 2);
}
int main() {
    int n, x_init, y_init, begin = 0;
    std::vector<pumpkin> lawn;
    std::cin >> n;
    std::cin >> x_init >> y_init;
    for(int i = 1; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        lawn.push_back({x - x_init, y - y_init, i + 1});
    }
    sort(lawn.begin(), lawn.end(), comparator);
    for(int i = 0; i < n - 2; ++i) {
        if(lawn[i].x * lawn[i + 1].y <= lawn[i].y * lawn[i + 1].x
        && lawn[i].x * lawn[i + 1].x < -(lawn[i].y * lawn[i + 1].y)) {
            begin = i;
            break;
        }
    }
    std::cout << n << "\n" << 1 << "\n";
    for(int i = 0; i < n - 1; i++) {
        std::cout << (lawn[(begin + i) % (n - 1)].i) << std::endl;
    }
    return 0;
}