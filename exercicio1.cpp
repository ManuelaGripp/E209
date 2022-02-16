#include <iostream>
#include <iomanip>

using namespace std;

int main()
{

    int qtdLaranja;

    cin >> qtdLaranja;

    if (qtdLaranja < 12)
    {
        cout << "Preco da unidade: R$" << fixed << setprecision(2) << 0.80 << endl;
        cout << "Preco total: R$" << fixed << setprecision(2) << qtdLaranja * 0.8;
    }
    else
    {
        cout << "Preco da unidade: R$" << 0.65 << endl;
        cout << "Preco total: R$" << fixed << setprecision(2) << qtdLaranja * 0.65;
    }

    return 0;
}