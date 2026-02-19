#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <sstream>

using namespace std;

const int MAX_NO_OF_TERMS = 100;         // the maximum number of terms to read for a word sequence
const int MAX_NO_OF_WORDS = 25000;       // the maximum number of words to read from a text file

bool read_word (ifstream& infile, string& word)
{   
    
    // precondition:
    assert (infile.is_open());


    /*  postcondition:
    result is true only if a word is read from `infile`, and this word is assigned to `word`.
    result is false otherwise, and the value of `word` should not be used.
    */
    infile >> word;
    return !infile.fail();
}

int enter_command (string filename, string content [MAX_NO_OF_WORDS])
{
    
    // precondition:
    assert (true);


    /*  postcondition:

    if result is a positive number then the text file with file name `filename` has been successfully opened and closed after reading, and result number of words
    have been read from that file (at most MAX_NO_OF_WORDS) and are stored in that order in `content`.
    if result is zero, then either the text file was empty or has not been opened.
    */

    ifstream inFile(filename);

    // checks if in file
    if (inFile.fail()) {
        cout << "File not found" << endl;
        return 0;
    }


    // reads all the words into an array while the number is lower than max and as long as there are words into fike
    string word;
    int word_count = 0;
    while (word_count < MAX_NO_OF_WORDS && read_word(inFile, word)) {
        content[word_count++] = word;
    }
    inFile.close();

    // Return the number of words taken from the file
    if (word_count == 0) {
        cout << "This file is empty." << endl;
        return 0;
    } else {
        cout << "Successfully read " << word_count << "words" << endl;
        return word_count;
    }
}

void content_command(string content[MAX_NO_OF_WORDS], int no_of_words) {
    //Precondition:
    assert(no_of_words >= 0);
    //Postcondition:
    //Prints "No words have been loaded." if there are no words to write out and otherwise writes out all the words in the array.

    if (no_of_words == 0) {
        cout << "No words have been loaded." << endl;
        return;
    }
    for (int i = 0; i < no_of_words; ++i) {
        cout << content[i] << endl;
    }
}

// this was supposte become a helper function :/ 
int count_instance(const string content[MAX_NO_OF_WORDS], const string terms[MAX_NO_OF_TERMS], int no_of_words, int no_of_terms){
    
    assert(no_of_terms >= 0 && no_of_terms <= MAX_NO_OF_TERMS);
    assert(no_of_words >= 0 && no_of_words <= MAX_NO_OF_WORDS);

    //Postcondition:
    // return the count of instances
    
    int count = 0;
    //loops through the content array, checking to find a match
    for (int i = 0; i <= no_of_words - no_of_terms; ++i) {
        bool match = true;
        for (int j = 0; j < no_of_terms && match; ++j) {
            if (content[i + j] != terms[j]) {
                match = false;
               
            }
        }
        if (match) {
            ++count;
        }
    }
    return count;

}


int count_command (string content [MAX_NO_OF_WORDS], int no_of_words, string terms [MAX_NO_OF_TERMS], int no_of_terms)
{// precondition:
    assert(no_of_terms >= 0 && no_of_terms <= MAX_NO_OF_TERMS);
    assert(no_of_words >= 0 && no_of_words <= MAX_NO_OF_WORDS);
    /*  postcondition:
    result is the number of occurrences of the word sequence `terms` (which has `no_of_terms` elements) in `content` (which has `no_of_words` elements)
    (the result is obviously zero in case `no_of_words` < `no_of_terms`)
    */
    

    if (no_of_words < no_of_terms) {
        return 0;
    }

    
    int count = count_instance(content, terms, no_of_words, no_of_terms);
 
    

    cout << "Found sequence " << count << " times in " << no_of_words << " words (" 
         << (static_cast<double>(count) / no_of_words * 100) << "%)" << endl;
    return count;
    return 0;
}

