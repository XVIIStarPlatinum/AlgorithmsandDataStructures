#include<bits/stdc++.h>
using namespace std;

struct val_depth{
    int value;
    int depth;
};

int main(){
    int depth = 0;
    stack<unordered_set<string>> changedVal;
    map<string, stack<val_depth>> hashMap;
    changedVal.emplace(0);
    string input;
    while(cin >> input){
//        if(input == "&") {
//            break;
//        }
        if(input == "{") {
            depth++;
            changedVal.emplace(0);
        } else if(input == "}"){
            depth--;
            for(const string &k: changedVal.top())
                if(!hashMap[k].empty() && hashMap[k].top().depth > depth){
                    hashMap[k].pop();
                }
            changedVal.top().clear();
            changedVal.pop();
        } else if(!input.empty()){
            char equalSign = (int) input.find('=');
            string lHash = input.substr(0, equalSign);
            string rHash = input.substr(equalSign + 1, input.length());
            if(hashMap[lHash].empty()) {
                hashMap[lHash].push({0, depth});
            }
            if(isdigit(rHash[0]) || rHash[0] == '-'){
                if(hashMap[lHash].top().depth < depth){
                    hashMap[lHash].push({stoi(rHash), depth});
                } else {
                    hashMap[lHash].top() = {stoi(rHash), depth};
                }
            } else {
                if(hashMap[rHash].empty()){
                    hashMap[rHash].push({0, depth});
                }
                cout << hashMap[rHash].top().value << "\n";
                if(hashMap[lHash].top().depth < depth){
                    hashMap[lHash].push({hashMap[rHash].top().value, depth});
                } else {
                    hashMap[lHash].top() = {hashMap[rHash].top().value, depth};
                }
            }
            changedVal.top().insert(lHash);
        }
    }
    return 0;
}
