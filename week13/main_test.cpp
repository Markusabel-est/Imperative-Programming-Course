#include "main.cpp"
#include "gtest/gtest.h"

#include <sstream>

// Invalid character '?'
const vector<vector<char>> BAD_FORMAT_1 = {
    {'.', '.', '.'},
    {'.', 'f', '.'},
    {'.', '.', '?'}
};
// Mismatching number of columns in rows
const vector<vector<char>> BAD_FORMAT_2 = {
    {'.', '.', '.'},
    {'.', 'f', '.', '.'},
    {'.', '.', '.'}
};
// No flamingo or rescue locations
const vector<vector<char>> BAD_FORMAT_3 = {
    {'.', '.', '.'},
    {'.', '.', '.'},
    {'.', '.', '.'}
};
// Multiple flamingos and no rescue locations
const vector<vector<char>> BAD_FORMAT_4 = {
    {'.', '.', '.'},
    {'.', 'f', '.'},
    {'.', '.', 'f'}
};
// Multiple flamingos
const vector<vector<char>> BAD_FORMAT_5 = {
    {'r', '.', '.'},
    {'.', 'f', '.'},
    {'.', '.', 'f'}
};
// No rescue location
const vector<vector<char>> BAD_FORMAT_6 = {
    {'.', '.', '.'},
    {'.', '.', '.'},
    {'.', '.', 'f'}
};
const vector<vector<char>> TEST_CHALLENGE_1 = {
    {'x','.','r','.','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'r','.','f','.','.','.','r'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'.','.','r','.','.','.','.'}
};
const vector<vector<char>> TEST_CHALLENGE_1_n = {
    {'x','.','r','.','.','.','.'},
    {'.','.','f','.','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'r','.','.','.','.','.','r'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'.','.','r','.','.','.','.'}
};
const vector<vector<char>> TEST_CHALLENGE_1_e = {
    {'x','.','r','.','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'r','.','.','.','.','f','r'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'.','.','r','.','.','.','.'}
};
const vector<vector<char>> TEST_CHALLENGE_1_s = {
    {'x','.','r','.','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'r','.','.','.','.','.','r'},
    {'.','.','.','.','.','.','.'},
    {'.','.','f','.','.','.','.'},
    {'.','.','r','.','.','.','.'}
};
const vector<vector<char>> TEST_CHALLENGE_1_w = {
    {'x','.','r','.','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'r','f','.','.','.','.','r'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'.','.','r','.','.','.','.'}
};
const vector<vector<char>> TEST_CHALLENGE_2 = {
    {'x','.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','r','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.','.'},
    {'.','r','.','.','.','.','f','.','.','r','.'},
    {'.','.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','r','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.','.'}
};
const vector<vector<char>> TEST_CHALLENGE_2_n = {
    {'x','.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','r','.','.','.','.'},
    {'.','.','.','.','.','.','f','.','.','.','.'},
    {'.','r','.','.','.','.','.','.','.','r','.'},
    {'.','.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','r','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.','.'}
};
const vector<vector<char>> TEST_CHALLENGE_2_e = {
    {'x','.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','r','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.','.'},
    {'.','r','.','.','.','.','.','.','f','r','.'},
    {'.','.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','r','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.','.'}
};
const vector<vector<char>> TEST_CHALLENGE_2_s = {
    {'x','.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','r','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.','.'},
    {'.','r','.','.','.','.','.','.','.','r','.'},
    {'.','.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','f','.','.','.','.'},
    {'.','.','.','.','.','.','r','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.','.'}
};
const vector<vector<char>> TEST_CHALLENGE_2_w = {
    {'x','.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','r','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.','.'},
    {'.','r','f','.','.','.','.','.','.','r','.'},
    {'.','.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','r','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.','.'}
};
const vector<vector<char>> TEST_CHALLENGE_3 = {
    {'.','.','.','.','.'},
    {'.','.','x','.','.'},
    {'.','x','f','x','.'},
    {'.','.','x','.','.'},
    {'.','.','.','.','.'}
};
const vector<vector<char>> TEST_CHALLENGE_3_n = {
    {'.','.','.','.','.'},
    {'.','.','F','.','.'},
    {'.','x','.','x','.'},
    {'.','.','x','.','.'},
    {'.','.','.','.','.'}
};
const vector<vector<char>> TEST_CHALLENGE_3_e = {
    {'.','.','.','.','.'},
    {'.','.','x','.','.'},
    {'.','x','.','F','.'},
    {'.','.','x','.','.'},
    {'.','.','.','.','.'}
};
const vector<vector<char>> TEST_CHALLENGE_3_s = {
    {'.','.','.','.','.'},
    {'.','.','x','.','.'},
    {'.','x','.','x','.'},
    {'.','.','F','.','.'},
    {'.','.','.','.','.'}
};
const vector<vector<char>> TEST_CHALLENGE_3_w = {
    {'.','.','.','.','.'},
    {'.','.','x','.','.'},
    {'.','F','.','x','.'},
    {'.','.','x','.','.'},
    {'.','.','.','.','.'}
};
const vector<vector<char>> TEST_CHALLENGE_4 = {
    {'.','.','.','.','.','.','.'},
    {'.','.','.','x','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'.','x','.','f','.','x','.'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','x','.','.','.'},
    {'.','.','.','.','.','.','.'}
};
const vector<vector<char>> TEST_CHALLENGE_4_n = {
    {'.','.','.','.','.','.','.'},
    {'.','.','.','F','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'.','x','.','.','.','x','.'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','x','.','.','.'},
    {'.','.','.','.','.','.','.'}
};
const vector<vector<char>> TEST_CHALLENGE_4_e = {
    {'.','.','.','.','.','.','.'},
    {'.','.','.','x','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'.','x','.','.','.','F','.'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','x','.','.','.'},
    {'.','.','.','.','.','.','.'}
};
const vector<vector<char>> TEST_CHALLENGE_4_s = {
    {'.','.','.','.','.','.','.'},
    {'.','.','.','x','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'.','x','.','.','.','x','.'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','F','.','.','.'},
    {'.','.','.','.','.','.','.'}
};
const vector<vector<char>> TEST_CHALLENGE_4_w = {
    {'.','.','.','.','.','.','.'},
    {'.','.','.','x','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'.','F','.','.','.','x','.'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','x','.','.','.'},
    {'.','.','.','.','.','.','.'}
};
const vector<vector<char>> TEST_CHALLENGE_5 = {
    {'.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','r','.','.','.','.'},
    {'.','.','.','.','x','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.'},
    {'.','r','x','.','f','.','x','r','.'},
    {'.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','x','.','.','.','.'},
    {'.','.','.','.','r','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.'}
};
const vector<vector<char>> TEST_CHALLENGE_5_n = {
    {'.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','r','.','.','.','.'},
    {'.','.','.','.','F','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.'},
    {'.','r','x','.','.','.','x','r','.'},
    {'.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','x','.','.','.','.'},
    {'.','.','.','.','r','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.'}
};
const vector<vector<char>> TEST_CHALLENGE_5_e = {
    {'.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','r','.','.','.','.'},
    {'.','.','.','.','x','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.'},
    {'.','r','x','.','.','.','F','r','.'},
    {'.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','x','.','.','.','.'},
    {'.','.','.','.','r','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.'}
};
const vector<vector<char>> TEST_CHALLENGE_5_s = {
    {'.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','r','.','.','.','.'},
    {'.','.','.','.','x','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.'},
    {'.','r','x','.','.','.','x','r','.'},
    {'.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','F','.','.','.','.'},
    {'.','.','.','.','r','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.'}
};
const vector<vector<char>> TEST_CHALLENGE_5_w = {
    {'.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','r','.','.','.','.'},
    {'.','.','.','.','x','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.'},
    {'.','r','F','.','.','.','x','r','.'},
    {'.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','x','.','.','.','.'},
    {'.','.','.','.','r','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.'}
};

/***********************************************************
    Loading tests
***********************************************************/
TEST(loading, bad_format_1)
{
    Puzzle puzzle;
    EXPECT_FALSE(load_puzzle(BAD_FORMAT_1, puzzle));
}

TEST(loading, bad_format_2)
{
    Puzzle puzzle;
    EXPECT_FALSE(load_puzzle(BAD_FORMAT_2, puzzle));
}

TEST(loading, bad_format_3)
{
    Puzzle puzzle;
    EXPECT_FALSE(load_puzzle(BAD_FORMAT_3, puzzle));
}

TEST(loading, bad_format_4)
{
    Puzzle puzzle;
    EXPECT_FALSE(load_puzzle(BAD_FORMAT_4, puzzle));
}

TEST(loading, bad_format_5)
{
    Puzzle puzzle;
    EXPECT_FALSE(load_puzzle(BAD_FORMAT_5, puzzle));
}

TEST(loading, bad_format_6)
{
    Puzzle puzzle;
    EXPECT_FALSE(load_puzzle(BAD_FORMAT_6, puzzle));
}

TEST(loading, test_challenge_1)
{
    Puzzle puzzle;
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_1, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_1_n, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_1_e, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_1_s, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_1_w, puzzle));
}

TEST(loading, test_challenge_2)
{
    Puzzle puzzle;
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_2, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_2_n, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_2_e, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_2_s, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_2_w, puzzle));
}

TEST(loading, test_challenge_3)
{
    Puzzle puzzle;
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_3, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_3_n, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_3_e, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_3_s, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_3_w, puzzle));
}