void where_command(string content[MAX_NO_OF_WORDS], int no_of_words, string terms[MAX_NO_OF_TERMS], int no_of_terms) {
    
    //Precondition:
    assert(no_of_terms >= 0 && no_of_terms <= MAX_NO_OF_TERMS);
    assert(no_of_words >= 0 && no_of_words <= MAX_NO_OF_WORDS);
    
    //Postcondition:
    // Prints out all the locations where it found the occurrence and prints out "No occurrences found." if it did not find one

    if (no_of_words < no_of_terms) {
        cout << "No occurrences found." << endl;
        return;
    }

    int count = 0;
    for (int i = 0; i <= no_of_words - no_of_terms; ++i) {
        bool match = true;
        for (int j = 0; j < no_of_terms && match; ++j) {
            if (content[i + j] != terms[j]) {
                match = false;
                
            }
        }
        if (match) {
            cout << "Found occurrence at index " << i + 1 << endl;
            ++count;
        }
    }
}

void context_command(string content[MAX_NO_OF_WORDS], int no_of_words, string terms[MAX_NO_OF_TERMS], int no_of_terms, int m) {
    
    //Precondition
    assert(no_of_terms >= 0 && no_of_terms <= MAX_NO_OF_TERMS);
    assert(no_of_words >= 0 && no_of_words <= MAX_NO_OF_WORDS);

    //Postcondition:
    // prints out the given word sequence and m words befor and after the sequence
    if (no_of_words < no_of_terms) {
        cout << "No occurrences found." << endl;
        return;
    }

    int count = 0;
    for (int i = 0; i <= no_of_words - no_of_terms; ++i) {
        bool match = true;
        for (int j = 0; j < no_of_terms && match; ++j) {
            if (content[i + j] != terms[j]) {
                match = false;
                
            }
        }
        if (match) {
            int start = max(0, i - m);
            int end = min(no_of_words, i + no_of_terms + m);
            for (int k = start; k < end; ++k) {
                cout << content[k] << " ";
            }
            cout << endl;
            ++count;
        }
    }

}


int input_function(const string& user_input, string content[MAX_NO_OF_WORDS], int& no_of_words) {
    
    //Precondition:
    assert(true);

    //Postconditon
    // after handeling the requested command, returns 1 and returns zero if requeested command is "stop" or command does not exist
    
    istringstream line(user_input);
    string command;

    line >> command;

    //Depending on the desired command does the actions that given comand needs
    if (command == "enter") {
        string filename;
        getline(line >> ws, filename);
        no_of_words = enter_command(filename, content);
        return 1;
    } 
    else if (command == "content") {
        content_command(content, no_of_words);
        return 1;
    } 
    else if (command == "count") {
        string terms[MAX_NO_OF_TERMS];
        int no_of_terms = 0;

        while (line >> terms[no_of_terms] && no_of_terms < MAX_NO_OF_TERMS) {
            ++no_of_terms;
        }

        count_command(content, no_of_words, terms, no_of_terms);
        return 1;
    }
    else if (command == "where"){
        string terms[MAX_NO_OF_TERMS];
        int no_of_terms = 0;

        while (line >> terms[no_of_terms] && no_of_terms < MAX_NO_OF_TERMS) {
            ++no_of_terms;
        }
        where_command(content, no_of_words, terms, no_of_terms);
        return 1;
    } 
    else if( command == "context"){
        int m;
        line >> m;

        string terms[MAX_NO_OF_TERMS];
        int no_of_terms = 0;

        while (line >> terms[no_of_terms] && no_of_terms < MAX_NO_OF_TERMS) {
            ++no_of_terms;
        }

        context_command(content, no_of_words, terms, no_of_terms, m);
        return 1;
    }
    else if (command == "stop") {
        return 0;
    } 
    else {
        cout << "Invalid command" << endl;
        return 0;
    }
}


#ifndef TESTING
int main ()
{// precondition:
    assert(true);
    /*  postcondition:
    program has presented interactive interface to user, allowing commands to be entered and executed
    */
    string content[MAX_NO_OF_WORDS]; // store words read in this array
    // Implement your interactive console application.
    // The user should be able to enter the commands "enter", "content", "count", "where", "context", and "stop".
    int no_of_words;
    int value = 1;
    while(value == 1){
        cout << "enter command" << endl;
        string user_input;
        getline(cin, user_input);
        
        if(input_function(user_input, content, no_of_words) == 0 ){
            value = 0;
        }
    } 

    cout << "program stoped" << endl;
    
    return 0;
}
#endif
