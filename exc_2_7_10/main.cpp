#include <iostream>

using namespace std;
#define MIN(x,y)        ((x) < (y) ? (x) : (y))

void swap_min(int *m[], unsigned rows, unsigned cols)
{
    int min = (int) 0x7FFFFFFF;
    int mr = 0;

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols ; ++j)
        {
            if (min > m[i][j])
            {
                min = m[i][j];
                mr = i;
            }
        }
    }

    if (mr != 0)
    {
        for (int j = 0; j < cols; ++j)
        {
            m[mr][j] += m[0][j];
            m[0][j] = m[mr][j] - m[0][j];
            m[mr][j] = m[mr][j] - m[0][j];
        }
    }
}

void printmas(int *m[], unsigned rows, unsigned cols)
{
    cout << "printm:" << endl;
    cout << "m=" << (void*) m << endl;
    cout << "*m=" << (void*) m[0] << endl;

//    return;

    for (unsigned i = 0; i < rows; ++i)
    {
        for (unsigned j = 0; j < cols ; ++j)
        {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
//    int m1[3][3] = {
//                    {1,  2, 3},
//                    {-4, 5, 6},
//                    {7,  8, 9}
//                 };

    int col = 3;
    int row = 3;
    int** m = new int *[row];
    for (int i = 0; i < row; ++i)
        m[i] = new int [col];

    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = -4;
    m[1][1] = 5;
    m[1][2] = 6;
    m[2][0] = 7;
    m[2][1] = 8;
    m[2][2] = 9;

    printmas(/*(int **) */m, row, col);
    swap_min(m, row, col);
    printmas(/*(int **) */m, row, col);
    cout << "Hello world!" << endl;
    return 0;
}
