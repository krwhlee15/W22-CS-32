#include <iostream>
#include <cmath>
#include <cassert>
using namespace std;

bool somePredicate(double x)
{
	return x < 0; // include <cmath> for std::sin, etc.
}
// Return true if the somePredicate function returns false for at
// least one of the array elements, false otherwise.
bool anyFalse(const double a[], int n)
{
	if (n < 0)
	{
		return true;
	}
	else
	{
		return somePredicate(a[n - 1]) && anyFalse(a, n - 1);
	}
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const double a[], int n)
{
	if (n < 0)
	{
		return 0;
	}
	else
	{
		if (!somePredicate(a[n - 1]))
		{
			return 1 + countFalse(a, n - 1);
		}
		else
		{
			return 0 + countFalse(a, n - 1);
		}
	}
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns true.  If there is no such
// element, return -1.
int firstTrue(const double a[], int n)
{
	if (n <= 0)
	{
		return -1;
	}
	else if (n == 1)
	{
		if (somePredicate(a[0]))
		{
			return 0;
		}
		return -1;
	}
	else
	{
		int check = firstTrue(a, n - 1);
		if (check == -1)
		{
			if (somePredicate(a[n - 1]))
			{
				return n - 1;
			}
			else
			{
				return -1;
			}
		}
		else
			return check;
	}
}

// Return the subscript of the largest element in the array (i.e.,
// return the smallest subscript m such that a[m] >= a[k] for all
// k such that k >= 0 and k < n).  If there is no such subscript,
// return -1.
int locateMax(const double a[], int n)
{
	if (n < 0)
	{
		return -1;
	}
	else if (n == 1)
	{
		return 0;
	}
	else
	{
		if (a[0] < a[n - 1])
		{
			return 1 + locateMax(a + 1, n - 1);
		}
		else
		{
			return locateMax(a, n - 1);
		}
	}
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not contain
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a2 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a2 is
//    50 30 20
// or
//    10 20 20
bool contains(const double a1[], int n1, const double a2[], int n2)
{
	if (n1 <= 0)
	{
		n1 = 0;
	}

	if (n2 <= 0)
	{
		n2 = 0;
	}

	if (n2 == 0)
	{
		return true;
	}
	else if (n1 == 0 && n2 != 0)
	{
		return false;
	}
	else
	{
		if (a2[0] == a1[0])
		{
			return contains(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
		}
		else
		{
			return contains(a1 + 1, n1 - 1, a2, n2);
		}
	}
}

int main()
{
	double arr1[10] = { -5, 5, -4, 4, -3, 3, -2, 2, -1, 1 };
	double arr2[5] = { 10, 9, 8, 7, 5 };
	double arr3[5] = { 5, 4, 3, 2, 1 };
	double arr4[7] = { 2, 6, 9, 19, 4, -5, 8 };
	double arr5[1] = {};
	assert(somePredicate(arr1[0]));
	assert(firstTrue(arr2, 5) == -1);
	assert(firstTrue(arr4, 7) == 5);
	assert(locateMax(arr4, 7) == 3);
	assert(locateMax(arr2, 5) == 0);
	assert(!contains(arr1, 10, arr2, 5));
	assert(contains(arr1, 10, arr3, 5));
	assert(contains(arr1, 10, arr5, 0));

	cout << "Test Successful" << endl;
}