// LAB7: C++ code that generates strings representing properly balanced parentheses using a context-free grammar
#include <iostream>
#include <string>
using namespace std;

// Recursive function to generate balanced parentheses
void generateBalancedParentheses(string prefix, int openCount, int closeCount, int n)
{
    if (openCount == n && closeCount == n)
    {
        cout << prefix << endl;
        return;
    }
    if (openCount < n)
        generateBalancedParentheses(prefix + "(", openCount + 1, closeCount, n);
    if (closeCount < openCount)
        generateBalancedParentheses(prefix + ")", openCount, closeCount + 1, n);
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
