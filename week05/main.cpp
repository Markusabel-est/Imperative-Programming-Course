#include <iostream>
#include <fstream>          // for file I/O

using namespace std;

enum Action {Encrypt, Decrypt} ;

int seed = 0 ;

/** Given an integer r between 0 (not including) and 65536 (including) sets the
seed to the value of r */
void initialise_pseudo_random (int r)
{
    seed = r ;
}

/** Return the next pseudo random number. This function will use and update the
global variable seed. */
int next_pseudo_random_number ()
{
    const int SEED75 = seed * 75 ;
    int next = (SEED75 & 65535) - (SEED75 >> 16) ;
    if (next < 0)
        next += 65537 ;
    seed = next ;
    return next ;
}

char rotate_char (char a, int r, Action action)
{
    int b;
    if(action == Encrypt){
        if(a < 32){
            b = a;
        }else{
            b = (a - 32 + (r % (128 - 32)) ) % (128 - 32) + 32;
        }
    }else{
        if(a < 32){
            b = a;
        }else{
            b = (a - 32 - (r % (128 - 32)) + (128 - 32)) % (128 - 32) + 32;
        }
    }
    return b;
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
    string input_file_name, output_file_name;

    cout << "Input File name: ";
    cin >> input_file_name;

    cout << "Output File name: ";
    cin >> output_file_name;

    if(input_file_name == output_file_name){
        cout << "Invalid File Names. Names should not be the same.";
        return false;
    }

    infile.open(input_file_name);
    if(infile.fail()){
        cout << "Invalid Input File Name";
        return false;
    }

    outfile.open(output_file_name);
    if(outfile.fail()){
        cout << "Invalid Output File Name";
        return false;
    }

    cout << "Files have been opened" << endl;
    return true;
}

/* The result of this function is the Action that the user has indicated that
the program should encrypt / decrypt */
Action get_user_action ()
{
    cout << "Do you want to encrypt the file? (y/n): " ;
    string answer ;
    cin  >> answer ;
    if (answer == "y")
        return Encrypt;
    else
        return Decrypt;
}

/** The result of this function is result is a value between 0 and 65355 (both
inclusive). */
int initial_encryption_value ()
{
    int initial_value = -1 ;
    while (initial_value < 0 || initial_value > 65535)
    {
        cout << "Please enter the initial coding value (greater or equal to 0 and less than 65536)" << endl ;
        cin  >> initial_value ;
    }
    return initial_value ;
}

void use_OTP (ifstream& infile, ofstream& outfile, Action action, int initial_value)
{
    char a, b;
    
    initialise_pseudo_random(initial_value); 
    infile.get(a);
    while (!infile.fail()){
        int r = next_pseudo_random_number();  
        b = rotate_char(a, r, action);       
        outfile.put(b);                      
        infile.get(a);                        
    }
}

#ifndef TESTING
int main ()
{
    const Action ACTION = get_user_action();
    ifstream input_file;
    ofstream output_file;
    if (!open_input_and_output_file (input_file,output_file))
    {
        cout << "Program aborted." << endl;
        return -1;
    }
    const int INITIAL_VALUE = initial_encryption_value ();
    use_OTP (input_file,output_file,ACTION,INITIAL_VALUE);
    input_file.clear ();
    output_file.clear ();
    input_file.close ();
    output_file.close ();

    if (!input_file || !output_file)
    {
        cout << "Not all files were closed successfully. The output might be incorrect." << endl;
        return -1;
    }
    return 0;
}
#endif
