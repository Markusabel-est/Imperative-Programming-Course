#include <iostream>
#include <cassert>
#include <string>
#include <cctype>
using namespace std;

/**********************************************************************************************************
 *
 * Part 1: Run-time complexity of recursive algorithms
 *
*********************************************************************************************************/

/*
    [Part 1: (a)]
    Complexity: O(i)
    Explanation: The inputs are vector data, the integer i, and the double x. The complexity is i because the base case is 
    when either i is zero or x is equal to -1. The worst is when i is decreased iteratively to zero for the entirety of i without 
    getting stopped by x.

    [Part 1: (b)]
    Complexity: O(2^(i-j))
    Explanation: The inputs are the integers j and i, and the worst case is when the function runs until j is less than i which only 
    occurs at the difference of j and i and with each recursive call, the function calls itself two more times creating a binary tree-like 
    structure. The complexity should be an exponetial with a base of 2 and an exponent of j-i.

    [Part 1: (c)]
    Complexity: O(size of data)
    Explanation: the function's inputs are the vector data and the integer n. The worst case is when the function iterates through the entirety
    of data without interruptions. It does this linearly, meaning that the complexity is just the size of the vector.
 */

/**********************************************************************************************************
 *
 * Part 2: The power function
 *
*********************************************************************************************************/

int naive_power (int x, int n)
{
    assert(n >= 0);

    if(n == 0){
        return 1;
    }
    else{
        return x * naive_power(x, n -1);
    }
}

int power (int x, int n)
{
    assert(n >= 0);

    if(n==0){
        return 1;
    }
    if(n % 2 == 0){
        return power(x, n/2) * power(x, n/2);
    }
    else{
        return x * power(x, (n-1)/2) * power(x, (n-1)/2);
    }
}

/**********************************************************************************************************
 *
 * Part 2.3: Power, run-time complexity
 *
*********************************************************************************************************/

/*
    Complexity: O(n)
    Explanation: in the worst case, the function naive_power iterates through the power of x which is n in this case
*/

/*
    Complexity: O(log n)
    Explanation: in the worst case, the function power iterates through the power of x which is log n, becasue every iteration divides n by 2.
*/

/**********************************************************************************************************
 *
 * Part 3: Palindromes
 *
*********************************************************************************************************/

bool palindrome1 (string text, int i, int j)
{
    assert(i >= 0 && j >=0);

    if(i >= j){
        return true;
    }
    if(text.at(i)!= text.at(j)){
        return false;
    }
    else{
        return palindrome1(text, i+1, j-1);
    }
    
}
bool palindrome2(const std::string& text, int i, int j) {
    assert(i >= 0 && j >= 0);
   
    if (i >= j) {
        return true; 
    }

    char charLeft = text.at(i);
    char charRight = text.at(j);
    if(charLeft >= 'A' && charLeft <= 'Z'){
        charLeft = charLeft - ('A' - 'a');
    }

    if(charRight >= 'A' && charRight <= 'Z'){
        charRight = charRight - ('A' - 'a');
    }

    if(charLeft != charRight){
        return false;
    }
    else {
       return palindrome2(text, i + 1, j - 1); 
    }
}

bool palindrome3 (string text, int i, int j)
{
    assert(i >= 0 && j >= 0);
   
    if (i >= j) {
        return true; 
    }

    char charLeft = text.at(i);
    char charRight = text.at(j);


    if(charLeft >= 'A' && charLeft <= 'Z'){
        charLeft = charLeft - ('A' - 'a');
    }

    if(charRight >= 'A' && charRight <= 'Z'){
        charRight = charRight - ('A' - 'a');
    }
    if(charRight < 'a' || charRight > 'z'){
        return palindrome3(text, i, j - 1); 
    }
     if(charLeft < 'a' || charLeft > 'z'){
        return palindrome3(text, i+1, j); 
    }
    if(charLeft != charRight){
        return false;
    }
    else {
       return palindrome3(text, i + 1, j - 1); 
    }
}

/**********************************************************************************************************
 *
 * Part 4: Matching characters in a string
 *
*********************************************************************************************************/

bool match_chars (string chars, int i, string source, int j)
{
    assert(i >= 0 && j >= 0);
    
    if(i >= ssize(chars)){
        return true;
    }

    if(j >= ssize(source)){
        return false;
    }

    if(chars.at(i) == source.at(j)){
        return match_chars(chars, i + 1, source, j + 1);
    }
    return match_chars(chars, i, source, j + 1);
}

string to_bool (bool value)
{
    // Pre-condition:
    assert(true);
    // Post-condition: return value is "Yes" if `value` is true, "No" otherwise
    if (value) {
        return "Yes";
    } else {
        return "No";
    }
}

#ifndef TESTING
int main ()
{
    // Pre-condition:
    assert(true);
    // Post-condition: user has entered a line of text, and program has printed
    // return value of all palindrome functions on that line of text

    string input;

    cout << "Enter a line of text: ";
    getline(cin, input);

    cout << "Palindrome1? " << to_bool(palindrome1(input, 0, ssize(input)-1)) << endl;
    cout << "Palindrome2? " << to_bool(palindrome2(input, 0, ssize(input)-1)) << endl;
    cout << "Palindrome3? " << to_bool(palindrome3(input, 0, ssize(input)-1)) << endl;

    return 0;
}
#endif
