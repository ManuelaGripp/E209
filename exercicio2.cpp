#include <iostream>
#include <iomanip>

using namespace std;

int main()
{

    int x;

    cout << "Entre com o valor [0,50]: ";
    cin >> x;

    while (x < 0 || x > 50)
    {
        cout << "Entre com o valor [0,50]: ";
        cin >> x;
    }

    for (int i = (x - 1); i > 0; i--)
    {
        cout << "Resto da divisao  de " << x << " por " << i << ":" << x % i << endl;
    }

    return 0;
}