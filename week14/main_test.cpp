#include "main.cpp"
#include "gtest/gtest.h"

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
const vector<vector<char>> UNSOLVABLE_CHALLENGE = {
    {'.', '.', 'x'},
    {'.', 'f', '.'},
    {'.', '.', '.'}
};
const vector<vector<char>> CHALLENGE_0 = {
    {'.','.','.','.','.','.'},
    {'.','.','.','.','.','.'},
    {'.','.','.','.','.','.'},
    {'.','.','.','.','.','.'},
    {'.','.','.','.','.','F'}
};
const vector<vector<char>> CHALLENGE_1 = {
    {'.','.','.','.','r','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','r','.'},
    {'.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','f','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','x','.','.'}
};
const vector<vector<char>> CHALLENGE_2 = {
    {'.','.','.','.','.','r','.'},
    {'r','.','.','.','.','.','.'},
    {'r','.','f','.','.','.','r'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'.','.','.','.','r','.','.'},
    {'.','r','.','x','.','.','.'}
};
const vector<vector<char>> CHALLENGE_3 = {
    {'r','r','r','r','r','r','r'},
    {'.','.','.','.','.','.','r'},
    {'.','r','r','r','.','.','.'},
    {'.','.','.','x','.','.','.'},
    {'.','.','.','.','.','.','.'},
    {'.','r','.','.','.','.','.'},
    {'f','.','.','.','.','r','.'}
};
const vector<vector<char>> CHALLENGE_4 = {
    {'.','.','.','.','.','.','.','.','.','.','.','r','.','.'},
    {'r','.','.','.','.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.','r','.','.','.'},
    {'.','.','r','.','.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','x','.','r','.','.','.','.','.'},
    {'.','.','.','.','.','r','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','f','.','.','.','.','r','.'},
    {'.','.','.','.','.','.','.','.','.','r','.','.','.','.'},
    {'.','.','.','r','.','.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.','.','.','r','.','r'},
    {'.','r','.','.','.','.','.','.','.','.','.','.','.','.'}
};

