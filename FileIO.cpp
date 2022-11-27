#include <iostream>
#include<fstream>

using namespace std;


class location
{
public:
    int x, y;

public:
    location()
    {
        set(0, 0);
    }
    location(int _y, int _x)
    {
        set(_y, _x);
    }
    void set(int _y, int _x)
    {
        y = _y;
        x = _x;
    }
    void increment(location l)
    {
        x += l.x;
        y += l.y;
    }
};

class Character
{
public:
    location l;
    char status;
    Character(){};
    Character(location _l, char _status)
    {
        l = _l;
        status = _status;
    }
};

class node
{
public:
    Character data;
    node *next;
    node(Character _data)
    {
        data = _data;
        next = NULL;
    }
    char getCharacter()
    {
        return data.status;
    }
    friend class nodes;
};

class nodes
{
public:
    node *top;
    nodes()
    {
        top = NULL;
    }
    void push(Character data)
    {
        node *n = new node(data);
        n->next = top;
        top = n;
    }
    bool pop(Character &data)
    {
        if (top == NULL)
            return false;
        node *n = top;
        top = top->next;
        data = n->data;
        delete n;
        return true;
    }
    void remove1(location l){
        node * prev = top;
        for (node* n = top; n != NULL; n = n->next){
            if( n->data.l.x == l.x && n->data.l.y == l.y){
                if(n == top){
                    if(top->next == NULL){
                        delete n;
                        top = NULL;
                        return;
                    }
                    top = top->next;
                    delete n;
                    return;
                }
                prev->next = n->next;
                delete n;
                return;
            }
            prev = n;
        }
    }
    void remove(int nodeOffset)
    {
        node *temp1 = top, *temp2 = NULL;
        int ListLen = 0;

        if (top == NULL)
        {
            //cout << "nodes empty." << endl;
            return;
        }
        temp1 = top;
        if (nodeOffset == 1)
        {

            top = top->next;
            delete temp1;
            return;
        }

        while (nodeOffset-- > 1)
        {
            temp2 = temp1;
            temp1 = temp1->next;
        }
        temp2->next = temp1->next;
        delete temp1;
    }
    node *find(location l)
    {
        //cout << "Looking for node at " << l.y << ", " << l.x << endl;
        for (node *n = top; n != NULL; n = n->next)
        {
            if (n->data.l.x == l.x && n->data.l.y == l.y)
            {
                return n;
            }
        }
        return NULL;
    }
    int findOffset(location l)
    {
        int offset = 0;
        for (node *n = top; n != NULL; n = n->next)
        {
            if (n->data.l.x == l.x && n->data.l.y == l.y)
            {
                return offset;
            }
            offset++;
        }
        return offset;
    }
    void display()
    {
        for (node *n = top; n != NULL; n = n->next)
            cout << n->getCharacter() << '\t';
        cout << endl;
    }
};

