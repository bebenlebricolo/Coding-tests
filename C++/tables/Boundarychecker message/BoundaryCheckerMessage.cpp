#include <iostream>
#include <limits>
#include <cstdio>
using namespace std;

struct IndexedPoint2D
{
    IndexedPoint2D(unsigned i, double x, double y) : index(i) , X(x), Y(y) {}
    unsigned index;
    double X;
    double Y;
};

static const IndexedPoint2D pointList[3] = 
{
    IndexedPoint2D(0, 16325698.23659745 , 6598745632.26548965 ),
    IndexedPoint2D(0, 15469873.25645789 , 6598745696.32678693 ),
    IndexedPoint2D(0, 65447986.65987454 , 45126658.2365889 )
};




int main()
{

    cout << "|  Index  |\tX\t|\tY\t|" << endl;
    cout.precision(std::numeric_limits< double >::max_digits10);
    
    for(auto &point : pointList)
    {
        char sX[64];
        char sY[64];
        snprintf(sX, 64, "%.2lf", point.X);
        snprintf(sY, 64, "%.2lf", point.Y);
        cout << "     " << point.index << "\t    " << sX << "\t  " << sY << endl;
    }


    return 0;
}