#include <deque>
#include <iostream>

int main() {

    int n;
    std::cin >> n;

    std::deque<std::string> q1;
    std::deque<std::string> q2;

    for (int i = 0; i < n; i++) {
        char action;
        std::cin >> action;
        if(action == '-') {
            std::cout << q1.front() << std::endl;
            q1.pop_front();
        } else {
            std::string number;
            std::cin >> number;
            if(action == '+') {
                q2.push_back(number);
            } else {
                q2.push_front(number);
            }
        }
        int diff = q1.size() - q2.size();
        if(diff == 2) {
            q2.push_front(q1.back());
            q1.pop_back();
        } else if(diff == -1) {
            q1.push_back(q2.front());
            q2.pop_front();
        }
    }
    return 0;
}
