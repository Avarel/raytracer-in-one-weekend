#include <iostream>
#include "vec3.h"

using std::cout;
using std::endl;

int main()
{
    int nx = 200;
    int ny = 100;
    cout << "P3" << endl
         << nx << " " << ny << endl
         << "255" << endl;
    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            cout << ye() << endl;
            vec3 col(float(i) / float(nx), float(j) / float(ny), 0.2);
            col *= 255.99;
            col.make_round_int();
            cout << col << endl;
        }
    }
    return 0;
}