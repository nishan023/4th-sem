// LAB6: Design an NFA that accepts strings starting with "10" or not over {0,1}.
#include <iostream>
#include <vector>
#include <set>

using namespace std;

// Define the NFA as a set of states and transitions
vector<vector<pair<char, int>>> transitions = {
    {{'1', 1}},          // Transitions from state 0: move to state 1 on '1'
    {{'0', 2}},          // Transitions from state 1: move to state 2 on '0'
    {{'0', 2}, {'1', 2}} // Transitions from state 2: stay in state 2 on '0' or '1'
};

// Define a function to simulate the NFA on a given string
bool simulate_nfa(const string &input)
{
    // Set of current states
    set<int> current_states = {0};

    // Loop through each character in the input string
    for (char c : input)
    {
        // Set of next states
        set<int> next_states;
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
        // Update the current states to the next states
        current_states = next_states;
    }
    // Check if state 2 (the accepting state) is in the set of current states
    return current_states.find(2) != current_states.end();
}

int main()
{
    string input;
    cout << "Enter the string over {0,1}: ";
    cin >> input;

    if (simulate_nfa(input))
    {
        cout << "The string starts with 10.";
    }
    else
    {
        cout << "The string does not start with 10.";
    }

    return 0;
}
