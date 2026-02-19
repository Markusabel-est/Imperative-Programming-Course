#include <iostream>
#include <fstream>          // for file I/O

using namespace std;

enum Action {Encrypt, Decrypt} ;

int seed = 0;

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

    
    input_file_name = "secret.txt";

    output_file_name = "source.txt";

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

    return true;
}

/* The result of this function is the Action that the user has indicated that
the program should encrypt / decrypt */
Action get_user_action ()
{
    return Decrypt;
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

string common_words [8] = { "and", "the", "for", "that", "are", "but", "not", "you"};

int check_condition(ifstream& infile, ofstream& outfile, Action action) {
    for (int INITIAL_VALUE = 0; INITIAL_VALUE <= 65535; ++INITIAL_VALUE) {
        if (infile.is_open()) 
            infile.close();
        if (outfile.is_open()) 
            outfile.close();

        if (!open_input_and_output_file (infile,outfile))
        {
            cout << "Program aborted." << endl;
            return -1;
        }

        if (infile.fail() || outfile.fail())
        {
            cout << "Error reopening files." << endl;
            return -1;
        }

        initialise_pseudo_random(INITIAL_VALUE);

        char a, b;
        string decrypted_text;
        int cword = 0;
        infile.get(a);
        while (!infile.fail()) {
            int r = next_pseudo_random_number();
            b = rotate_char(a, r, action);
            decrypted_text += b;
            infile.get(a);
        }

        for (int i = 0; i < 8; ++i) {
            if (decrypted_text.find(common_words[i]) != string::npos) {
                cword++;
            }
        }

        if (cword >= 3) {
            cout << "Possible match found at initial R: " << INITIAL_VALUE << endl;
            outfile << decrypted_text;
            return INITIAL_VALUE;
        }
    }

    cout << "No valid decryption found." << endl;
    return -1;
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
    int INITIAL_VALUE = check_condition(input_file, output_file, ACTION);

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