TEST(loading, test_challenge_4)
{
    Puzzle puzzle;
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_4, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_4_n, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_4_e, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_4_s, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_4_w, puzzle));
}

TEST(loading, test_challenge_5)
{
    Puzzle puzzle;
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_5, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_5_n, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_5_e, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_5_s, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_5_w, puzzle));
}

/***********************************************************
    Output tests
***********************************************************/
TEST(output, test_challenge_1)
{
    Puzzle puzzle;
    stringstream ss;
    string EXPECTED = "x.r....\n"
                      ".......\n"
                      ".......\n"
                      ".......\n"
                      ".......\n"
                      "r.f...r\n"
                      ".......\n"
                      ".......\n"
                      "..r....\n";

    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_1, puzzle));
    ss << puzzle;
    EXPECT_EQ(ss.str(), EXPECTED);
}

TEST(output, test_challenge_2)
{
    Puzzle puzzle;
    stringstream ss;
    string EXPECTED = "x..........\n"
                      "......r....\n"
                      "...........\n"
                      ".r....f..r.\n"
                      "...........\n"
                      "...........\n"
                      "...........\n"
                      "......r....\n"
                      "...........\n";

    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_2, puzzle));
    ss << puzzle;
    EXPECT_EQ(ss.str(), EXPECTED);
}

