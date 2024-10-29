// LAB1: Program to find prefixes, suffixes, and substrings from a given string (Using C, C++ and else)
#include <iostream>
#include <string>
#include <set>
using namespace std;

int main()
{
    char str[100], prefix[100], suffix[100];
    int i, j, k, l, m, n, o;

    cout << "Enter a string: ";
    cin >> str;

    int len = str.length();

    // Print prefixes
    cout << "Prefix: ";
    for (int i = 1; i <= len; ++i)
        cout << str.substr(0, i) << " ";
    cout << endl;

    // Print suffixes
    cout << "Suffix: ";
    for (int i = 0; i < len; ++i)
        cout << str.substr(i) << " ";
    cout << endl;

    // Print unique substrings
    cout << "Substring: ";
    set<string> unique_substrings;
    for (int i = 0; i < len; ++i)
    {
        for (int j = i + 1; j <= len; ++j)
        {
            string sub = str.substr(i, j - i);
            if (unique_substrings.insert(sub).second)
                cout << sub << " ";
        }
    }
    cout << endl;

    return 0;
}
