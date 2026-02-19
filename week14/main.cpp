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

const int NO_SOLUTION = -1;     // Puzzle has no solution
const int BAD_FORMAT = -2;      // Puzzle field has an invalid format
const int NO_PARENT = -1;       // Index of the parent of the root candidate
const int NO_DEPTH_LIMIT = -1;  // Do not use a depth limit in depth first search

struct Cell {
    char type; 
};

struct Puzzle
{
    int rows, cols;               
    vector<vector<Cell>> cells; 
};

ostream& operator<< (ostream& os, const Puzzle& puzzle)
{// Precondition:
    assert (true);
/*  Postcondition: `puzzle` has been printed to `os`
*/
    for(int i = 0; i < puzzle.rows; ++i) {
        for(int k = 0; k <puzzle.cols; ++k) {
            os << puzzle.cells[i][k].type;
        }
        os << endl;
    }
    // TODO: implement this function
    return os;
}

vector<vector<char>> read_field (istream& is)
{// Precondition:
    assert (true);
/*  Postcondition: return value is the field that has been read from `is`
*/
    vector<vector<char>> field;
    vector<char> line;
    char c;

    // Convert `is` to a 2d array of chars.
    while(is.get(c)){
        if(c == '\n') {
            field.push_back(line);
            line = {};
        } 
        else{
            line.push_back(c);
        }
    }

    if(!line.empty()) {
        field.push_back(line);
    }

    return field;
}

bool is_valid_puzzle(const vector<vector<char>>&field) {
    assert(true);
    // Postcondition: return value is true if the field is a valid puzzle
    
    if (field.empty() ||field[0].empty()){
        return false;
    } 

    size_t width = field[0].size(); 
    int flamingo_count = 0; 
    int rescue_count = 0;

    for(const auto& row : field){
        if(row.size()!= width) return false;  
        for(char cell_type : row) {
            
            if(cell_type == FLAMINGO_CELL || cell_type == FLAMINGO_ON_RESCUE_CELL) flamingo_count++;
            if(cell_type == RESCUE_CELL || cell_type == FLAMINGO_ON_RESCUE_CELL) rescue_count++;
            if(cell_type != ICE_CELL && 
                cell_type != ROCK_CELL && 
                cell_type != FLAMINGO_CELL && 
                cell_type != RESCUE_CELL && 
                cell_type != FLAMINGO_ON_RESCUE_CELL
            ) 
            return false;  
        }
    }

    return flamingo_count == 1 && rescue_count > 0;
}

Puzzle convert_to_puzzle(const vector<vector<char>>& field) {
    assert(true);
    //Postcondition: return value is the puzzle that has been converted from the field
    
    Puzzle puzzle;
    puzzle.rows=field.size();
    puzzle.cols=field[0].size();
    puzzle.cells = vector<vector<Cell>>(puzzle.rows); 
    for (int i = 0; i < puzzle.rows; i++) {
        puzzle.cells[i] = vector<Cell>(puzzle.cols); 
    }
    for (int i = 0; i < puzzle.rows; i++) {
        for (int j = 0;j< puzzle.cols; j++){
            puzzle.cells[i][j].type = field[i][j];  
        }
    }

    return puzzle;
}

struct PuzzleState{
    Puzzle puzzle;         
    int parent_index;      

    PuzzleState(const Puzzle& p, int parent) {
        puzzle= p;
        parent_index = parent;
    }
};

struct Position {
    int row;
    int col;
};

Position find_flamingo(const Puzzle& puzzle) {
    assert(true);
    // Postcondition: return value is the row, col of the flamingo in `puzzle`
    
    for (int i = 0;i<puzzle.rows;i++) {
        for (int j = 0;j<puzzle.cols;j++) {
            if (puzzle.cells[i][j].type == FLAMINGO_CELL||puzzle.cells[i][j].type == FLAMINGO_ON_RESCUE_CELL){
                return {i, j};  
            }
        }
    }
    
}

bool is_solved(const Puzzle& puzzle) {
    assert(true);
    // Postcondition: return value is true if the flamingo is at a rescue position in `puzzle`
    
    for (int i = 0;i < puzzle.rows;i++) {
        for (int j = 0;j < puzzle.cols;j++) {
            if (puzzle.cells[i][j].type == FLAMINGO_CELL||puzzle.cells[i][j].type == RESCUE_CELL) {
                return false; 
            }
        }
    }
    return true;
}

vector<Puzzle> get_next_states(const Puzzle& current) {
    assert(true);
    // Postcondition: the next states have been generated from the current state

    vector<Puzzle> next_states;
    Position flamingo_pos = find_flamingo(current);

    int row = flamingo_pos.row;
    int col = flamingo_pos.col;
    const int dr[] = {-1, 0, 1, 0};
    const int dc[] = {0, 1, 0, -1};

    
    for (int i = 0; i < 4; i++){
        int new_row = row + dr[i];
        int new_col = col + dc[i];
        if (new_row >= 0&& new_row < current.rows && 
            new_col >= 0&& new_col < current.cols && 
            current.cells[new_row][new_col].type != ROCK_CELL){

            Puzzle next =current;
            if(current.cells[row][col].type == FLAMINGO_ON_RESCUE_CELL) {
                next.cells[row][col].type = RESCUE_CELL; 
            } 
            else{
                next.cells[row][col].type = ICE_CELL;    
            }


            if(next.cells[new_row][new_col].type == RESCUE_CELL){
                next.cells[new_row][new_col].type = FLAMINGO_ON_RESCUE_CELL; 
            } 
            else {
                next.cells[new_row][new_col].type = FLAMINGO_CELL; 
            }
            next_states.push_back(next);
        }
    }
    return next_states;
}

