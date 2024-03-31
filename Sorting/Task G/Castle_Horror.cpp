#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

struct element {
    char letter;
    int weight;
};

bool comparator(const element a, const element b) {
    if(a.weight == b.weight) {
        return a.letter < b.letter;
    } else {
        return a.weight < b.weight;
    }
}

int main() {
    const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::string str, answer;
    std::cin >> str;
    std::unordered_map<char, int> weights;
    for (int i = 0; i < 26; ++i) {
        int x;
        std::cin >> x;
        weights[alphabet[i]] = x;
    }
    std::map<char, int> taken, all;
    for (char &i : str) {
        all[i]++;
    }
    std::vector<element> word;
    for (char &i : str) {
        if (all[i] > 1 && taken[i] < 2) {
            word.push_back({i, weights[i]});
            taken[i]++;
        } else {
            answer += i;
        }
    }
    std::sort(word.begin(), word.end(), comparator);
    for (int j = 0; answer.length() != str.length(); j += 2) {
        answer = word[j].letter + answer;
        answer += word[j + 1].letter;
    }
    std::cout << answer;
    return 0;
}
