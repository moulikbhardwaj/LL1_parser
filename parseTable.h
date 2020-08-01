#include "firstAndFollow.h"

template<typename T1, typename T2>
ostream & operator<<(ostream & os, pair<T1,T2> dt){
    os << dt.first << " -> " << dt.second;
    return os;
}

template<typename T>
ostream & operator<<(ostream & os, vector<T> dt){
    for(auto i:dt){
        os << i;
    }
    return os;
}

class parseTable{
private:

    // friend ostream &operator<<(ostream & os, const pair<string, vector<string>> & dt){
    //     os << dt.first << " -> ";
    //     for(auto i:dt.second){
    //         os << i;
    //     }
    //     return os;
    // }
    map<string, set<vector<string>>> productions;
    map<string,set<string>> first;
    map<string,set<string>> follow;
    set<string> terminal;
    set<string> nonTerminals;

    map<pair<string,string>, pair<string, vector<string>>> table;
    firstAndFollow f;

public:
    parseTable(map<string, set<vector<string>>> productions, set<string> terminal,set<string> nonTerminals, string startingSymbol):productions(productions), terminal(terminal), nonTerminals(nonTerminals), f(productions,terminal,nonTerminals,startingSymbol){
        first = f.getFirstSet();
        follow = f.getFollowSet();
        for(auto i:productions){
            // j is rhs of one of production rule originating from i.first
            for(auto j:i.second){
                if(j==vector<string>(1,"")){
                    for(auto j:follow[i.first]){
                        table[{i.first,j}] = {i.first,{""}};
                    }
                    continue;
                }
                auto fst = first[j[0]];
                for(auto k:fst){
                    table[{i.first,k}] = {i.first,j};
                }
            }
        }
    }
    void printSets(){
        cout << left;
        cout << "FirstSet:\n";
        f.printFirstSet();
        cout << "\nFollowSet:\n";
        f.printFollowSet();
    }
    
    void printParseTable(){
        cout << "Parse Table:\n\n";
        cout << setw(15) << "NT\\T";
        for(auto i:terminal){
            cout << setw(15) <<  i;
        }
        cout << setw(15) <<  "Epsilon";
        cout << endl;
        for(auto i:nonTerminals){
            cout << setw(15) << i;
            for(auto j:terminal){
                if(table.find({i,j})!=table.end()){
                    stringstream st;
                    st << table[{i,j}];
                    cout << setw(15) << st.str();
                }
                else{
                    cout << setw(15) << "empty";
                }
            }
            if(table.find({i,""s})!=table.end()){
                stringstream st;
                st << table[{i,""}];
                cout << setw(15) << st.str();
            }
            else{
                cout << setw(15) << "empty";
            }
            cout << endl;
        }
    }
    map<pair<string,string>, pair<string, vector<string>>> getParseTable(){
        return table;
    }
};