void extract_path(const vector<PuzzleState>& candidates, int index, vector<Puzzle>& path) {

    assert(true);
    // Postcondition: the solution path has been extracted from the candidates list
    if (index == -1){
        return;  
    } 
    path.push_back(candidates[index].puzzle);
}

int breadth_first(const vector<vector<char>>& field, vector<Puzzle>& solution_path) {
    assert(true);
    /* Postcondition: return value is the minimal number of steps needed to solve the puzzle represented by `field` in which case `solution_path`
    will contain the solution path, or `BAD_FORMAT` if `field` does not represent a valid puzzle, or `NO_SOLUTION` if the puzzle has no solutions
    */
    if (!is_valid_puzzle(field)) {
        return BAD_FORMAT;  
    }


    Puzzle initial = convert_to_puzzle(field);

    PuzzleState initial_state(initial, -1);

    vector<PuzzleState> candidates;
    candidates.push_back(initial_state);

    for (size_t i = 0;i < candidates.size();i++) {
        if (is_solved(candidates[i].puzzle)){
            solution_path.clear();

            extract_path (candidates, i, solution_path);
            return solution_path.size() - 1;  
        }

        vector<Puzzle> next_states = get_next_states(candidates[i].puzzle);
        for (const Puzzle& next : next_states) {
            PuzzleState next_state (next, i);
            candidates.push_back(next_state);
        }
    }

    return NO_SOLUTION;
}




int depth_first_helper(const Puzzle& puzzle,vector<Puzzle>& path, int depth_limit, int current_depth) 
{    // Precondition:
    assert(true);
/*  Postcondition: returns the minimal number of steps needed to solve the puzzle starting from the current state,
    or NO_SOLUTION if no solution exists within depth_limit. The solution path is stored in path vector.
*/
    if(depth_limit != NO_DEPTH_LIMIT && current_depth > depth_limit){
        return NO_SOLUTION;
    }
    
    if(is_solved(puzzle) == true){
        path.push_back(puzzle);
        return current_depth;
    }

    vector<Puzzle> next_moves = get_next_states(puzzle);
    
    for (int i = 0;i < next_moves.size();i++){
        path.push_back(puzzle);
        int found = depth_first_helper(next_moves[i], path,depth_limit, current_depth + 1);
        if(found != NO_SOLUTION) {
            return found;
        }
        path.pop_back();
    }
    
    return NO_SOLUTION;
}

int depth_first (const vector<vector<char>>& field, vector<Puzzle>& solution_path, int depth_limit)
{// Precondition:
    assert (true);
/*  Postcondition: return value is the minimal number of steps needed to solve the puzzle represented by `field` in which case `solution_path`
    will contain the solution path, or `BAD_FORMAT` if `field` does not represent a valid puzzle, or `NO_SOLUTION` if the puzzle has no solutions
*/
    if (!is_valid_puzzle(field)) {
        return BAD_FORMAT;
    }
    Puzzle start_puzzle= convert_to_puzzle(field);
    
    solution_path.clear();
    
    int result= depth_first_helper(start_puzzle, solution_path, depth_limit, 0);
    if(result != NO_SOLUTION) {
        return result;
    }
    solution_path.clear();

    return NO_SOLUTION;
}


/*
 * Main
 */

#ifndef TESTING
int main ()
{// Precondition:
    assert (true);
/*  Postcondition: the user chosen puzzle file has been read and a solution path printed to `cout` if one exists
*/
    string filename, algorithm;
    int depth_limit, steps;
    vector<Puzzle> solution_path;

    cout << "Enter file to open: ";
    getline(cin, filename);

    ifstream puzzle_file(filename);

    if(!puzzle_file.is_open()) {
        cout << "Failed to open file" << endl;
        return 1;
    }

    vector<vector<char>> field = read_field(puzzle_file);

    cout << "Enter algorithm (dfs/bfs): ";
    getline(cin, algorithm);

    if(algorithm == "dfs") {
        cout << "Enter depth limit (" << NO_DEPTH_LIMIT << " = no limit): ";
        cin >> depth_limit;

        steps = depth_first(field, solution_path, depth_limit);
    } else if(algorithm == "bfs") {
        steps = breadth_first(field, solution_path);
    } else {
        cout << "Unknown algorithm" << endl;
        return 2;
    }

    if(steps == BAD_FORMAT) {
        cout << "Puzzle configuration is not valid" << endl;
    } else if(steps == NO_SOLUTION) {
        cout << "No solution found" << endl;
    } else {
        for(int i = 0; i < ssize(solution_path); i++) {
            cout << solution_path.at(i) << endl;
        }

        cout << "Found solution in " << steps << " step(s)" << endl;
    }

    return 0;
}
#endif
