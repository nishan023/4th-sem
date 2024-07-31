// LAB7: C++ code that generates strings representing properly balanced parentheses using a context-free grammar.
#include <iostream>
#include <string>

using namespace std;

// Function to generate strings representing properly balanced parentheses
void generateBalancedParentheses(string prefix, int openCount, int closeCount, int n)
{
    // Base case: if openCount and closeCount reach n (both are balanced)
    if (openCount == n && closeCount == n)
    {
        cout << prefix << endl;
        return;
    }

    // Recursive case: if openCount < n, add an open parenthesis
    if (openCount < n)
    {
        generateBalancedParentheses(prefix + "(", openCount + 1, closeCount, n);
    }

    // Recursive case: if closeCount < openCount, add a close parenthesis
    if (closeCount < openCount)
    {
        generateBalancedParentheses(prefix + ")", openCount, closeCount + 1, n);
    }
}

int main()
{
    int n;
    cout << "Enter the number of pairs of parentheses: ";
    cin >> n;

    cout << "Properly balanced parentheses of size " << n << ":" << endl;
    generateBalancedParentheses("", 0, 0, n);

    return 0;
}
