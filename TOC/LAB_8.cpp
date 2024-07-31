// LAB8: C++ code that simulates the behavior of a PDA for the language L = {a^n b^n | n ≥ 1}.
#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool isLanguageAccepted(const string &input)
{
    stack<char> stack;

    for (char c : input)
    {
        if (c == 'a')
        {
            stack.push('a');
        }
        else if (c == 'b')
        {
            if (stack.empty())
            {
                return false; // More 'b's than 'a's
            }
            else
            {
                stack.pop();
            }
        }
        else
        {
            return false; // Invalid input character
        }
    }

    return stack.empty(); // Stack should be empty at the end
}

int main()
{
    string input;
    cout << "Enter a string: ";
    cin >> input;

    if (isLanguageAccepted(input))
    {
        cout << "Accepted: The string is in the language L = {a^n b^n | n ≥ 0}\n";
    }
    else
    {
        cout << "Rejected: The string is not in the language L = {a^n b^n | n ≥ 0}\n";
    }

    return 0;
}
