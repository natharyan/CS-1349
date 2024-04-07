// regular expression to NFA
#include <iostream>
#include <string>
#include <unordered_set>
#include <stack>
#include <vector>

using namespace std;

struct State{
    static int idCount;
    string name;
    // symbol, set of next pointers
    unordered_map<char, vector<State*> > transitions;
    bool isFinal = false;

    State(){name = "q" + to_string(idCount++);}
};

int State::idCount = 0;

class NFA{
    private:
        State* start;
        State* end;
    public:
    // NFA constructor for a single character
    NFA(char c){
        start = new State();
        end = new State();
        start->transitions[c].push_back(end);
    }
    // NFA constructor for existing states
    NFA(State* startstate, State* endstate){
        this->start = startstate;
        this->end = endstate;
    }
    void add_transition(State* from, State* to, char symbol){
        from->transitions[symbol].push_back(to); 
    }
    // concatenation of two NFAs
    static NFA concatenate(NFA a, NFA b){
        a.add_transition(a.end,b.start,'\0'); // epsilon transition
        return NFA(a.start,b.end);
    }
    static NFA unionize(NFA a, NFA b){
        State* start = new State();
        State* end = new State();
        start->transitions['\0'].push_back(a.start);
        start->transitions['\0'].push_back(b.start);
        a.add_transition(a.end,end,'\0');
        b.add_transition(b.end,end,'\0');
        return NFA(start, end);
    }
    static NFA kleenstar(NFA a){
        State* start = new State();
        State* end = new State();
        start->transitions['\0'].push_back(a.start);
        start->transitions['\0'].push_back(end);
        a.add_transition(a.end,end,'\0');
        a.add_transition(a.end,a.start,'\0');
        return NFA(start,end);
    }
    static NFA fromregex(string regex){
        stack<NFA> stack;
        for(char c : regex){
            if(c == '*'){
                stack.push(kleenstar(stack.top()));
                stack.pop();
            }else if(c == '|'){
                NFA a = stack.top();
                stack.pop();
                NFA b = stack.top();
                stack.pop();
                stack.push(unionize(a,b));
            }else if(c == '.'){
                NFA a = stack.top();
                stack.pop();
                NFA b = stack.top();
                stack.pop();
                stack.push(concatenate(a,b));
            }else{
                stack.push(NFA(c));
            }
        }
        stack.top().end->isFinal = true;
        return stack.top();
    }
    // dfs to transitions on input
    bool accepts(string input){
        unordered_set<State*> curstates;
        curstates.insert(this->start);
        for(char c : input){
            unordered_set<State*> nextstates;
            for(State* state : curstates){
                if (state->transitions.count(c) > 0)
                {
                    for(State* nextstate : state->transitions[c]){
                        nextstates.insert(nextstate);
                    }
                }
            }
            curstates = nextstates;
        }
        for(State* state : curstates){
            if(state->isFinal){
                return true;
            }
        }
        return false;
    }
};

int main(){
    // TODO: add (a|b)* type
    // TODO: remove . for concatenation
    NFA nfa = NFA::fromregex("a.b|c*");
    cout << "input: ";
    string input;
    cin >> input;
    bool accepted = nfa.accepts(input);
    cout << "accepted: " << accepted;
} 