#include <iostream>
#include <string>
using namespace std;

int main()
{
    string str;
    int state = 0;

    cout << "Enter the string: ";
    cin >> str;

    // Check each character of the string and transition between states
    for (char ch : str)
    {
        if (ch != 'a' && ch != 'b')
        {
            cout << "String not accepted.\nPlease enter a string over {a,b}" << endl;
            return 0;
        }
        state = (state == 0 && ch == 'a') ? 1 : (state == 0 && ch == 'b') ? 0
                                            : (state == 1 && ch == 'a')   ? 1
                                            : (state == 1 && ch == 'b')   ? 2
                                            : (state == 2 && ch == 'a')   ? 1
                                                                          : 0;
    }

    // Determine if the string is accepted based on the final state
    cout << (state == 0 || state == 1 ? "String accepted" : "String not accepted") << endl;

    return 0;
}
