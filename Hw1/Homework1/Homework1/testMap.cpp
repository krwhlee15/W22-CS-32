#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Map m;  // maps strings to doubles
    assert(m.empty());
    ValueType v = -1234.5;
    assert(!m.get("abc", v) && v == -1234.5); // v unchanged by get failure
    m.insert("xyz", 9876.5);
    //cerr << m.size() << endl;
    assert(m.size() == 1);
    KeyType k = "hello";
    assert(m.get(0, k, v) && k == "xyz" && v == 9876.5);
    assert(m.contains("xyz"));
    Map n;
    m.swap(n);
    KeyType a = "Bye";
    ValueType b = 215;
    assert(n.get(0, a, b) && a == "xyz" && b == 9876.5);

    Map mm;
    mm.insert("Little Ricky", 3.206);
    mm.insert("Ethel", 3.538);
    mm.insert("Ricky", 3.350);
    mm.insert("Lucy", 2.956);
    mm.insert("Ethel", 3.538);
    mm.insert("Fred", 2.956);
    mm.insert("Lucy", 2.956);
    assert(mm.size() == 5);  // duplicate "Ethel" and "Lucy" were not added
    string x;
    double y;
    mm.get(0, x, y);
    assert(x == "Ethel");  // "Ethel" is greater than exactly 0 items in mm
    mm.get(4, x, y);
    assert(x == "Ricky");  // "Ricky" is greater than exactly 4 items in mm
    mm.get(2, x, y);
    assert(x == "Little Ricky");  // "Little Ricky" is greater than exactly 2 items in mm
    assert(y == 3.206);  // the value corresponding to the key "Little Ricky"

    Map m1;
    m1.insert("Fred", 2.956);
    Map m2;
    m2.insert("Ethel", 3.538);
    m2.insert("Lucy", 2.956);
    m1.swap(m2);
    assert(m1.size() == 2 && m1.contains("Ethel") && m1.contains("Lucy") &&
        m2.size() == 1 && m2.contains("Fred"));

    Map gpas;
    gpas.insert("Fred", 2.956);
    assert(!gpas.contains(""));
    gpas.insert("Ethel", 3.538);
    gpas.insert("", 4.000);
    gpas.insert("Lucy", 2.956);
    assert(gpas.contains(""));
    gpas.erase("Fred");
    assert(gpas.size() == 3 && gpas.contains("Lucy") && gpas.contains("Ethel") &&
        gpas.contains(""));
    string kk;
    double vv;
    assert(gpas.get(1, kk, vv) && kk == "Ethel");
    assert(gpas.get(0, kk, vv) && kk == "");

    cout << "Passed all tests" << endl;
}


//int main()
//{
//    Map m;  // maps ints to strings
//    assert(m.empty());
//    ValueType v = "Ouch";
//    assert(!m.get(42, v) && v == "Ouch"); // v unchanged by get failure
//    m.insert(123456789, "Wow!");
//    assert(m.size() == 1);
//    KeyType k = 9876543;
//    assert(m.get(0, k, v) && k == 123456789 && v == "Wow!");
//    cout << "Passed all tests" << endl;
//}