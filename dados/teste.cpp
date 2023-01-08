#include <iostream>

using namespace std;

int main()
{
    string a;
    cout << "cin" << endl;
    cin >> a;
    fflush(stdout);
    cout << a << endl;
    cout << "getline" << endl;
    std::getline(cin >> ws, a);
    cout << a << endl;
}