TEST(output, test_challenge_3)
{
    Puzzle puzzle;
    stringstream ss;
    string EXPECTED = ".....\n"
                      "..x..\n"
                      ".xfx.\n"
                      "..x..\n"
                      ".....\n";

    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_3, puzzle));
    ss << puzzle;
    EXPECT_EQ(ss.str(), EXPECTED);
}

TEST(output, test_challenge_4)
{
    Puzzle puzzle;
    stringstream ss;
    string EXPECTED = ".......\n"
                      "...x...\n"
                      ".......\n"
                      ".x.f.x.\n"
                      ".......\n"
                      "...x...\n"
                      ".......\n";

    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_4, puzzle));
    ss << puzzle;
    EXPECT_EQ(ss.str(), EXPECTED);
}

TEST(output, test_challenge_5)
{
    Puzzle puzzle;
    stringstream ss;
    string EXPECTED = ".........\n"
                      "....r....\n"
                      "....x....\n"
                      ".........\n"
                      ".rx.f.xr.\n"
                      ".........\n"
                      "....x....\n"
                      "....r....\n"
                      ".........\n";

    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_5, puzzle));
    ss << puzzle;
    EXPECT_EQ(ss.str(), EXPECTED);
}

TEST(output, test_challenge_5_n)
{
    Puzzle puzzle;
    stringstream ss;
    string EXPECTED = ".........\n"
                      "....r....\n"
                      "....F....\n"
                      ".........\n"
                      ".rx...xr.\n"
                      ".........\n"
                      "....x....\n"
                      "....r....\n"
                      ".........\n";

    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_5_n, puzzle));
    ss << puzzle;
    EXPECT_EQ(ss.str(), EXPECTED);
}

/***********************************************************
    Is solved tests
***********************************************************/
TEST(is_solved, test_challenge_1)
{
    Puzzle puzzle;

    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_1, puzzle));
    EXPECT_FALSE(is_solved(puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_1_n, puzzle));
    EXPECT_FALSE(is_solved(puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_1_e, puzzle));
    EXPECT_FALSE(is_solved(puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_1_s, puzzle));
    EXPECT_FALSE(is_solved(puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_1_w, puzzle));
    EXPECT_FALSE(is_solved(puzzle));
}

