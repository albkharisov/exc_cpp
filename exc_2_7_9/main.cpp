#include <iostream>

using namespace std;

/**
 *
 * 1 2 3
 * 4 5 6
 *
 * 2x3
 *
 * 1 4
 * 2 5
 * 3 6
 */
int ** transpose(int const * const * m, unsigned rows, unsigned cols)
{
    int **mt;

    mt = new int*[cols];

    for (int i = 0; i < cols; ++i)
    {
        mt[i] = new int[rows];
        for (int j = 0; j < rows; ++j)
            mt[i][j] = m[j][i];
    }
    return mt;
}

int main()
{
    int **m ;
    m = new int*[3];

    for (int i = 0; i < 3; ++i)
    {
        m[i] = new int[2];
    }

    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

    int **g;
    g = transpose(m, 2, 3);


//    cout << "g = " << g << endl;
//    cout << "g[0] = " << g[0] << endl;
//    cout << "g[1] = " << g[1] << endl;
//
//    return 0;
    cout << endl << "m:" << endl;
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 3; ++j)
            cout << " " << m[i][j];
        cout << endl;
    }


    cout << endl << "g:" << endl;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 2; ++j)
            cout << " " << g[i][j];
        cout << endl;
    }
    return 0;
}
