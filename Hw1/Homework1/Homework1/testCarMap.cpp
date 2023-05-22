#include "CarMap.h"
#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    CarMap c;
    assert(c.addCar("8AJT930"));
    assert(c.addCar("3FUN029"));
    assert(c.addCar("7UCS032"));

    assert(c.miles("8AJT930") == 0);
    assert(c.drive("8AJT930", 70293));
    assert(c.miles("8AJT930") == 70293);

    assert(c.fleetSize() == 3);

    c.print();

    cout << "Passed all tests" << endl;
}