#include <iostream>
#include <fstream>
#include <cassert>
#include <stdio.h>

using namespace std;

/***********************************************************
    Part 1: Pre- and postconditions
***********************************************************/
int compare (int a, int b)
{
    //Precondition:    
    assert(true);
    
    // Postcondition:
    // The result is -1, if 'a < b' 
    // The reuslt is 1, if 'a > b'
    // The result is 0, if 'a==b'


    if (a < b)
        return -1;
    if (a > b)
        return 1;
    return 0;
}

enum Direction {North, East, South, West};
bool opposite (Direction a, Direction& b)
{
    //Precondition
    assert(a >= North && b <= West);

    //Postcondition:
    // The result is true when a is North and b South
    // The result is false for every other case

    switch (a)
    {
        case North: b = South; return true;
        case East:  b = West;  break;
        case South: b = North; break;
        case West:  b = East;  break;
    }
    return false;
}

void write_numbers_to_file (int number, ofstream& out_file)
{
    
    //Precondition:
    assert(number >= 0 && out_file.is_open());

    //Postcondition:
    // The values starting from 'number' are written in decreassing order into the file
    while (number >= 0)
    {
        out_file << number << ' ';
        number--;
    }
}

void read_numbers_from_file (ifstream& infile)
{
    //Precondition:
    assert(infile.is_open());
    //Postcondition:
    // Writes out all the intgeres from the file in one

    int number;
    infile >> number;
    while (!infile.fail ())
    {
        cout << number;
        infile >> number;
    }
}

int compare (int a [], int b [], bool c [], int n)
{
    //Precondition
    assert(n >= 0);
    // returns the number of elements that have the same value in two arrays

    int x = 0;
    for (int i = 0; i < n; i++)
    {   if (a[i] == b[i])
        {
            c[i] = true;
            x++;
        }
        else
            c[i] = false;
    }
    return x;
}



/***********************************************************
    Part 2: Game of Life
***********************************************************/
enum Cell {Dead=0, Live};                         // a cell is either Dead or Live (we use the fact that dead = 0 and live = 1)

const char DEAD             = '.' ;               // the presentation of a dead cell (both on file and screen)
const char LIVE             = '*' ;               // the presentation of a live cell (both on file and screen)
const int NO_OF_ROWS        = 40 ;                // the number of rows (height) of the universe (both on file and screen)
const int NO_OF_COLUMNS     = 60 ;                // the number of columns (width) of the universe (both on file and screen)

// Part 2.1: Get cell in bounded universe
Cell cell_at (Cell universe [NO_OF_ROWS][NO_OF_COLUMNS], int row, int column)
{
    // pre-condition:
    assert(NO_OF_ROWS > 0 && NO_OF_COLUMNS > 0);
    //Postcondition:
    //  Retruns Value of exact cell if cell is in bounds and returns "dead " otherwise
    if (row < NO_OF_COLUMNS && column < NO_OF_ROWS && row >= 0 && column >= 0 ){
        return universe [row][column];
    }
    return Dead;
}

// Part 2.2: Setting the scene
bool read_universe_file (string filename, Cell universe [NO_OF_ROWS][NO_OF_COLUMNS])
{
    //Precondition:
    assert(NO_OF_COLUMNS > 0 && NO_OF_ROWS > 0 && filename != "");
    //Postcondition:
    // Returns true when the text file was successully iterated through and false otherwise
    
    
    int r = 0;
    int c = 0;
    string row;

    ifstream inFile; 

    inFile.open(filename);
    
    if (!inFile.is_open()) {
        return false;
    }

    //first extracts lines and then iterates through the lines 
    while(getline(inFile, row)){
        for( char iteration : row){
            if( iteration == DEAD){
                universe[r][c] = Dead;
            }
            if(iteration == LIVE){
                universe[r][c] = Live;
            }
            if(iteration != LIVE && iteration != DEAD){
                return false;
            }
            c++;

        }
        if(c != NO_OF_COLUMNS){
            return false;
        }
        c = 0;
        r++;
    }

    inFile.close();
    return true;
   
}

void show_universe (Cell universe [NO_OF_ROWS][NO_OF_COLUMNS])
{
   assert(NO_OF_ROWS > 0 && NO_OF_COLUMNS > 0);
   // Postcondition:
   // Writes out the whole array

    // outputs the given array
    for(int k = 0  ; k < NO_OF_ROWS; k++){
        for(int m = 0; m < NO_OF_COLUMNS; m++){
            cout << universe[k][m] << " ";
        }
        cout << endl;
    }
}

// Part 2.3: The next generation
void next_generation (Cell now [NO_OF_ROWS][NO_OF_COLUMNS], Cell next [NO_OF_ROWS][NO_OF_COLUMNS])
{
     assert(NO_OF_ROWS > 0 && NO_OF_COLUMNS > 0);
     //Postcondition:
     // Outputs a new generation
    
    for(int r = 0  ; r < NO_OF_ROWS; r++){
        for(int c = 0; c < NO_OF_COLUMNS; c++){
            
            int living = 0;

            //ceckes for the surounding cells
            for(int x = -1; x <= 1; x++ ){
                for (int y = -1; y <= 1; y++ ){
                    if(cell_at(now, r + y, c + x) == Live && !(x== 0 && y == 0)){
                        living ++;
                    }
                }
            }

            // checks for the game of life conditions
            if(cell_at(now, r, c) == Live){
                if(living < 2){
                    next[r][c] = Dead;
                }
                else if (living == 2 || living == 3){
                    next[r][c] = Live;
                }
                else if (living > 3){
                    next[r][c] = Dead;
                }

            }
            if(cell_at(now, r, c) == Dead){
                if(living == 3){
                    next[r][c] = Live;
                }
                else{
                    next[r][c] = Dead;
                }
            }
            
            
            
            
            
            

            
        }
        
    }
}

// Part 2.4: The final program
#ifndef TESTING
int main ()
{
    assert(NO_OF_COLUMNS > 0 && NO_OF_ROWS > 0);


    Cell universe [NO_OF_ROWS][NO_OF_COLUMNS];
    Cell next [NO_OF_ROWS][NO_OF_COLUMNS];

    string filename;
    cout << "input a filename" << endl;
    cin >> filename;

    read_universe_file(filename, universe);
    next_generation(universe, next);
    show_universe(next);

    return 0;




}
#endif