TEST(is_solved, test_challenge_2)
{
    Puzzle puzzle;

    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_2, puzzle));
    EXPECT_FALSE(is_solved(puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_2_n, puzzle));
    EXPECT_FALSE(is_solved(puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_2_e, puzzle));
    EXPECT_FALSE(is_solved(puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_2_s, puzzle));
    EXPECT_FALSE(is_solved(puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_2_w, puzzle));
    EXPECT_FALSE(is_solved(puzzle));
}

TEST(is_solved, test_challenge_3)
{
    Puzzle puzzle;

    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_3, puzzle));
    EXPECT_FALSE(is_solved(puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_3_n, puzzle));
    EXPECT_TRUE(is_solved(puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_3_e, puzzle));
    EXPECT_TRUE(is_solved(puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_3_s, puzzle));
    EXPECT_TRUE(is_solved(puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_3_w, puzzle));
    EXPECT_TRUE(is_solved(puzzle));
}

TEST(is_solved, test_challenge_4)
{
    Puzzle puzzle;

    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_4, puzzle));
    EXPECT_FALSE(is_solved(puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_4_n, puzzle));
    EXPECT_TRUE(is_solved(puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_4_e, puzzle));
    EXPECT_TRUE(is_solved(puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_4_s, puzzle));
    EXPECT_TRUE(is_solved(puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_4_w, puzzle));
    EXPECT_TRUE(is_solved(puzzle));
}

TEST(is_solved, test_challenge_5)
{
    Puzzle puzzle;

    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_5, puzzle));
    EXPECT_FALSE(is_solved(puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_5_n, puzzle));
    EXPECT_TRUE(is_solved(puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_5_e, puzzle));
    EXPECT_TRUE(is_solved(puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_5_s, puzzle));
    EXPECT_TRUE(is_solved(puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_5_w, puzzle));
    EXPECT_TRUE(is_solved(puzzle));
}

/***********************************************************
    Move north tests
***********************************************************/
TEST(move_north, test_challenge_1)
{
    Puzzle puzzle;
    Puzzle expected;

    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_1, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_1_n, expected));
    move_north(puzzle);
    EXPECT_EQ(puzzle, expected);
    move_north(puzzle);
    EXPECT_EQ(puzzle, expected);
}

TEST(move_north, test_challenge_2)
{
    Puzzle puzzle;
    Puzzle expected;

    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_2, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_2_n, expected));
    move_north(puzzle);
    EXPECT_EQ(puzzle, expected);
    move_north(puzzle);
    EXPECT_EQ(puzzle, expected);
}

TEST(move_north, test_challenge_3)
{
    Puzzle puzzle;
    Puzzle expected;

    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_3, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_3_n, expected));
    move_north(puzzle);
    EXPECT_EQ(puzzle, expected);
}

TEST(move_north, test_challenge_4)
{
    Puzzle puzzle;
    Puzzle expected;

    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_4, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_4_n, expected));
    move_north(puzzle);
    EXPECT_EQ(puzzle, expected);
}

TEST(move_north, test_challenge_5)
{
    Puzzle puzzle;
    Puzzle expected;

    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_5, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_5_n, expected));
    move_north(puzzle);
    EXPECT_EQ(puzzle, expected);
}

/***********************************************************
    Move east tests
***********************************************************/

TEST(move_east, test_challenge_1)
{
    Puzzle puzzle;
    Puzzle expected;

    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_1, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_1_e, expected));
    move_east(puzzle);
    EXPECT_EQ(puzzle, expected);
    move_east(puzzle);
    EXPECT_EQ(puzzle, expected);
}

TEST(move_east, test_challenge_2)
{
    Puzzle puzzle;
    Puzzle expected;

    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_2, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_2_e, expected));
    move_east(puzzle);
    EXPECT_EQ(puzzle, expected);
    move_east(puzzle);
    EXPECT_EQ(puzzle, expected);
}

TEST(move_east, test_challenge_3)
{
    Puzzle puzzle;
    Puzzle expected;

    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_3, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_3_e, expected));
    move_east(puzzle);
    EXPECT_EQ(puzzle, expected);
}

TEST(move_east, test_challenge_4)
{
    Puzzle puzzle;
    Puzzle expected;

    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_4, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_4_e, expected));
    move_east(puzzle);
    EXPECT_EQ(puzzle, expected);
}

