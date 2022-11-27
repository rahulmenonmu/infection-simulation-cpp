#include <iostream>


using namespace std;


class Map
{
public:
    unsigned int x, y, size;
    char **grid;
    void displayMap();
    void place(char c);
    char getXY(int y, int x);
    Map()

    {
        setGrid(1, 1);
    }
    Map(unsigned int _y, unsigned int _x)
    {
        if (_y < 1)
        {
            cout << " Number of rows must be greater than 1, setting to default 1" << endl;
            _y = 1;
        }
        if (_x < 1)
        {
            cout << " Number of columns must be greater than 1, setting to default 1" << endl;
            _x = 1;
        }
        setGrid(_y, _x);
    }
    ~Map()
    {
        for (unsigned int i = 0; i < y; i++)
            delete[] grid[i];
        delete[] grid;
    }
    void setGrid(unsigned int _y, unsigned int _x, unsigned int _size = 5)
    {
        x = _x;
        y = _y;
        size = _size;
        grid = new char *[y];
        for (unsigned int i = 0; i < y; i++)
            grid[i] = new char[x];

        for (unsigned int i = 0; i < y; i++)
            for (unsigned int j = 0; j < x; j++)
                grid[i][j] = ' ';
    }
};

void Map::displayMap()
{
    cout<<endl;
    for (unsigned int i = 0; i < y; ++i)
    {
        for (unsigned int k = 0; k < 2 * x; ++k)
        {
            cout << "---";
        }
        cout << endl;
        for (unsigned int j = 0; j < x; ++j)
        {
            if(j==0)
                cout << "|  " << grid[i][j];
            else
                cout<<"  |  "<<grid[i][j];
        }
        cout<< "  |"<<endl;
    }
    for (unsigned int k = 0; k < 2 * x; ++k)
    {
        cout << "---";
    }
}

void Map::place(char c)
{
    unsigned int xloc, yloc;
    while(1){
        yloc = rand() % y;
        xloc = rand() % x;
        if(grid[yloc][xloc] == ' '){
            grid[yloc][xloc] = c;
            break;
        }
    }
}

char Map::getXY(int _y, int _x){
    if( _x > x || _y > y || _x < 1 || _y < 1){
        cout<<"Passed in values are out of bounds for the grid"<<endl;
        return ' ';
    }
    return grid[y-1][x-1];
}


int main(int argc, const char *argv[])
{
    srand((unsigned int)time(NULL));
    int rows, columns;
    cout << "Enter Y" << endl;
    cin >> rows;
    cout << "Enter X" << endl;
    cin >> columns;
    Map map(rows, columns);
    for (int i = 0; i<rows ; ++i){
        map.place('#');
    }
    map.displayMap();
    
    return 0;

}