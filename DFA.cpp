#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

struct State{
    string name;
    // symbol, next state pointer
    unordered_map<char, State*> transitions;
    bool isFinal;

    State(string name, bool isFinal) : name(name), isFinal(isFinal) {}
};

class DFA{
private:
    State* start;
    unordered_map<string, State*> states;
public:
    DFA(State* start){
        this->start = start;
        // add string and state pointer to the map
        states[start->name] = start;
    }
    void addtransition(State* from, State* to, char symbol){
        // state does not exist in the map
        if(states.find(from->name) == states.end()){
            states[from->name] = from;
        }
        // state does not exist in the map
        if(states.find(to->name) == states.end()){
            states[to->name] = to;
        }
        // add transition
        from->transitions[symbol] = to;
    }
    bool accepts(string input){
        State* current = this->start;
        for(char c : input){
            if(current->transitions.find(c) == current->transitions.end()){
                return false;
            }
            cout << current->name << " -> " << current->transitions[c]->name << " on " << c << "\n";
            current = current->transitions[c];
        }
        return current->isFinal;
    }
};

int main(){
    State* q0 = new State("q0", true);
    State* q1 = new State("q1", false);

    DFA dfa(q0);
    // accepts even number of 0's
    dfa.addtransition(q0, q1, '0');
    dfa.addtransition(q0,q0,'1');
    dfa.addtransition(q1, q0, '0');
    dfa.addtransition(q1, q1, '1');

    string input;
    cout << "input: ";
    cin >> input;
    cout << "transitions: " << "\n";
    bool accept = dfa.accepts(input);
    cout << "accepts: " << (accept ? " true " : " false ") << "\n";
    return 0;
}