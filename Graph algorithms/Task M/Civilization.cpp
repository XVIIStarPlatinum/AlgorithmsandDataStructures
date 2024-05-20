#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

int main() {
    int n, m, x, y, dx, dy, xPath, yPath, xInit, yInit;
    std::string result;
    std::cin >> n >> m >> x >> y >> dx >> dy;
    --x, --y, --dx, --dy;
    xPath = dx, yPath = dy, xInit = x, yInit = y;
    if(x == dx && y == dy) {
        std::cout << 0 << std::endl;
    }
    std::vector<std::string> seed(n);
    for(int i = 0; i < n; ++i) {
        std::cin >>seed[i];
    }
    std::vector<std::vector<int>> path(n, std::vector<int>(m, INT_MAX));
    std::vector<std::vector<std::pair<int, int>>> parent(n,std::vector<std::pair<int, int>>(m, {-1, -1}));

    auto axisComparator = [&](const std::pair<int, int>& s1, const std::pair<int, int>& s2) {
        return path[s1.first][s1.second] > path[s2.first][s2.second];
    };

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(axisComparator)> vacant(axisComparator);
    path[x][y] = 0;

    vacant.push({x, y});
    int abscissa[] = {1, -1, 0, 0};
    int ordinate[] = {0, 0, 1, -1};
    char compass[] = {'N', 'S', 'W', 'E'};

    while(!vacant.empty()) {
        x = vacant.top().first;
        y = vacant.top().second;
        vacant.pop();
        if(x == dx && y == dy) {
            break;
        }
        for(int i = 0; i < 4; ++i) {
            int xNext = x + abscissa[i];
            int yNext = y + ordinate[i];
            if(xNext >= 0 && yNext >= 0 && xNext < n && yNext < m && seed[xNext][yNext] != '#') {
                int currentCost = path[x][y] + (seed[xNext][yNext] == '.' ? 1 : (seed[xNext][yNext] == 'W' ? 2 : 0));
                if (currentCost < path[xNext][yNext]) {
                    path[xNext][yNext] = currentCost;
                    parent[xNext][yNext] = {x, y};
                    vacant.push({xNext, yNext});
                }
            }
        }
    }
    if(path[dx][dy] == INT_MAX) {
        std::cout << -1 << std::endl;
        return 0;
    }

    while(xPath != xInit || yPath != yInit) {
        int xPathAfter = parent[xPath][yPath].first;
        int yPathAfter = parent[xPath][yPath].second;
        for(int i = 0; i < 4; ++i) {
            if(xPathAfter == xPath + abscissa[i] && yPathAfter == yPath + ordinate[i]) {
                result.push_back(compass[i]);
            }
        }
        xPath = xPathAfter;
        yPath = yPathAfter;
    }
    std::reverse(result.begin(), result.end());
    std::cout << path[dx][dy] << "\n" << result;
}
