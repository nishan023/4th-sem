#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool isLanguageAccepted(const string &input) {
    stack<char> stack;

    for (char c : input) {
        if (c == 'a') {
            stack.push('a');
        } else if (c == 'b') {
            if (stack.empty()) return false;
            stack.pop();
        } else {
            return false; // Invalid character
        }
    }

    return stack.empty(); // Valid if stack is empty
}

int main() {
    string input;
    cout << "Enter a string: ";
    cin >> input;

    cout << (isLanguageAccepted(input) ? "Accepted: The string is in the language L = {a^n b^n | n ≥ 1}\n" : "Rejected: The string is not in the language L = {a^n b^n | n ≥ 1}\n");

    return 0;
}
