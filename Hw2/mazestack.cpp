#include <iostream>
#include <string>
#include <stack>
using namespace std;

class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    stack<Coord> coordStack;
    coordStack.push(Coord(sr, sc));
    maze[sr][sc] = '#';

    while (!coordStack.empty())
    {
        Coord x = coordStack.top();
        //cout << coordStack.top().r() << ", " << coordStack.top().c() << endl;
        coordStack.pop();

        if (x.r() == er && x.c() == ec)
        {   
            return true;
        }
        if (maze[x.r()][x.c() - 1] == '.')
        {
            coordStack.push(Coord(x.r(), x.c() - 1));
            maze[x.r()][x.c() - 1] = '#';
        }
        if (maze[x.r() + 1][x.c()] == '.')
		{
			coordStack.push(Coord(x.r() + 1, x.c()));
			maze[x.r() + 1][x.c()] = '#';
		}
        if (maze[x.r()][x.c() + 1] == '.')
        {
            coordStack.push(Coord(x.r(), x.c() + 1));
            maze[x.r()][x.c() + 1] = '#';
        }
        if (maze[x.r() - 1][x.c()] == '.')
		{
			coordStack.push(Coord(x.r() - 1, x.c()));
			maze[x.r() - 1][x.c()] = '#';
		}
	}
	return false;
}

int main()
{
string maze[10] = {
        "XXXXXXXXXX",
        "X.X..X...X",
        "X....XXX.X",
        "X.XXXX.X.X",
        "X......XXX",
        "X.XX.X...X",
        "X.X..X.X.X",
        "X.X.XXXX.X",
        "X.X...X..X",
        "XXXXXXXXXX"
    };

    if (pathExists(maze, 10, 10, 4, 6, 1, 1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;

    //string maze2[10] = {
    //    "XXXXXXXXXX",
    //    "X.X......X",
    //    "X.X......X",
    //    "X.X......X",
    //    "X.X......X",
    //    "X.X......X",
    //    "X.XXXXXX.X",
    //    "X......X.X",
    //    "X......X.X",
    //    "XXXXXXXXXX"
    //};

    //if (pathExists(maze2, 10, 10, 4, 6, 1, 1))
    //    cout << "Solvable!" << endl;
    //else
    //    cout << "Out of luck!" << endl;
}