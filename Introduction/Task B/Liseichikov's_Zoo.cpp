#include<bits/stdc++.h>
#include<iostream>
using namespace std;

int main(){
    string str;
    cin >> str;
    bool caught;
    stack<char> st;
    int animal = 0, trap = -1;
    stack<int> animals, traps;
    const int a = str.length() / 2;
    int cage[a];
    for(char c : str){
        (islower(c)) ? animals.push(++animal) : traps.push(++trap);
        if(st.empty()){
            st.push(c);
        } else {
            caught = (isupper(st.top()) && islower(c) || islower(st.top()) && isupper(c))
                   && tolower(st.top()) == tolower(c);
            if(caught){
                cage[traps.top()] = animals.top();
                st.pop();
                traps.pop();
                animals.pop();
            } else {
                st.push(c);
            }
        }
    }
    if(st.empty()) {
        cout << "Possible" << "\n";
        for(int i = 0; i < a; i++){
            cout << cage[i] << " ";
        }
    } else {
        cout << "Impossible" << endl;
    }
    return 0;
}
