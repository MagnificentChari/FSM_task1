#include <iostream>
#include <map>
#include <set>

using namespace std;

class FSM {
private:
    int initialState;
    int currentState;
    set<int> finalStates;
    map<pair<int, char>, int> setState;

public:
    FSM(int init) {
        finalStates.insert(4);
        finalStates.insert(5);

        setState[make_pair(0, 'a')] = 1;
        setState[make_pair(1, 'a')] = 2;
        setState[make_pair(1, 'b')] = 3;
        setState[make_pair(3, 'c')] = 4;
        setState[make_pair(2, 'a')] = 3;
        setState[make_pair(3, 'b')] = 5;

        initialState = init;
        currentState = initialState;

    }

    bool nextState(char symbol) {
        if (!setState.count(make_pair(currentState, symbol))) {
            return false;
        }
        else {
            currentState = setState[make_pair(currentState, symbol)];
            return true;
        }
    }

    bool isFinal() {
        return finalStates.count(currentState);
    }
};

pair<bool, int> maxString(FSM fsm, string str, int k = 0) {
    int counter = 0;
    pair<bool, int> result = make_pair(false, counter);

    for (int i = k; i < str.size(); i++) {
        if (!fsm.nextState(str[i])) {
            break;
        }

        counter += 1;
        if (fsm.isFinal()) {
            result.first = true;
            result.second = counter;
        }
    }
    return result;
}

void output(pair<bool, int> result) {
    cout << "Есть подстрока: " << (result.first ? "true" : "false") << ", " << "максимальная длина: " << result.second << endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    FSM fsm(0);
    output(maxString(fsm, "aaacab"));
    output(maxString(fsm, "aca"));
    output(maxString(fsm, "aaab"));
    output(maxString(fsm, "aaa"));
    output(maxString(fsm, "axfdaaabc", 4));
    output(maxString(fsm, "axfdaaabc", 6));
    output(maxString(fsm, "aaaabbbab", 3));
}
