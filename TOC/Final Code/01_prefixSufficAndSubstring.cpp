/* WAP to find prefix, suffix and substring from given string */
#include <iostream>
#include <string.h>
#include <set>
using namespace std;
void prefixFunction(int i, int j, int l, char str[], char prefix[])
{
    cout << "Prefix: ";
    for (i = 0; i < l; i++)
    {
        for (j = 0; j <= i; j++)
        {
            prefix[j] = str[j];
        }
        prefix[j] = '\0';
        cout << prefix << " ";
    }
    cout << endl;
}
void suffixFunction(int i, int j, int l, int k, int m, char str[], char suffix[])
{
    cout << "Suffix: ";
    for (k = 0; k < l; k++)
    {
        for (m = k; m < l; m++)
        {
            suffix[m - k] = str[m];
        }
        suffix[m - k] = '\0';
        cout << suffix << " ";
    }
    cout << endl;
}
void subStringFunction(int i, int j, int l, int o, int n, char str[], char substring[])
{
    cout
        << "Substring: ";
    set<string> unique_substrings; // Use a set to keep track of unique substrings
    for (n = 0; n < l; n++)
    {
        for (o = n; o < l; o++)
        {
            // Extract substring using string.substr() function
            string sub = string(str).substr(n, o - n + 1); // (start, length) of substring
            // Check if substring has already been generated
            if (unique_substrings.find(sub) == unique_substrings.end())
            {
                unique_substrings.insert(sub);
                cout << sub << " ";
            }
        }
    }
    cout << endl;
}
int main()
{
    char str[100], prefix[100], suffix[100], substring[100];
    int i, j, k, l, m, n, o, p, choice;
    cout << "----------------------\n";
    cout << "   String Operations\n";
    cout << "     Coder: Deepesh\n";
    cout << "----------------------\n";
    cout << "\n1) Prefix\n";
    cout << "2) Suffix\n";
    cout << "3) Sub String\n";
    cout << "4) Exit\n";
    while (1)
    {
        cout << "\nChoose an option: ";
        cin >> choice;
        cout << "\nEnter a string: ";
        cin >> str;
        l = strlen(str);
        if (choice == 1)
            prefixFunction(i, j, l, str, prefix);
        else if (choice == 2)
            suffixFunction(i, j, l, k, m, str, suffix);
        else if (choice == 3)
            subStringFunction(i, j, l, o, n, str, substring);
        else
            exit(1);
    }
    return 0;
}
