// Design a TM that accepts L = {anbn / n ≥ 1}

#include <iostream>
#include <string>

using namespace std;

// Define states of the Turing Machine
enum State
{
    START,
    SCAN_A,
    SCAN_B,
    REJECT,
    ACCEPT
};

class TuringMachine
{
private:
    string tape;
    int head;
    State state;

public:
    TuringMachine(string input)
    {
        tape = input;
        head = 0;
        state = START;
    }

    void transition()
    {
        while (state != ACCEPT && state != REJECT)
        {
            switch (state)
            {
            case START:
                if (tape[head] == 'a')
                {
                    tape[head] = 'X';
                    moveRight();
                    state = SCAN_A;
                }
                else if (tape[head] == 'B')
                {
                    state = REJECT;
                }
                else
                {
                    state = REJECT;
                }
                break;

            case SCAN_A:
                if (tape[head] == 'a')
                {
                    moveRight();
                }
                else if (tape[head] == 'B')
                {
                    state = REJECT;
                }
                else if (tape[head] == 'b')
                {
                    tape[head] = 'Y';
                    moveRight();
                    state = SCAN_B;
                }
                else
                {
                    state = REJECT;
                }
                break;

            case SCAN_B:
                if (tape[head] == 'b')
                {
                    moveRight();
                }
                else if (tape[head] == 'B')
                {
                    state = ACCEPT;
                }
                else
                {
                    state = REJECT;
                }
                break;

            case REJECT:
                return;

            case ACCEPT:
                return;
            }
        }
    }

    void printResult()
    {
        if (state == ACCEPT)
        {
            cout << "String accepted." << endl;
        }
        else
        {
            cout << "String rejected." << endl;
        }
    }

private:
    void moveRight()
    {
        head++;
        if (head == tape.length())
        {
            tape.push_back('B');
        }
    }
};

int main()
{
    string input;
    cout << "--------------------------------------------------------\n";
    cout << "   Turing Machine that accepts L = {anbn / n >= 1} \n";
    cout << "                  Coder: Deepesh\n";
    cout << "--------------------------------------------------------\n";
    while (1)
    {
        cout << "\nEnter input string: ";
        cin >> input;

        input += 'B';

        TuringMachine tm(input);
        tm.transition();
        tm.printResult();
    }

    return 0;
}
