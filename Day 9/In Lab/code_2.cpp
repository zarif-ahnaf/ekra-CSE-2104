#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ofstream mehedi("Data_input1.txt");
    mehedi << "Mehedi Hasan, BAUET" << endl;
    for (int i = 39; i < 73; i++)
    {
        mehedi << i << " ";
    }
    return 0;
}
