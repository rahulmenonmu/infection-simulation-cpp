#include <iostream>


using namespace std;

class stack;
class Character;


class location {
public:
    int x, y;
public:
    location() {
        set(0, 0);
    }
    location(int _y, int _x) {
        set(_y, _x);
    }
    void set(int _y, int _x) {
        y = _y;
        x = _x;
    }
    void increment(location l) {
        x += l.x;
        y += l.y;
    }
};


class Character {
    public:
        location l;
        char status;
        Character() {};
        Character(location _l, char _status){
            l = _l;
            status = _status;
        }
};


class node {
public:
    Character data;
	node* next;
	node(Character _data) {
		data = _data;
		next = NULL;
	}
    char getCharacter(){
        return data.status;
    }
	friend class stack;
};


class stack { 
public: 
    node* top;
	stack() {
		top = NULL; 
	}
	void push(Character data) {
		node* n = new node(data);
		n->next = top; 
		top = n; 
	}
	bool pop(Character& data) {
		if (top == NULL) return false;
		node* n = top;
		top = top->next;
		data = n->data;
		delete n; 
		return true;
	}
	void display() {
		for (node* n = top; n != NULL; n = n->next)
			cout << n->getCharacter() << '\t';
		cout << endl;
	}
};




class Map
{
public:
    unsigned int x, y, h_count,i_count,r_count;
    char **grid;
    stack characters;
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
    cout<<endl<<"Frame : "<< frame<< " Healthy : " << h_count << "\t" << "Infected : " << i_count << "\t" << "Recovered : " << r_count<< "\t" << "MP : "<< mp << endl;

}
void Map::place(char c)
{
    unsigned int xloc, yloc;
    while(1){
        yloc = rand() % y;
        xloc = rand() % x;
        if(grid[yloc][xloc] == ' '){
            if(c != '#')
                characters.push(Character(location(yloc,xloc),c));
            grid[yloc][xloc] = c;
            switch(c){
                case 'H' :
                    h_count += 1;
                    break;
                case 'R' :
                    r_count += 1;
                    break;
                case 'I' :
                    i_count += 1;
                    break;
                default:
                    break;
            }
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
};
void Map::moveUp(location &l, Character ch){
    // cout<<"character " << ch.status<< " at "<<l.y <<", " << l.x << " with MP = " << ch.mp<< endl;
    if(l.y-1 >= 0){
        if(grid[l.y-1][l.x] == ' '){
            cout<<"\t"<<"Moving Up " << ch.status<< " done"<< endl;
            l.increment(location(-1,0));
            grid[l.y][l.x] = ch.status;
            grid[l.y+1][l.x] = ' ';
        } 
    }
};
void Map::moveDown(location &l, Character ch){
    // cout<<"character " << ch.status<< " at "<<l.y <<", " << l.x << " with MP = " << ch.mp<< endl;
    if(l.y+1 <= y-1){
        if(grid[l.y+1][l.x] == ' ' ){
            cout<<"\t"<<"Moving Down " << ch.status<< " done"<< endl;
            l.increment(location(1,0));
            grid[l.y][l.x] = ch.status;
            grid[l.y-1][l.x] = ' ';
        }
    }
};
void Map::moveRight(location &l, Character ch){
    // cout<<"character " << ch.status<< " at "<<l.y <<", " << l.x << " with MP = " << ch.mp<< endl;
    if(l.x+1 <= x-1){
        if(grid[l.y][l.x+1] == ' '){
            cout<<"\t"<<"Moving Right " << ch.status<< " done" << endl;
            l.increment(location(0,1));
            grid[l.y][l.x] = ch.status;
            grid[l.y][l.x-1] = ' ';
        }
    }
}
void Map::moveLeft(location &l, Character ch){
    // cout<<"character " << ch.status<< " at "<<l.y <<", " << l.x << " with MP = " << ch.mp<< endl;
    if(l.x-1 >= 0){
        if(grid[l.y][l.x-1] == ' '){
            cout<<"\t"<<"Moving Left " << ch.status<< " done" << endl;
            l.increment(location(0,-1));
            grid[l.y][l.x] = ch.status;
            grid[l.y][l.x+1] = ' ';
        }   
    }
}

void Map::makeMove(int moveSelector, location &l, Character ch){
    switch(moveSelector) {
        case 0:
            cout<<"Moving Up " << ch.status<< " at "<<l.y <<", " << l.x  << endl;
            moveUp(l,ch);
            break;
        case 1 : 
            cout<<"Moving Down " << ch.status<< " at "<<l.y <<", " << l.x  << endl;
            moveDown(l,ch);
            break;
        case 2 : 
            cout<<"Moving Right " << ch.status<< " at "<<l.y <<", " << l.x  << endl;
            moveRight(l,ch);
            break;
        case 3:
            cout<<"Moving Left " << ch.status<< " at "<<l.y <<", " << l.x  << endl;
            moveLeft(l,ch);
            break;
        case 4:
            cout<<"Not moving " << ch.status<< " at "<<l.y <<", " << l.x  << endl;
            break;
    }
}

void Map::moveCharacters(){
    for (node* n = characters.top; n != NULL; n = n->next){
            cout<<"Node : "<< n->data.status << " at " << n->data.l.y <<", " << n->data.l.x<<endl;
            int moveSelector;
            // Both the ch and l variables are created as pointers so that when they are passed to the move functions and updates are
            // done to them, the updates are reflected in the parent structures
            switch (mp) {
                case 0 :
                    moveUp(n->data.l,n->data);
                    break;
                case 1 :
                    moveDown(n->data.l,n->data);
                    break;
                case 2 :
                    moveRight(n->data.l,n->data);
                    break;
                case 3 :
                    moveLeft(n->data.l,n->data);
                    break;
                // Equal probabilities among moving in 4 directions and not moving at all
                case 4 :
                    moveSelector = rand() % 4;
                    makeMove(moveSelector,n->data.l,n->data);
                    break;
                case 5:
                    moveSelector = rand() % 5;
                    makeMove(moveSelector,n->data.l,n->data);
                    break;
                // If MP is greater than 5, we calculate the stay move probabilities and make the move accordingly
                default :
                    float stayProbability = (mp-4)/mp;
                    float moveProbability = 1/mp;
                    if(stayProbability >= moveProbability) {
                        moveSelector = 4;
                        makeMove(moveSelector,n->data.l,n->data);
                        break;
                    }
                    else{
                        moveSelector = rand() % 4;
                        makeMove(moveSelector,n->data.l,n->data);
                        break;
                    }
            }
    }
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
    map.mp = 4;
    for (int i = 0; i<12 ; ++i){
        map.place('#');
    }
    for (int i=0 ; i<3 ; ++i){
        map.place('H');
        map.place('I');
    }
    map.displayMap(1);
    cout<<endl<<"The MPs of the characters in the map are :"<<endl;
    map.characters.display();

    map.moveCharacters();
    map.displayMap(2);

    map.moveCharacters();
    map.displayMap(3);

    map.moveCharacters();
    map.displayMap(4);

    
    return 0;
}