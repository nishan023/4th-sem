#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

// Simulate the NFA
bool simulate_nfa(const string &input)
{
    vector<vector<pair<char, int>>> transitions = {
        {{'1', 1}},          // From state 0: move to state 1 on '1'
        {{'0', 2}},          // From state 1: move to state 2 on '0'
        {{'0', 2}, {'1', 2}} // From state 2: stay in state 2 on '0' or '1'
    };

    unordered_set<int> current_states = {0};

    for (char c : input)
    {
        unordered_set<int> next_states;
        for (int state : current_states)
        {
            for (const auto &transition : transitions[state])
            {
                if (transition.first == c)
                {
                    next_states.insert(transition.second);
                }
            }
        }
        current_states = next_states;
    }

    return current_states.count(2) > 0; // Accepting state is 2
}

int main()
{
    string input;
    cout << "Enter the string over {0,1}: ";
    cin >> input;

    cout << (simulate_nfa(input) ? "The string starts with 10." : "The string does not start with 10.") << endl;

    return 0;
}