TEST(bfs, bad_format_1)
{
    const int EXPECTED_STEPS = BAD_FORMAT;

    vector<Puzzle> solution_path;
    int actual = breadth_first(BAD_FORMAT_1, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
}

TEST(bfs, bad_format_2)
{
    const int EXPECTED_STEPS = BAD_FORMAT;

    vector<Puzzle> solution_path;
    int actual = breadth_first(BAD_FORMAT_2, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
}

TEST(bfs, bad_format_3)
{
    const int EXPECTED_STEPS = BAD_FORMAT;

    vector<Puzzle> solution_path;
    int actual = breadth_first(BAD_FORMAT_3, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
}

TEST(bfs, bad_format_4)
{
    const int EXPECTED_STEPS = BAD_FORMAT;

    vector<Puzzle> solution_path;
    int actual = breadth_first(BAD_FORMAT_4, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
}

TEST(bfs, bad_format_5)
{
    const int EXPECTED_STEPS = BAD_FORMAT;

    vector<Puzzle> solution_path;
    int actual = breadth_first(BAD_FORMAT_5, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
}

TEST(bfs, bad_format_6)
{
    const int EXPECTED_STEPS = BAD_FORMAT;

    vector<Puzzle> solution_path;
    int actual = breadth_first(BAD_FORMAT_6, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
}

TEST(bfs, no_solution)
{
    const int EXPECTED_STEPS = NO_SOLUTION;

    vector<Puzzle> solution_path;
    int actual = breadth_first(UNSOLVABLE_CHALLENGE, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
}

TEST(bfs, challenge0)
{
    const int EXPECTED_STEPS = 0;
    vector<Puzzle> solution_path;
    int actual = breadth_first(CHALLENGE_0, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(bfs, challenge1)
{
    const int EXPECTED_STEPS = 3;
    vector<Puzzle> solution_path;
    int actual = breadth_first(CHALLENGE_1, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(bfs, challenge2)
{
    const int EXPECTED_STEPS = 4;
    vector<Puzzle> solution_path;
    int actual = breadth_first(CHALLENGE_2, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(bfs, challenge3)
{
    const int EXPECTED_STEPS = 6;
    vector<Puzzle> solution_path;
    int actual = breadth_first(CHALLENGE_3, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(bfs, challenge4)
{
    const int EXPECTED_STEPS = 12;
    vector<Puzzle> solution_path;
    int actual = breadth_first(CHALLENGE_4, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(dfs, bad_format_1)
{
    const int EXPECTED_STEPS = BAD_FORMAT;

    vector<Puzzle> solution_path;
    int actual = depth_first(BAD_FORMAT_1, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
}

TEST(dfs, bad_format_2)
{
    const int EXPECTED_STEPS = BAD_FORMAT;

    vector<Puzzle> solution_path;
    int actual = depth_first(BAD_FORMAT_2, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
}

TEST(dfs, bad_format_3)
{
    const int EXPECTED_STEPS = BAD_FORMAT;

    vector<Puzzle> solution_path;
    int actual = depth_first(BAD_FORMAT_3, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
}

TEST(dfs, bad_format_4)
{
    const int EXPECTED_STEPS = BAD_FORMAT;

    vector<Puzzle> solution_path;
    int actual = depth_first(BAD_FORMAT_4, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
}

TEST(dfs, bad_format_5)
{
    const int EXPECTED_STEPS = BAD_FORMAT;

    vector<Puzzle> solution_path;
    int actual = depth_first(BAD_FORMAT_5, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
}

TEST(dfs, bad_format_6)
{
    const int EXPECTED_STEPS = BAD_FORMAT;

    vector<Puzzle> solution_path;
    int actual = depth_first(BAD_FORMAT_6, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
}

TEST(dfs, no_solution)
{
    const int EXPECTED_STEPS = NO_SOLUTION;

    vector<Puzzle> solution_path;
    int actual = depth_first(UNSOLVABLE_CHALLENGE, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
}

TEST(dfs, challenge0)
{
    const int EXPECTED_STEPS = 0;
    vector<Puzzle> solution_path;
    int actual = depth_first(CHALLENGE_0, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(dfs, challenge1)
{
    const int EXPECTED_STEPS = 3;
    vector<Puzzle> solution_path;
    int actual = depth_first(CHALLENGE_1, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(dfs, challenge2)
{
    const int EXPECTED_STEPS = 4;
    vector<Puzzle> solution_path;
    int actual = depth_first(CHALLENGE_2, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(dfs, challenge3)
{
    const int EXPECTED_STEPS = 6;
    vector<Puzzle> solution_path;
    int actual = depth_first(CHALLENGE_3, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(dfs, challenge4)
{
    const int EXPECTED_STEPS = 12;
    vector<Puzzle> solution_path;
    int actual = depth_first(CHALLENGE_4, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(ssize(solution_path), EXPECTED_STEPS+1);
}

TEST(dfs, depth_limit)
{
    vector<Puzzle> solution_path;

    EXPECT_EQ(depth_first(CHALLENGE_3, solution_path, 0), NO_SOLUTION);
    EXPECT_EQ(depth_first(CHALLENGE_3, solution_path, 1), NO_SOLUTION);
    EXPECT_EQ(depth_first(CHALLENGE_3, solution_path, 2), NO_SOLUTION);
    EXPECT_EQ(depth_first(CHALLENGE_3, solution_path, 3), NO_SOLUTION);
    EXPECT_EQ(depth_first(CHALLENGE_3, solution_path, 4), NO_SOLUTION);
    EXPECT_EQ(depth_first(CHALLENGE_3, solution_path, 5), NO_SOLUTION);
    EXPECT_EQ(depth_first(CHALLENGE_3, solution_path, 6), 6);
    EXPECT_EQ(depth_first(CHALLENGE_3, solution_path, 7), 6);
    EXPECT_EQ(depth_first(CHALLENGE_3, solution_path, 8), 6);
}
