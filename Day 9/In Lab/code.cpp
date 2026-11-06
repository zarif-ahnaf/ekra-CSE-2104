#include <iostream>
using namespace std;

int main()
{
    float a, b;
    cout << "Enter Your Number: " << endl;
    cin >> a >> b;

    try
    {
        if (a < 0 || b < 0)
            throw 10;
        cout << "Result= " << a / b;
    }
    catch (int q)
    {
        cout << " Negative Number" << endl;
    }

    try
    {
        if (b == 0)
            throw 5.66666666666;
        cout << "Result= " << a / b;
    }
    catch (double w)
    {
        cout << "Undefine! Something devided zero not possible" << endl;
    }

    return 0;
}