class Map
{
public:
    unsigned int x, y, h_count, i_count, r_count, f_count;
    char **grid;
    nodes characters;
    void moveCharacters();
    void moveLeft(location &l, Character ch);
    void moveRight(location &l, Character ch);
    void moveUp(location &l, Character ch);
    void moveDown(location &l, Character ch);
    void makeMove(int moveSelector, location &l, Character ch);
    void displayMap(int frame);
    void place(char c);
    char getXY(int y, int x);
    int mp;
    float ir, rr, mr;
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
    void setGrid(unsigned int _y, unsigned int _x)
    {
        x = _x;
        y = _y;
        h_count = 0;
        i_count = 0;
        r_count = 0;
        f_count = 0;
        grid = new char *[y];
        for (unsigned int i = 0; i < y; i++)
            grid[i] = new char[x];

        for (unsigned int i = 0; i < y; i++)
            for (unsigned int j = 0; j < x; j++)
                grid[i][j] = ' ';
    }
};
void Map::displayMap(int frame)
{
    cout << endl;
    for (unsigned int i = 0; i < y; ++i)
    {
        for (unsigned int k = 0; k < 2 * x; ++k)
        {
            cout << "---";
        }
        cout << endl;
        for (unsigned int j = 0; j < x; ++j)
        {
            if (j == 0)
                cout << "|  " << grid[i][j];
            else
                cout << "  |  " << grid[i][j];
        }
        cout << "  |" << endl;
    }
    for (unsigned int k = 0; k < 2 * x; ++k)
    {
        cout << "---";
    }
    cout << endl
         << "Frame : " << frame << " Healthy : " << h_count << "\t"
         << "Infected : " << i_count << "\t"
         << "Recovered : " << r_count << "\t"
         << "Fatalities : " << f_count << "\n"
         << "MP : " << mp << endl;
}
void Map::place(char c)
{
    unsigned int xloc, yloc;
    // cout<<"Map::place"<<endl;
    while (1)
    {
        yloc = rand() % y;
        xloc = rand() % x;
        // cout<<"random y,x is : " << yloc << ", " << xloc<<endl;
        if (grid[yloc][xloc] == ' ')
        {
            if (c != '#')
                characters.push(Character(location(yloc, xloc), c));
            grid[yloc][xloc] = c;
            switch (c)
            {
            case 'H':
                h_count += 1;
                break;
            case 'R':
                r_count += 1;
                break;
            case 'I':
                i_count += 1;
                break;
            default:
                break;
            }
            break;
        }
        // cout<<"Cant find empty location"<<endl;
    }
}
char Map::getXY(int _y, int _x)
{
    if (_x > x || _y > y || _x < 1 || _y < 1)
    {
        cout << "Passed in values are out of bounds for the grid" << endl;
        return ' ';
    }
    return grid[y - 1][x - 1];
};
void Map::moveUp(location &l, Character ch)
{
    // cout<<"character " << ch.status<< " at "<<l.y <<", " << l.x << " with MP = " << ch.mp<< endl;
    if (l.y - 1 >= 0)
    {
        if (grid[l.y - 1][l.x] == ' ')
        {
            // cout << "\t"
            //      << "Moving Up " << ch.status << " done" << endl;
            l.increment(location(-1, 0));
            grid[l.y][l.x] = ch.status;
            grid[l.y + 1][l.x] = ' ';
        }
        else if (ch.status == 'I' && grid[l.y - 1][l.x] == 'H')
        {
            bool shouldInfect = (rand() % 100) < ir * 100; // shouldInfect will be true with a probability of ir
            if (shouldInfect)
            {
                grid[l.y - 1][l.x] = 'I';
                node *n = characters.find(location(l.y - 1, l.x));
                n->data.status = 'I';
                h_count--;
                i_count++;
                // cout << "H at " << l.y - 1 << ", " << l.x << " has turned into an I" << endl;
            }
        }
        else if (ch.status == 'H' && grid[l.y - 1][l.x] == 'I')
        {
            bool shouldInfect = (rand() % 100) < ir * 100; // shouldInfect will be true with a probability of ir
            if (shouldInfect)
            {
                grid[l.y][l.x] = 'I';
                node *n = characters.find(location(l.y, l.x));
                n->data.status = 'I';
                h_count--;
                i_count++;
                // cout << "H at " << l.y << ", " << l.x << " has turned into an I" << endl;
            }
        }
    }
};
void Map::moveDown(location &l, Character ch)
{
    // cout<<"character " << ch.status<< " at "<<l.y <<", " << l.x << " with MP = " << ch.mp<< endl;
    if (l.y + 1 <= y - 1)
    {
        if (grid[l.y + 1][l.x] == ' ')
        {
            // cout << "\t"
            //      << "Moving Down " << ch.status << " done" << endl;
            l.increment(location(1, 0));
            grid[l.y][l.x] = ch.status;
            grid[l.y - 1][l.x] = ' ';
        }
        else if (ch.status == 'I' && grid[l.y + 1][l.x] == 'H')
        {
            bool shouldInfect = (rand() % 100) < ir * 100; // shouldInfect will be true with a probability of ir
            if (shouldInfect)
            {
                grid[l.y + 1][l.x] = 'I';
                node *n = characters.find(location(l.y + 1, l.x));
                n->data.status = 'I';
                h_count--;
                i_count++;
                // cout << "H at " << l.y + 1 << ", " << l.x << " has turned into an I" << endl;
            }
        }
        else if (ch.status == 'H' && grid[l.y + 1][l.x] == 'I')
        {
            bool shouldInfect = (rand() % 100) < ir * 100; // shouldInfect will be true with a probability of ir
            if (shouldInfect)
            {
                grid[l.y][l.x] = 'I';
                node *n = characters.find(location(l.y, l.x));
                n->data.status = 'I';
                h_count--;
                i_count++;
                // cout << "H at " << l.y << ", " << l.x << " has turned into an I" << endl;
            }
        }
    }
};
void Map::moveRight(location &l, Character ch)
{
    // cout<<"character " << ch.status<< " at "<<l.y <<", " << l.x << " with MP = " << ch.mp<< endl;
    if (l.x + 1 <= x - 1)
    {
        if (grid[l.y][l.x + 1] == ' ')
        {
            // cout << "\t"
            //      << "Moving Right " << ch.status << " done" << endl;
            l.increment(location(0, 1));
            grid[l.y][l.x] = ch.status;
            grid[l.y][l.x - 1] = ' ';
        }
        else if (ch.status == 'I' && grid[l.y][l.x + 1] == 'H')
        {
            bool shouldInfect = (rand() % 100) < ir * 100; // shouldInfect will be true with a probability of ir
            if (shouldInfect)
            {
                grid[l.y][l.x + 1] = 'I';
                node *n = characters.find(location(l.y, l.x + 1));
                n->data.status = 'I';
                h_count--;
                i_count++;
                //cout << "H at " << l.y << ", " << l.x + 1 << " has turned into an I" << endl;
            }
        }
        else if (ch.status == 'H' && grid[l.y][l.x + 1] == 'I')
        {
            bool shouldInfect = (rand() % 100) < ir * 100; // shouldInfect will be true with a probability of ir
            if (shouldInfect)
            {
                grid[l.y][l.x] = 'I';
                node *n = characters.find(location(l.y, l.x));
                n->data.status = 'I';
                h_count--;
                i_count++;
                //cout << "H at " << l.y << ", " << l.x << " has turned into an I" << endl;
            }
        }
    }
}
void Map::moveLeft(location &l, Character ch)
{
    // cout<<"character " << ch.status<< " at "<<l.y <<", " << l.x << " with MP = " << ch.mp<< endl;
    if (l.x - 1 >= 0)
    {
        if (grid[l.y][l.x - 1] == ' ')
        {
            // cout << "\t"
            //      << "Moving Left " << ch.status << " done" << endl;
            l.increment(location(0, -1));
            grid[l.y][l.x] = ch.status;
            grid[l.y][l.x + 1] = ' ';
        }
        else if (ch.status == 'I' && grid[l.y][l.x - 1] == 'H')
        {
            bool shouldInfect = (rand() % 100) < ir * 100; // shouldInfect will be true with a probability of ir
            if (shouldInfect)
            {
                grid[l.y][l.x - 1] = 'I';
                node *n = characters.find(location(l.y, l.x - 1));
                n->data.status = 'I';
                h_count--;
                i_count++;
                //cout << "H at " << l.y << ", " << l.x - 1 << " has turned into an I" << endl;
            }
        }
        else if (ch.status == 'H' && grid[l.y][l.x - 1] == 'I')
        {
            bool shouldInfect = (rand() % 100) < ir * 100; // shouldInfect will be true with a probability of ir
            if (shouldInfect)
            {
                grid[l.y][l.x] = 'I';
                node *n = characters.find(location(l.y, l.x));
                n->data.status = 'I';
                h_count--;
                i_count++;
                //cout << "H at " << l.y << ", " << l.x << " has turned into an I" << endl;
            }
        }
    }
}
void Map::makeMove(int moveSelector, location &l, Character ch)
{
    switch (moveSelector)
    {
    case 0:
        //cout << "Moving Up " << ch.status << " at " << l.y << ", " << l.x << endl;
        moveUp(l, ch);
        break;
    case 1:
        //cout << "Moving Down " << ch.status << " at " << l.y << ", " << l.x << endl;
        moveDown(l, ch);
        break;
    case 2:
        //cout << "Moving Right " << ch.status << " at " << l.y << ", " << l.x << endl;
        moveRight(l, ch);
        break;
    case 3:
        //cout << "Moving Left " << ch.status << " at " << l.y << ", " << l.x << endl;
        moveLeft(l, ch);
        break;
    case 4:
        //cout << "Not moving " << ch.status << " at " << l.y << ", " << l.x << endl;
        break;
    }
}
void Map::moveCharacters()
{
    for (node *n = characters.top; n != NULL; n = n->next)
    {
        //cout << "Node : " << n->data.status << " at " << n->data.l.y << ", " << n->data.l.x << endl;
        if(n == NULL){
            return;
        }
        // Check if infected character will recover or decease
        if (n->data.status == 'I')
        {
            bool shouldRecover = (rand() % 100) < rr * 100; // shouldInfect will be true with a probability of rr
            bool shouldDecease = (rand() % 100) < mr * 100; // shouldInfect will be true with a probability of mr
            //cout << "Recover ? : " << shouldRecover << " Die? : " << shouldDecease << endl;
            if (shouldRecover)
            {

                grid[n->data.l.y][n->data.l.x] = 'R';
                //cout << "Should Recover " << n->data.l.y << ", " << n->data.l.x << endl;
                node *node = characters.find(location(n->data.l.y, n->data.l.x));
                //cout << "Node Found" << endl;
                node->data.status = 'R';
                i_count--;
                r_count++;
                //cout << "I at " << n->data.l.y << ", " << n->data.l.x << " has turned into an R" << endl;
                shouldDecease = false;
            }
            if (shouldDecease)
            {
                //cout << "Should Die" << endl;
                grid[n->data.l.y][n->data.l.x] = ' ';
                // characters.remove(characters.findOffset(n->data.l));
                characters.remove1(n->data.l);
                //cout << "Stack Trace after removing said character : " << endl;
                //characters.display();
                i_count--;
                f_count++;
                //cout << "I at " << n->data.l.y << ", " << n->data.l.x << " has deceased" << endl;
                continue;
            }
        }
        int moveSelector;
        // Both the ch and l variables are created as pointers so that when they are passed to the move functions and updates are
        // done to them, the updates are reflected in the parent structures
        switch (mp)
        {
        case 0:
            moveUp(n->data.l, n->data);
            break;
        case 1:
            moveDown(n->data.l, n->data);
            break;
        case 2:
            moveRight(n->data.l, n->data);
            break;
        case 3:
            moveLeft(n->data.l, n->data);
            break;
        // Equal probabilities among moving in 4 directions and not moving at all
        case 4:
            moveSelector = rand() % 4;
            makeMove(moveSelector, n->data.l, n->data);
            break;
        case 5:
            moveSelector = rand() % 5;
            makeMove(moveSelector, n->data.l, n->data);
            break;
        // If MP is greater than 5, we calculate the stay move probabilities and make the move accordingly
        default:
            float stayProbability = float(mp - 4) / mp;
            bool shouldStay = (rand() % 100) < stayProbability * 100;
            if (shouldStay)
            {
                moveSelector = 4;
                makeMove(moveSelector, n->data.l, n->data);
                break;
            }
            else
            {
                moveSelector = rand() % 4;
                makeMove(moveSelector, n->data.l, n->data);
                break;
            }
        }
    }
}

