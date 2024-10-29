// LAB3: Write a program for DFA for the language of string over {0,1} in which each string ends with 11 (using C, C++ and else).
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string str;
    int state = 0;

    cout << "Enter the string: ";
    cin >> str;

    // Check for valid characters and transition between states
    for (char ch : str)
    {
        if (ch != '0' && ch != '1')
        {
            cout << "String not accepted.\nPlease enter a string over {0,1}" << endl;
            return 0;
        }

        // DFA transition based on current state and input character
        state = (state == 0 && ch == '1') ? 1 : (state == 1 && ch == '1') ? 2
                                            : (state == 2 && ch == '0')   ? 0
                                            : (state == 2 && ch == '1')   ? 1
                                                                          : state;
    }

    // Determine if the string is accepted
    cout << (state == 2 ? "String accepted" : "String not accepted") << endl;

    return 0;
}
