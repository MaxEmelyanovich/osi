#include <iostream>
#include <cmath>
using namespace std;
int main(int argc, char *argv[])
{
    int* newArray = new int[argc];
    for (int i = 0, l = 0, r = 1; i < argc; i++)
    {
        int number = atoi(argv[i]);
        for (int j=2; j <= sqrt((double)number); j++)
        {
            if (number%j == 0 && number != j)
            {
                newArray[argc - r] = number;
                ++r;
                number = 0;

                break;
            }
        }
        if (number != 0)
        {
            newArray[l] = number;
            ++l;
        }
    }
    for (int i = 0; i < argc; i++)
    {
        cout << newArray[i] << " ";
    }
    cout << "\n";
    system("pause");
    return 0;
}