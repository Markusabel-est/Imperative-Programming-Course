#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>

using namespace std;

const char ICE_CELL = '.';
const char ROCK_CELL = 'r';
const char FLAMINGO_CELL = 'f';
const char FLAMINGO_ON_RESCUE_CELL = 'F';
const char RESCUE_CELL = 'x';
const char UNKNOWN_CELL = '?';

enum Action
{
    MoveNorth,
    MoveEast,
    MoveSouth,
    MoveWest,
    Reset,
    Quit,
    Invalid
};

struct Cell {
    char type; 
};

struct Puzzle
{
    int rows, cols;               
    vector<vector<Cell>> cells; 
};

bool operator== (const Puzzle& lhs, const Puzzle& rhs)
{// Precondition:
    assert (true);
/*  Postcondition: return value is true if `lhs` and `rhs` have the same puzzle state
*/
    if(lhs.rows != rhs.rows){
        return false;
    }
    if(lhs.cols != rhs.cols){
        return false;
    }
    for(int i = 0; i < lhs.rows; i++){
        for(int k = 0; k < lhs.cols; k++){
            if(lhs.cells[i][k].type != rhs.cells[i][k].type ){
                return false;
            }
        }
    }

    // TODO: implement this function
    return true;
}

bool operator!= (const Puzzle& lhs, const Puzzle& rhs)
{// Precondition:
    assert (true);
/*  Postcondition: return value is true if `!(lhs == rhs)`
*/
    return !(lhs == rhs);
}

bool is_solved (const Puzzle& puzzle)
{// Precondition:
    assert (true);
/*  Postcondition: return value is true if the flamingo is at a rescue position in `puzzle`
*/
    for (int i = 0; i < puzzle.rows; ++i) {
        for (int j = 0; j < puzzle.cols; ++j) {
            if (puzzle.cells[i][j].type == FLAMINGO_ON_RESCUE_CELL) {
                return true; 
            }
        }
    }
    return false; 
}

bool is_solvable (const Puzzle& puzzle)
{// Precondition:
    assert (true);
/*  Postcondition: return value is true if the flamingo in `puzzle` is still on the ice floe
*/
    for(int i = 0; i < puzzle.rows; i++){
        for(int k = 0; k < puzzle.cols; k++){
            if(puzzle.cells.at(i).at(k).type == FLAMINGO_CELL ){
                return true;
            }
        }
    }
    // TODO: implement this function
    return false;
}

ostream& operator<< (ostream& os, const Puzzle& puzzle)
{// Precondition:
    assert (true);
/*  Postcondition: `puzzle` has been printed to `os`
*/
    for(int i = 0; i < puzzle.rows; ++i) {
        for(int k = 0; k < puzzle.cols; ++k) {
            os << puzzle.cells[i][k].type;
        }
        os << endl;
    }
    // TODO: implement this function
    return os;
}

bool load_puzzle (const vector<vector<char>>& field, Puzzle& puzzle)
{// Precondition:
    assert (true);
/*  Postcondition: return value is true if `field` denotes a valid puzzle, in which case `field` has been parsed into `puzzle`
*/
    puzzle.rows = field.size();
    if(puzzle.rows <= 0) return false;

    puzzle.cols = field[0].size();
    if(puzzle.cols <= 0) return false;

    puzzle.cells.clear();
    bool has_flamingo = false;
    bool has_rescue = false;

    for(int i = 0; i < puzzle.rows; i++){
        
        vector<Cell> row;
        for (int k = 0; k < puzzle.cols; ++k) {
            char c = field[i][k];
            if (c != ICE_CELL && c != ROCK_CELL && c != FLAMINGO_CELL &&
                c != FLAMINGO_ON_RESCUE_CELL && c != RESCUE_CELL) {
                return false;
            }
            row.push_back({c});
            if (c == FLAMINGO_CELL || c == FLAMINGO_ON_RESCUE_CELL) {
                if (has_flamingo){ 
                    return false;
                }
                has_flamingo = true;
            }
            if (c == RESCUE_CELL || c == FLAMINGO_ON_RESCUE_CELL) {
                has_rescue = true;
            }
        }
        puzzle.cells.push_back(row);
    }
    // TODO: implement this function
    return has_flamingo && has_rescue;
}

void slide(Puzzle& puzzle, int start_row, int start_col, int diff_row, int diff_col)
{
    int row = start_row, col = start_col;
    puzzle.cells[row][col].type = ICE_CELL;

    while (true) {
        row += diff_row;
        col += diff_col;

        if (row < 0 || row >= puzzle.rows || col < 0 || col >= puzzle.cols) {
            return;
        }

        if (puzzle.cells[row][col].type == ROCK_CELL) {
            puzzle.cells[row - diff_row][col - diff_col].type = 'f';
            return;
        } else if (puzzle.cells[row][col].type == 'x') {
            puzzle.cells[row][col].type = 'F';
            return;
        }
    }
}