TEST(move_east, test_challenge_5)
{
    Puzzle puzzle;
    Puzzle expected;

    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_5, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_5_e, expected));
    move_east(puzzle);
    EXPECT_EQ(puzzle, expected);
}

/***********************************************************
    Move south tests
***********************************************************/
TEST(move_south, test_challenge_1)
{
    Puzzle puzzle;
    Puzzle expected;

    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_1, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_1_s, expected));
    move_south(puzzle);
    EXPECT_EQ(puzzle, expected);
    move_south(puzzle);
    EXPECT_EQ(puzzle, expected);
}

TEST(move_south, test_challenge_2)
{
    Puzzle puzzle;
    Puzzle expected;

    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_2, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_2_s, expected));
    move_south(puzzle);
    EXPECT_EQ(puzzle, expected);
    move_south(puzzle);
    EXPECT_EQ(puzzle, expected);
}

TEST(move_south, test_challenge_3)
{
    Puzzle puzzle;
    Puzzle expected;

    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_3, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_3_s, expected));
    move_south(puzzle);
    EXPECT_EQ(puzzle, expected);
}

TEST(move_south, test_challenge_4)
{
    Puzzle puzzle;
    Puzzle expected;

    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_4, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_4_s, expected));
    move_south(puzzle);
    EXPECT_EQ(puzzle, expected);
}

TEST(move_south, test_challenge_5)
{
    Puzzle puzzle;
    Puzzle expected;

    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_5, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_5_s, expected));
    move_south(puzzle);
    EXPECT_EQ(puzzle, expected);
}


/***********************************************************
    Move west tests
***********************************************************/
TEST(move_west, test_challenge_1)
{
    Puzzle puzzle;
    Puzzle expected;

    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_1, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_1_w, expected));
    move_west(puzzle);
    EXPECT_EQ(puzzle, expected);
    move_west(puzzle);
    EXPECT_EQ(puzzle, expected);
}

TEST(move_west, test_challenge_2)
{
    Puzzle puzzle;
    Puzzle expected;

    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_2, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_2_w, expected));
    move_west(puzzle);
    EXPECT_EQ(puzzle, expected);
    move_west(puzzle);
    EXPECT_EQ(puzzle, expected);
}

TEST(move_west, test_challenge_3)
{
    Puzzle puzzle;
    Puzzle expected;

    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_3, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_3_w, expected));
    move_west(puzzle);
    EXPECT_EQ(puzzle, expected);
}

TEST(move_west, test_challenge_4)
{
    Puzzle puzzle;
    Puzzle expected;

    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_4, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_4_w, expected));
    move_west(puzzle);
    EXPECT_EQ(puzzle, expected);
}

TEST(move_west, test_challenge_5)
{
    Puzzle puzzle;
    Puzzle expected;

    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_5, puzzle));
    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_5_w, expected));
    move_west(puzzle);
    EXPECT_EQ(puzzle, expected);
}

/***********************************************************
    Is solvable tests
***********************************************************/
TEST(is_solvable, north)
{
    Puzzle puzzle;

    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_1, puzzle));
    EXPECT_TRUE(is_solvable(puzzle));
    move_west(puzzle); 
    EXPECT_TRUE(is_solvable(puzzle));
    move_north(puzzle); 
    EXPECT_FALSE(is_solvable(puzzle));
}

TEST(is_solvable, east)
{
    Puzzle puzzle;

    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_1, puzzle));
    EXPECT_TRUE(is_solvable(puzzle));
    move_north(puzzle); 
    EXPECT_TRUE(is_solvable(puzzle));
    move_east(puzzle); 
    EXPECT_FALSE(is_solvable(puzzle));
}

TEST(is_solvable, south)
{
    Puzzle puzzle;

    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_1, puzzle));
    EXPECT_TRUE(is_solvable(puzzle));
    move_east(puzzle); 
    EXPECT_TRUE(is_solvable(puzzle));
    move_south(puzzle); 
    EXPECT_FALSE(is_solvable(puzzle));
}

TEST(is_solvable, west)
{
    Puzzle puzzle;

    EXPECT_TRUE(load_puzzle(TEST_CHALLENGE_1, puzzle));
    EXPECT_TRUE(is_solvable(puzzle));
    move_south(puzzle);
    EXPECT_TRUE(is_solvable(puzzle));
    move_west(puzzle); 
    EXPECT_FALSE(is_solvable(puzzle));
}
