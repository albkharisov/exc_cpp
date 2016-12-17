#include <iostream>

using namespace std;

int main()
{
    cout << "Hello world!" << endl;

    int const ** m =  new int const *[10];
    for (int i = 0; i < 10; i++)
    {
        m[i] = new int[10];
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
//            m[i][j] = i*10 + j;
        }
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
            cout << m[i][j] << "  ";
        cout << endl;
    }



    return 0;
}
