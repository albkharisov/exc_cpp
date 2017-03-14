#include <iostream>

using namespace std;

int main()
{
    unsigned long a = 0;
    cin >> a;

    unsigned long *am = new unsigned long [a];
    unsigned long *aw = new unsigned long [a];

    for (unsigned long i = 0; i < a; ++i)
    {
        cin >> aw[i];
    }

    unsigned long tmp = 1;
    for (unsigned long i = 0; i < a; ++i)
    {
        unsigned long j = 30;
        do
        {
            tmp = 0x01ul << --j;
//            cout << "tmp=" << tmp << " j=" << j << " aw[" << i << "]=" << aw[i] << endl;
        }
        while (tmp > aw[i]);
        cout << j << endl;
    }


    delete am;
    delete aw;
    return 0;
}
