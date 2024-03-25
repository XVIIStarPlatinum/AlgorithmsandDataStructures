#include<bits/stdc++.h>
using namespace std;

int main(){
    string str;
    cin >> str;
    bool caught;
    stack<char> st;
    int animal = 0, trap = 0;
    stack<int> animals, traps;
    vector<int> a;
    for(char c : str) {
        (islower(c)) ? animals.push(++animal) : traps.push(++trap), a.push_back(0);
        if(st.empty()){
            st.push(c);
        } else {
            caught = (isupper(st.top()) && islower(c)
                   || islower(st.top()) && isupper(c))
                   && tolower(st.top()) == tolower(c);
            if(caught){
                st.pop();
                a.at(traps.top()-1) = animals.top();
                traps.pop();
                animals.pop();
            } else {
                st.push(c);
            }
        }
    }
    if(!st.empty()) {
        cout << "Impossible";
    } else {
        cout << "Possible\n";
        for(int i : a){
            if(i != 0){
                cout << i << " ";
            }
        }
    }
    return 0;
}
