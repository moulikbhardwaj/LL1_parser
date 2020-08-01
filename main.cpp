#include "parseTable.h"

int main(){
    map<string,set<vector<string>>> production;
    production["E"].insert({"T","E'"});
    production["E'"].insert({"+","T","E'"});
    production["E'"].insert({""});
    production["T"].insert({"F","T'"});
    production["T'"].insert({"*","F","T'"});
    production["T'"].insert({""});
    production["F"].insert({"(","E",")"});
    production["F"].insert({"id"});

    string startingSymbol = "E";
    set<string> terminals = {"+", "*", "(", ")", "id"};
    set<string> nonTerminals = {"E", "E'", "T", "T'", "F"};


    parseTable pt(production,terminals,nonTerminals,startingSymbol);
    pt.printSets();
    cout << endl;
    pt.printParseTable();
    auto table = pt.getParseTable();
    vector<string> input;
    ifstream inputFS("input.txt");
    while(!inputFS.eof()){
        string s;
        inputFS >> s;
        input.push_back(s); 
    }
    input.push_back("");
    stack<string> st;
    st.push("");
    st.push(startingSymbol);
    int nxt = 0;
    while(st.size()){
        auto tp = st.top();
        st.pop();
        if(tp == ""){continue;}
        if(terminals.find(tp)!=terminals.end()){
            nxt++;
            continue;
        }
        if(table.find({tp,input[nxt]})!=table.end()){
            for(auto i = table[{tp,input[nxt]}].second.rbegin(); i != table[{tp,input[nxt]}].second.rend(); i++){
                st.push(*i);
            }
            cout << "Applying Rule: " << table[{tp,input[nxt]}] << endl;
        }
        else{
            cout << "ERROR!!! Parsing failed, cant find transition for " << tp << "->" << input[nxt] << endl;
            return 1;
        }
    }
    cout << "Parsing Successful" << endl;
    return 0;
}