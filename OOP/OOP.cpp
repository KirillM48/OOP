#include <iostream>
using namespace std;
ostream& endll(ostream& out) { return  out << endl << endl; }
int main()
{
    int i;
    cout << "Enter int: ";
    while (!(cin >> i) || cin.get() != '\n')
    {
        cin.clear();
        cin.ignore(9999, '\n');
        cin.sync();
        cout << "Invalid number! Enter int: ";
    }
    cout << "hi" << endll << "bye";
}