#include <iostream>
#include <iomanip>

using namespace std;

int main()
{

    int n, pos, neg, par, impar;
    pos = neg = par = impar = 0;

    cin >> n;
for (int i = 0; i < n; i++)
{
    for(int j = 0; j < 5; j++) 
    {
        int x;
        cin >> x;
        if (x < 0)
            neg++;
        else
            pos++;

        if (x % 2 == 0)
            par++;
        else
            impar++;
    }

    cout << "Quantidade de numeros pares: " << par << endl;
    cout << "Quantidade de numeros impares: " << impar << endl;
    cout << "Quantidade de numeros positivos: " << pos << endl;
    cout << "Quantidade de numeros negativos: " << neg << endl;

    pos = neg = par = impar = 0;

    }

    return 0;
}