class Simulation
{
public:
    int healthy;
    int recovered;
    int infected;
    int blocks;
    int fatalities;
    int y, x;
    float ir, mr, rr, mp;
    Map *map;
    Simulation(Map *_map, int _y, int _x, int _healthy, int _infected, int _blocks, float _ir, float _rr, float _mr, float _mp)
    {
        healthy = _healthy;
        infected = _infected;
        blocks = _blocks;
        recovered = 0;
        y = _y;
        x = _x;
        ir = _ir;
        mr = _mr;
        rr = _rr;
        mp = _mp;
        map = _map;
        initializeMap();
    }
    ~Simulation() {}
    void initializeMap()
    {
        for (int i = 0; i < blocks; ++i)
        {
            map->place('#');
        }

        for (int i = 0; i < healthy; ++i)
        {
            map->place('H');
        }

        for (int i = 0; i < infected; ++i)
        {
            map->place('I');
        }
        map->mp = mp;
        map->ir = ir;
        map->mr = mr;
        map->rr = rr;
    }
    int run(bool charwait = false, char * fileName = NULL )
    {
        cout << "Healthy : " << healthy << "\t"
             << " Infected : " << infected << "\t"
             << "Recovered : " << recovered << "\t" << endl;
        cout << "RR : " << rr << "\t"
             << "IR : " << ir << "\t"
             << "MP : " << mp << "\t"
             << "MR : " << mr << endl;
        cout << "Press any key to start simulation" << endl;
        char c;
        int simCount = 0;
            
        if(charwait){
            while (map->i_count > 0)
            {
                c = getchar();
                if (c == 'q' || c == 'Q')
                {
                    break;
                }
                map->moveCharacters();
                if( c == 's' || c == 'S'){
                    if(fileName != NULL){ 
                    ofstream fout(fileName,std::ios_base::app);
                    fout << y << endl;
                    fout << x << endl;
                    fout << ir << endl;
                    fout << rr << endl;
                    fout << mr << endl;
                    fout << mp << endl;
                    for( int i = 0; i < y ; ++i){
                        for(int j = 0 ; j < x; ++j){
                            if(map->grid[i][j] == ' '){
                                fout<<'_';
                            }
                            else
                                fout<<map->grid[i][j];
                        }
                        fout<<endl;
                    }
                    fout.close();
                    }
                }
                // system("clear");
                map->displayMap(++simCount);
                //map->characters.display();
            }
            return map->f_count;
        }
        else{
            while(map->i_count > 0){
                //system("clear");
                map->moveCharacters();
                if(simCount == 0){
                    map->displayMap(++simCount);
                }
                else{
                    ++simCount;
                }
                //map->characters.display();
            }
            map->displayMap(simCount);
            return map->f_count;
        }
    }
};