void move_north(Puzzle& puzzle)
{
    for (int i = 0; i < puzzle.rows; ++i) {
        for (int j = 0; j < puzzle.cols; ++j) {
            if (puzzle.cells[i][j].type == FLAMINGO_CELL) {
                slide(puzzle, i, j, -1, 0);
                return;
            }
        }
    }
}

void move_south(Puzzle& puzzle)
{
    for (int i = 0; i < puzzle.rows; ++i) {
        for (int j = 0; j < puzzle.cols; ++j) {
            if (puzzle.cells[i][j].type == FLAMINGO_CELL) {
                slide(puzzle, i, j, 1, 0);
                return;
            }
        }
    }
}

void move_west(Puzzle& puzzle)
{
    for (int i = 0; i < puzzle.rows; ++i) {
        for (int j = 0; j < puzzle.cols; ++j) {
            if (puzzle.cells[i][j].type == FLAMINGO_CELL) {
                slide(puzzle, i, j, 0, -1);
                return;
            }
        }
    }
}

void move_east(Puzzle& puzzle)
{
    for (int i = 0; i < puzzle.rows; ++i) {
        for (int j = 0; j < puzzle.cols; ++j) {
            if (puzzle.cells[i][j].type == FLAMINGO_CELL) {
                slide(puzzle, i, j, 0, 1);
                return;
            }
        }
    }
}

bool read_puzzle (istream& is, Puzzle& puzzle)
{// Precondition:
    assert (true);
/*  Postcondition: return value is true if a valid puzzle has been read from `is`, in which case it is stored in `puzzle`
*/
    vector<vector<char>> field;
    vector<char> line;
    char c;

    // Convert `is` to a 2d array of chars.
    while(is.get(c)) {
        if(c == '\n') {
            field.push_back(line);
            line = {};
        } else {
            line.push_back(c);
        }
    }

    if(!line.empty()) {
        field.push_back(line);
    }

    // Attempt to parse the 2d arrays of chars into a proper puzzle.
    return load_puzzle(field, puzzle);
}

bool open_puzzle (string file, Puzzle& puzzle)
{// Precondition:
    assert (true);
/*  Postcondition: return value is true if a puzzle has been successfully read from filename `file` into `puzzle`
*/
    ifstream fs(file);

    if(!fs.is_open()) {
        cout << "Failed to open file" << endl;
        return false;
    } else if(!read_puzzle(fs, puzzle)) {
        cout << "Failed to read puzzle" << endl;
        return false;
    }

    cout << "Loaded the puzzle shown below:\n";
    cout << puzzle << endl;

    return true;
}

Action get_action ()
{// Precondition:
    assert (true);
/*  Postcondition: return value is action chosen by user.
*/
    cout << "Pick an action: " << endl;
    cout << "'n': Move north" << endl;
    cout << "'e': Move east" << endl;
    cout << "'s': Move south" << endl;
    cout << "'w': Move west" << endl;
    cout << "'r': Reset" << endl;
    cout << "'q': Quit" << endl;
    cout << "> ";

    char c;
    cin >> c;

    switch(c) {
        case 'n': return MoveNorth;
        case 'e': return MoveEast;
        case 's': return MoveSouth;
        case 'w': return MoveWest;
        case 'r': return Reset;
        case 'q': return Quit;
        default:  return Invalid;
    }
}


#ifndef TESTING
int main ()
{// Precondition:
    assert (true);
/*  Postcondition: the user chosen puzzle file has been read and played.
*/
    string file;
    Puzzle puzzle;

    cout << "Enter file to open: ";
    getline(cin, file);

    if(!open_puzzle(file, puzzle)) {
        return 1;
    } else if(is_solved(puzzle)) {
        cout << "This puzzle is already solved!" << endl;
        return 0;
    }

    Puzzle initial_puzzle = puzzle;
    int steps = 0;
    Action action;

    while((action = get_action()) != Quit) {
        switch(action) {
            case MoveNorth:
                // TODO: move the flamingo to the north in `puzzle`
                steps++;
                break;
            case MoveEast:
                // TODO: move the flamingo to the east in `puzzle`
                steps++;
                break;
            case MoveSouth:
                // TODO: move the flamingo to the south in `puzzle`
                steps++;
                break;
            case MoveWest:
                // TODO: move the flamingo to the west in `puzzle`
                steps++;
                break;
            case Reset:
                puzzle = initial_puzzle;
                steps = 0;
                break;
            case Invalid:
            case Quit: // dummy case to suppress compiler warning
                cout << "Invalid action" << endl;
                break;
        }

        cout << puzzle << endl;

        if(is_solved(puzzle)) {
            cout << "Congratulations, you have completed the puzzle in " << steps << " step(s)!" << endl;
            return 0;
        } else if(!is_solvable(puzzle)) {
            cout << "Puzzle no longer solvable, resetting" << endl;
            puzzle = initial_puzzle;
            steps = 0;
            cout << puzzle << endl;
        }
    }

    return 0;
}
#endif
