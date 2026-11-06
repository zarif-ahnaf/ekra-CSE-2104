#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream pointer("CSE21.txt");
    int x;
    for (int i = 0; pointer >> x; i++)
        cout << x << " ";
    return 0;
}