float runSimulation(int sims,int _y, int _x, int _healthy, int _infected, int _blocks, float _ir, float _rr, float _mr, float _mp){
    const int size = sims;
    float fatalities = 0.0;
    int fatality;
    for (int i = 0; i < sims ; ++i){
        Map map(_y,_x);
        Simulation sim(&map,_y,_x,_healthy, _infected, _blocks, _ir, _rr, _mr, _mp);
        fatality = sim.run();
        //cout<<fatality<<"\t";
        fatalities += fatality;
    }
    return float(fatalities/size);
}

int main(int argc, const char *argv[])
{
    srand((unsigned int)time(NULL));
    int x,y,blocks=0,spaces=0;
    string line;
    float avg;
    ifstream fin("map.txt");
    fin>>x>>y;
    cout<<"X,Y : "<<x<<", "<<y<<endl;
    while(fin >> line){
        for(int i = 0; i< line.size(); ++i){
            if(line[i] == '_')
                spaces++;
            else if(line[i] == '#')
                blocks++;
        }
    }
    cout<<"Blocks and Spaces : "<< blocks << ", "<< spaces<<endl;
    fin.close();

    Map map(y, x);
    Simulation sim(&map, y, x, 95, 5, blocks, 0.5, 0.1, 0.05, 5); // Simulation(Map * _map, int _y, int _x, int _healthy, int _infected, int _blocks, float _ir, float _rr, float _mr, float _mp)
    sim.run();

    srand((unsigned int)time(NULL)*0.1);
    avg = runSimulation(1000 ,y, x, 95, 5, blocks, 0.5, 0.1, 0.05, 5);
    cout<<endl<<"Average Fatalities for map config from input file with MP = 5 : "<<avg<<endl;


    //Part iii - Write the contents of a simulation into a file
    // The simulation::run function has been changed to accept an ofstream object to write into 
    Map map1(y, x);
    Simulation sim1(&map1, y, x, 95, 5, blocks, 0.5, 0.1, 0.05, 5); // Simulation(Map * _map, int _y, int _x, int _healthy, int _infected, int _blocks, float _ir, float _rr, float _mr, float _mp)
    char* fileName = "simulationData.txt";
    sim1.run(true,fileName);


    return 0;
}

// int main(int argc, const char *argv[])
// {
//     srand((unsigned int)time(NULL));
//     int x,y;
//     ifstream fin("map.txt");
//     fin>>x>>y;
//     cout<<"X,Y : "<<x<<", "<<y;
//     return 0;
// }

