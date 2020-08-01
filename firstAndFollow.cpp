#include <bits/stdc++.h>
using namespace std;

map<string,set<vector<string>>> production;
map<string,set<string>> first;
map<string,set<string>> follow;

string startingSymbol = "E";

set<string> terminals = {"+", "*", "(", ")", "id"};
set<string> nonTerminals = {"E", "E'", "T", "T'", "F"};

set<string> firstOf(string s){
    if(first.find(s)!=first.end()){
        return first[s];
    }
    if(terminals.find(s)!=terminals.end()){
        first[s].insert({s});
        return first[s];
    }
    if(production[s].find({""})!=production[s].end()){
        first[s].insert("");
    }
    for(auto k:production[s]){
        for(int i = 0; i < k.size(); i++){
            string symbol = k[i];
            auto fnt = firstOf(symbol);
            if(fnt.find("")==fnt.end()){
                set<string> st;
                set_union(first[s].begin(), first[s].end(), fnt.begin(), fnt.end(), inserter(st, st.begin()));
                first[s] = st;
                break;
            }
            fnt.erase(fnt.find(""));
            set<string> st;
            set_union(first[s].begin(), first[s].end(), fnt.begin(), fnt.end(), inserter(st,st.begin()));
            first[s] = st;
        }
    }
    return first[s];
}

map<string,set<string>> preSet;

void createProductions(){
    production["E"].insert({"T","E'"});
    production["E'"].insert({"+","T","E'"});
    production["E'"].insert({""});
    production["T"].insert({"F","T'"});
    production["T'"].insert({"*","F","T'"});
    production["T'"].insert({""});
    production["F"].insert({"(","E",")"});
    production["F"].insert({"id"});
    for(auto i:production){
        for(auto j:i.second){
            for(auto k:j){
                if(nonTerminals.find(k)!=nonTerminals.end()){
                    preSet[k].insert(i.first);
                }
            }
        }
    }
}

void printFirstSet(){
    for(auto k:first){
        if(nonTerminals.find(k.first)==nonTerminals.end()){continue;}
        cout << k.first << " -> [";
        for(auto it = k.second.begin(); it !=k.second.end(); it++){
            if(it!=k.second.begin()){cout << ", ";}
            cout << *it;
        }
        cout << ']' << endl;
    }
}

void printFollowSet(){
    for(auto k:follow){
        cout << k.first << " -> [";
        for(auto it = k.second.begin(); it !=k.second.end(); it++){
            if(it!=k.second.begin()){cout << ", ";}
            cout << *it;
        }
        cout << ']' << endl;
    }
}

void createFirstSet(){
    for(auto k:terminals){
        firstOf(k);
    }
    for(auto k:nonTerminals){
        firstOf(k);
    }
}


set<string> followOf(string s){
    if(follow.find(s)!=follow.end()){return follow[s];}
    if(s==startingSymbol){
        follow[s].insert("");
    }
    auto & st = preSet[s];
    for(auto k:st){
        for(auto j:production[k]){
            auto it = find(j.begin(), j.end(), s);
            if(it==j.end()){continue;}
            int symbolIdx = it-j.begin();
            int followId = symbolIdx+1;
            while(true){
                if(followId == j.size()){
                    if(k!=s){
                        auto fl = followOf(k);
                        set<string> st;
                        set_union(fl.begin(), fl.end(), follow[s].begin(), follow[s].end(), inserter(st,st.begin()));
                        follow[s] = st;
                    }
                    break;
                }
                string followSymbol = j[followId];
                auto fst = firstOf(followSymbol);
                if(fst.find("")==fst.end()){
                    set<string> st;
                    set_union(fst.begin(), fst.end(), follow[s].begin(), follow[s].end(), inserter(st,st.begin()));
                    follow[s] = st;
                    break;
                }
                fst.erase(fst.find(""));
                set<string> st;
                set_union(fst.begin(), fst.end(), follow[s].begin(), follow[s].end(), inserter(st, st.begin()));
                follow[s] = st;
                followId++;
            }
        }  
    }
    return follow[s];
}
void createFollowSet(){
    for(auto i:nonTerminals){
        followOf(i);
    }
}

int main(){
    createProductions();
    createFirstSet();
    cout << "FirstSet:\n\n";
    printFirstSet();
    createFollowSet();
    cout << "\n\nFollowSet:\n" << endl;
    printFollowSet();
}