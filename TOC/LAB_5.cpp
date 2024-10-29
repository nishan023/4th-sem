// LAB5: Design an NFA that displays if the string contains the substring "101" or not over {0,1}.
#include <iostream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

bool simulate_nfa(const string &input)
{
    // Define the NFA transitions
    vector<vector<pair<char, int>>> transitions = {
        {{'0', 0}, {'1', 1}}, // Transitions from state 0
        {{'0', 0}, {'1', 2}}, // Transitions from state 1
        {{'0', 0}, {'1', 3}}, // Transitions from state 2
        {}                    // State 3 is the accepting state
    };

    unordered_set<int> current_states = {0};

    // Process each character in the input string
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

    // Check if the accepting state 3 is reached
    return current_states.count(3) > 0;
}

int main()
{
    string input;
    cout << "Enter the string over {0,1}: ";
    cin >> input;

    cout << (simulate_nfa(input) ? "The string contains the substring 101." : "The string does not contain the substring 101.") << endl;

    return 0;
}
