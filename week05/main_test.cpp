#include "main.cpp"
#include "gtest/gtest.h"

using namespace std;


TEST (part1, encrypt)
{
  EXPECT_EQ (rotate_char (' ', 0, Encrypt), ' ');
  EXPECT_EQ (rotate_char ('~', 45774747, Encrypt), '9');
  /** Add at least 3 more tests for Encrypt */
  EXPECT_EQ(rotate_char('A', 1, Encrypt), 'B');    
  EXPECT_EQ(rotate_char('M', 15, Encrypt), '\\');   
  EXPECT_EQ(rotate_char('g', 20, Encrypt), '{');
}


TEST (part1, decrypt)
{
  EXPECT_EQ (rotate_char (' ', 0, Decrypt), ' ');
  EXPECT_EQ (rotate_char ('\x7f', 65535, Decrypt), '@');
  /** Add at least 3 more tests for Decrypt */
  EXPECT_EQ(rotate_char('B', 1, Decrypt), 'A');    
  EXPECT_EQ(rotate_char('\\', 15, Decrypt), 'M');  
  EXPECT_EQ(rotate_char('{', 20, Decrypt), 'g');   
}

TEST (part1, inverse)
{
  /** Add a property based test to determine that Encrypt and Decrypt are
  inverses. That is, test that we have:

  rotate_char (rotate_char (c, r, Encrypt), r, Decrypt) == c

  */
 for (char c = 32; c < 128; ++c) {
    int r = 500;
    EXPECT_EQ(rotate_char(rotate_char(c, r, Encrypt), r, Decrypt), c);
 }
}

bool streams_match (ifstream& ins, ifstream& refs) {
  char c, refc;

  // Loop over every character in the reference stream.
  while (refs.get (refc)) {
    // The input stream must also be able to read a character.
    // It must also match the reference character read from the reference stream.
    if (!ins.get (c) || c != refc)
      return false;
  }

  // We know the input stream begins with the reference stream, but may contain additional characters.
  return true;
}

int get_stream_length (ifstream& is)
{
  char c;
  int length = 0;

  // Determine stream length by reading character by character.
  // This makes sure we read CRLF as a single LF character on Windows.
  while (is.get (c))
      length++;

  // We then move back again to the start of the stream for further reading.
  // Note that we must clear the failbit for seekg to work, which was just set by us reading the entire file.
  is.clear ();
  is.seekg (0, ios_base::beg);

  return length;
}

TEST (part3, use_OTP_1)
{
  const int R = 1;
  const string INPUT_FILENAME = "test.txt";
  const string OUTPUT_FILENAME = "output" + to_string (R) + ".txt";
  const string TEST_FILENAME = "test_encrypted_with_" + to_string (R) + ".txt";

  ifstream input_file (INPUT_FILENAME);
  ofstream output_file (OUTPUT_FILENAME);
  use_OTP(input_file, output_file, Encrypt, R);
  output_file.close ();

  ifstream expected_file (TEST_FILENAME);
  ifstream actual_file (OUTPUT_FILENAME);
  int expected_length = get_stream_length (expected_file);
  int actual_length = get_stream_length (actual_file);

  EXPECT_TRUE (streams_match (actual_file, expected_file));
  EXPECT_EQ (actual_length, expected_length);
}

TEST (part3, use_OTP_42)
{
  const int R = 42;
  const string INPUT_FILENAME = "test.txt";
  const string OUTPUT_FILENAME = "output" + to_string (R) + ".txt";
  const string TEST_FILENAME = "test_encrypted_with_" + to_string (R) + ".txt";

  ifstream input_file (INPUT_FILENAME);
  ofstream output_file (OUTPUT_FILENAME);
  use_OTP (input_file, output_file, Encrypt, R);
  output_file.close ();

  ifstream expected_file (TEST_FILENAME);
  ifstream actual_file (OUTPUT_FILENAME);
  int expected_length = get_stream_length (expected_file);
  int actual_length = get_stream_length (actual_file);

  EXPECT_TRUE (streams_match(actual_file, expected_file));
  EXPECT_EQ (actual_length, expected_length);
}

TEST (part3, use_OTP_96)
{
  const int R = 96;
  const string INPUT_FILENAME = "test.txt";
  const string OUTPUT_FILENAME = "output" + to_string (R) + ".txt";
  const string TEST_FILENAME = "test_encrypted_with_" + to_string (R) + ".txt";

  ifstream input_file (INPUT_FILENAME);
  ofstream output_file (OUTPUT_FILENAME);
  use_OTP (input_file, output_file, Encrypt, R);
  output_file.close ();

  ifstream expected_file (TEST_FILENAME);
  ifstream actual_file (OUTPUT_FILENAME);
  int expected_length = get_stream_length (expected_file);
  int actual_length = get_stream_length (actual_file);

  EXPECT_TRUE (streams_match (actual_file, expected_file));
  EXPECT_EQ (actual_length, expected_length);
}

TEST (part3, use_OTP_65535)
{
  const int R = 65535;
  const string INPUT_FILENAME = "test.txt";
  const string OUTPUT_FILENAME = "output" + to_string (R) + ".txt";
  const string TEST_FILENAME = "test_encrypted_with_" + to_string (R) + ".txt";

  ifstream input_file (INPUT_FILENAME);
  ofstream output_file (OUTPUT_FILENAME);
  use_OTP (input_file, output_file, Encrypt, R);
  output_file.close ();

  ifstream expected_file (TEST_FILENAME);
  ifstream actual_file (OUTPUT_FILENAME);
  int expected_length = get_stream_length (expected_file);
  int actual_length = get_stream_length (actual_file);

  EXPECT_TRUE (streams_match (actual_file, expected_file));
  EXPECT_EQ (actual_length, expected_length);
}
