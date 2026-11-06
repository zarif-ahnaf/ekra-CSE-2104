#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream boot("Shagor.txt");
    ofstream pos("positive.txt");
    ofstream neg("negative.txt");

    int x;

    for (int i = 0; boot >> x; i++)
    {
        cout << x << " ";

        if (x > 0)
        {
            pos << x << endl;
        }
        else if (x < 0)
        {
            neg << x << endl;
        }
    }
    return 0;
}
