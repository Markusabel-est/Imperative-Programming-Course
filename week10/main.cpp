#define NDEBUG // we must define this _before_ we include cassert
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

/**********************************************************************************************************
 *
 * Part 1: Analyze the order of run-time complexity
 *
 *********************************************************************************************************/

/*
    [Part 1: (a)]
    Complexity: O(N^3)
    Explanation: There are 3 for loops inside each other, so each for loop runs N times and the whole set of for loops N*N*N times.

    [Part 1: (b)]
    Complexity: O(L*M*N)
    Explanation: It is basically the same as befor but this time the first loop  runs L, then M and then N times.

    [Part 1: (c)]
    Complexity: O(n)
    Explanation: the while loop iterates thorugh string at most once and the length of the string is n.

    [Part 1: (d)]
    Complexity: O(n^2)
    Explanation: strlen(text) takes two times n so n*n

    [Part 1: (e)]
    Complexity: O(sqrt(x))
    Explanation: the loop iterates through all potential divisors up to sqrt(x)

    [Part 1: (f)]
    Complexity: O(length) = O(n)
    Explanation: for loop iterates through the length

    [Part 1: (g)]
    Complexity: O(n)
    Explanation: the while loop iterates n times

    [Part 1: (h)]
    Complexity: O(2^n * N)
    Explanation: the while loop runs 2^n times and the for loop in there N times

    [Part 1: (i)]
    Complexity: O(1)
    Explanation: It only checks the first and last element
 */

/**********************************************************************************************************
 *
 * Part 4: Analyzing the measurements
 *
 *********************************************************************************************************/

/*
    Do the measured results of the sorting algorithms match with your expectations according to their order of run-time complexities?
    Discuss this here. In particular, include the following aspects in your analysis on each algorithm:
    - What is the worst/best/average case run-time complexity of the algorithm?
    - When do you expect each case to occur?
    - Does the order of the database significantly impact the measured number of operations?
    - If so, explain why this difference occurs.
    For your analysis you can refer to both the raw measurement data obtained in Part 2, and the charts produced in Part 3.
    You may generate additional graphs if this aids your analysis, but clearly state how they were obtained.

    <<WRITE YOUR DISCUSSION HERE>>
 */

/**********************************************************************************************************
 *
 * Part 2: Measuring the sorting algorithms
 *
 *********************************************************************************************************/
const int SLICE_STEP = 500; // The amount used when incrementing track sorting slices in each step
const int MAX_SLICE = 6500; // The maximum size of the tracks sorting slice (inclusive)
int Globalcounter = 0;
// Reuse your implementation from last week as a starting point.

struct Length
{
	int minutes;							// #minutes (0..)
	int seconds;							// #seconds (0..59)
};

struct Track
{
	string artist;                          // name of artist
	string cd;                              // cd title
	int    year;                            // year of appearance (if known)
	int    track;							// track number
	string title;                           // track title
	string tags;                            // tags
	Length time;							// playing time
	string country;                         // main countr(y/ies) of artist
};

/**********************************************************************************************************
 *
 * input and output code from prior week:
 *
 *********************************************************************************************************/
ostream& operator<< (ostream& out, const Length length)
{// Precondition:
    assert (true) ;
/*  Postcondition:
    the value of length is shown via out in the format: minutes, ':', seconds (two digits)
*/

    out << length.minutes << ":";
    if (length.seconds < 10){
        out << "0";
    } 
    out << length.seconds;
    return out;
}

istream& operator>> (istream& in, Length& length)
{// Precondition:
    assert (true) ;
/*  Postcondition:
    the value of length has been read from in: first minutes, then ':', then seconds
*/
    char colon;
    in >> length.minutes;
    in >> colon;
    in >> length.seconds;
    return in;
}

ostream& operator<< (ostream& out, const Track& track)
{// Precondition:
    assert (true) ;
/*  Postcondition:
    the value of track is shown via out.
*/
    return out << track.artist << " - " << track.track << ". " << track.title
        << " (" << track.cd << ", " << track.year << ") [" << track.time << "]";
}

istream& operator>> (istream& in, Track& track)
{// Precondition:
    assert (true) ;
/*  Postcondition:
    the content of the first 8 lines from in have been read and are stored in the corresponding members of track.
    The following (empty) line from in has also been read.
*/
    getline(in, track.artist);
    getline(in, track.cd);

    in >> track.year;
    in.ignore();

    in >> track.track;
    in.ignore();

    getline(in, track.title);
    getline(in, track.tags);

    in >> track.time;
    in.ignore();
    
    getline(in, track.country);
    in.ignore();
    return in;
}

/**********************************************************************************************************
 *
 * (slice) helper function:
 *
 *********************************************************************************************************/
typedef Track El;                           // as explained in lecture, define algorithms on El

struct Slice
{  int from;     // from >= 0
   int length;   // length >= 0
};

Slice make_slice (int from, int length)
{// Precondition:
    assert (from >= 0 && length >= 0);
/*  post-condition:
    return slice with given from and length
*/
    Slice s = { from, length};
    return s;
}

Slice make_slice (const vector<El>& data)
{// Precondition:
    assert (true);
/*  Postcondition:
    returns the slice for the entire vector data.
*/
    Slice s = { 0, static_cast<int>( ssize (data) ) };
    return s;
}

bool valid_slice (Slice s)
{// Precondition:
    assert (true);
/*  Postcondition:
    returns true only if all selector values of s are not negative.
*/
    return 0 <= s.from && 0 <= s.length;
}
bool valid_slice (const vector<El>& data, Slice s)
{// Precondition:
    assert (true);
/*  Postcondition:
    returns true only if s is a valid slice for data
*/
    return valid_slice (s) && s.from + s.length <= ssize (data);
}

int first (Slice s)
{// Precondition:
    assert (valid_slice (s));
/*  Postcondition:
    result is index of first element in s (s.from)
*/
    return s.from;
}

int last (Slice s)
{// Precondition:
    assert (valid_slice (s));
/*  Postcondition:
    result is one past the index of last element in s (s.from + s.length)
*/
    return s.from + s.length;
}

/**********************************************************************************************************
 *
 * compare operators:
 *
 *********************************************************************************************************/
bool operator== (const Track& a, const Track& b)
{// Precondition:
    assert (true);
/*  Postcondition:
    returns true only if all selector values of a are equal to their counterparts of b
*/
    Globalcounter++;
    return ( a.artist == b.artist && 
            a.cd == b.cd &&
            a.year == b.year &&
            a.track == b.track &&
            a.title == b.title &&
            a.tags == b.tags &&
            a.time.minutes == b.time.minutes &&
            a.time.seconds == b.time.seconds &&
            a.country == b.country);
}

bool operator!= (const Track& a, const Track& b)
{// Precondition:
    assert (true);
/*  Postcondition:
    returns true only if any selector values of a are not equal to their counterparts of b
*/
    return !(a == b);
}

bool operator< (const Track& a, const Track& b)
{// Precondition:
    assert (true);
/*  Postcondition:
    check the assignment for the proper definition of < on Tracks
*/
    Globalcounter++;
    if (a.artist != b.artist) {
        return a.artist < b.artist;
    }
    if (a.cd != b.cd) {
        return a.cd < b.cd;
    }
    if (a.year != b.year){
        return a.year < b.year;
    }
    if (a.track != b.track) {
        return a.track < b.track;
    }
    if (a.title != b.title) {
        return a.title < b.title;
    }
    if (a.tags != b.tags) {
        return a.tags < b.tags;
    }
    if (a.time.minutes != b.time.minutes) {
        return a.time.minutes < b.time.minutes;
    }
    if (a.time.seconds != b.time.seconds) {
        return a.time.seconds < b.time.seconds;
    }
    return a.country < b.country;

}

bool operator>(const Track& a, const Track& b)
{// Precondition:
    assert (true);
/*  Postcondition:
    returns true only if a does not precede b according to the ordering < on Tracks (don't forget to implement operator<)
*/
	return b < a;
}

bool operator<=(const Track& a, const Track& b)
{// Precondition:
    assert (true);
/*  Postcondition:
    returns true only if a < b or a == b according to their definitions on Tracks (don't forget to implement operator< and operator==)
*/
	return a < b || a == b;
}

bool operator>=(const Track& a, const Track& b)
{// Precondition:
    assert (true);
/*  Postcondition:
    returns true only if a > b or a == b according to their definitions on Tracks (don't forget to implement operator< and operator==)
*/
	return a > b || a == b;
}

bool is_sorted (const vector<El>& data, Slice s)
{// pre-condition:
    assert (valid_slice (data, s));
/*  post-condition:
    result is true if data.at (first(s)) <= data.at (first(s)+1) ... data.at (last(s)-2) <= data.at (last(s)-1)
*/
    for (int i = first(s); i < last(s) - 1; i++) {
        if (data.at(i) > data.at(i + 1)) {
            return false;
        }
    }

    return true; 
}

/**********************************************************************************************************
 *
 * insertion sort algorithm:
 *
 *********************************************************************************************************/
void insert (vector<El>& data, Slice s)
{// Precondition:
    assert (valid_slice (data,s));
    assert (is_sorted (data, s));
    assert (last (s) < ssize (data) - 1);
/*  Postcondition:
    data.at (last (s)+1) is moved in data.at (first (s))...data.at (last (s)+1) and is_sorted (data, make_slice (s.from s.length+1))
*/
    int i = last(s);

    while (i > 0 && data.at(i) < data.at(i - 1)) {
        swap(data.at(i), data.at(i - 1)); 
        i--;
    }
}

void insertion_sort(vector<El>& data)
{// Precondition:
    assert (true);
/*  Postcondition:
    data is sorted in increasing order, according to < and == on El (don't forget to implement operator< and operator==)
*/
    for (int i = 1; i < ssize(data); i++){
        insert(data, make_slice(0,i));
    }
}

/**********************************************************************************************************
 *
 * selection sort algorithm:
 *
 *********************************************************************************************************/
int max_value_at (const vector<El>& data, Slice s)
{// Precondition:
    assert (valid_slice (data, s));
    assert (s.length > 0);
/*  Postcondition:
    data.at (result) is the maximum of every element in data.at (first(s)) ... data.at (last(s))
*/
    int max_index = first(s);

    for(int i = first(s); i < last(s); i++){
        if(data.at(i) > data.at(max_index)){
            max_index = i;
        }
    }
    return max_index;
}

void selection_sort(vector<El>& data)
{// Precondition:
    assert (true);
/*  Postcondition:
    data is sorted in increasing order, according to < and == on El (don't forget to implement operator< and operator==)
*/
    int max;
    for (int i = ssize(data); i > 0; i--){


        max = max_value_at(data,make_slice(0,i));
        swap(data.at(max), data.at(i-1));
    }
}

/**********************************************************************************************************
 *
 * bubble sort algorithm:
 *
 *********************************************************************************************************/
bool bubble (vector<El>& data, Slice unsorted)
{// Precondition:
    assert (valid_slice (data, unsorted));
/*  Postcondition:
    immediate pairs in data with slice unsorted are swapped if left element is larger than right element, and result is
    true only if this is done at least once (do not forget to implement operator< and operator==)
*/
    bool swapped = false; 


    for (int i = first(unsorted); i < last(unsorted)-1; i++) {

        if (data.at(i) > data.at(i + 1)) {

            swap(data.at(i), data.at(i + 1));
            swapped = true; 
        }
    }

    return swapped;

}

void bubble_sort(vector<El>& data)
{// Precondition:
    assert (true);
/*  Postcondition:
    data is sorted in increasing order, according to < and == on El (don't forget to implement operator< and operator==)
*/
    bool buble = true;
    int unsorted = ssize(data) - 1;

    while(buble && (unsorted > 0))
    {
        buble = bubble(data,make_slice(0,unsorted));
        unsorted--;
    }
}

/**********************************************************************************************************
 *
 * heap sort algorithm:
 *
 *********************************************************************************************************/
int left_sibling (int i)
{// Precondition:
    assert (0 <= i);
/*  Postcondition:
    result is the index (if existing) of the left sibling of an element at index i in a heap structured array/vector
*/
    return i-1;
}

int right_sibling (int i)
{// Precondition:
    assert (0 <= i);
/*  Postcondition:
    result is the index (if existing) of the right sibling of an element at index i in a heap structured array/vector
*/
    return i+1;
}

int parent (int i)
{// Precondition:
    assert (0 <= i);
/*  Postcondition:
    result is the index (if existing) of the parent of an element at index i in a heap structured array/vector
*/
    return (i-1) / 2;
}

int left_child (int i)
{// Precondition:
    assert (0 <= i);
/*  Postcondition:
    result is the index (if existing) of the left child of an element at index i in a heap structured array/vector
*/
    return 2*(i+1)-1;
}

int right_child (int i)
{// Precondition:
    assert (0 <= i);
/*  Postcondition:
    result is the index (if existing) of the right child of an element at index i in a heap structured array/vector
*/
    return 2*(i+1);
}

bool is_a_heap (const vector<El>& data, Slice s)
{// Precondition:
    assert (valid_slice (data,s));
/*  Postcondition:
    result is true only if all existing children in slice s of data have a value that is not greater than their parent
*/
    for (int i = last(s) - 1; i > first(s); --i) {
        if (data.at(i) > data.at(parent(i))) {
            return false;
        }
    }
    return true;
}

void push_up ( vector<El>& data, int elem )
{// Precondition:
    assert (0 <= elem && elem < ssize (data) && is_a_heap (data, make_slice (0,elem)));
/*  Postcondition:
    is_a_heap (data, make_slice (0, elem+1))
*/
    while (elem > 0 && data.at(elem) > data.at(parent(elem))) {
        swap(data.at(elem), data.at(parent(elem)));
        elem = parent(elem);
    }
}

void build_heap ( vector<El>& data )
{// Precondition:
    assert (true );
/*  Postcondition:
    is_a_heap (data, make_slice (0, ssize (data)))
*/
    for (int i = 0;i < ssize(data); i++){
        push_up(data,i);
    }
}

bool largest_child (const vector<El>& data, int parent, int unsorted, El& child, int& which)
{// Precondition:
    assert (0 <= unsorted && unsorted < ssize (data));
    assert (0 <= parent && parent < ssize (data));
/*  Postcondition:
    result is true only if the element at parent in data has one or two unsorted child elements;
    only in that case the value of the largest child is child and its index position is which
*/
    int left = left_child(parent);
    int right = right_child(parent);

    if (left <= unsorted){
        if (right <= unsorted && data.at(right) > data.at(left)){
            which = right;
        } 
        else{
            which = left;
        }
        child = data.at(which);
        return true;
    }

    return false;
}

void push_down (vector<El>& data, int unsorted)
{// Precondition:
    assert (is_a_heap (data, make_slice (1,unsorted)));
/*  Postcondition:
    is_a_heap (data, make_slice (0,unsorted+1))
*/
    int n = 0;
    int m = 0;
    El child;

    while (largest_child(data, n,unsorted, child, m) && (data.at(n) < child)){
        swap(data.at(n), data.at(m));
        n = m;
    }
}

void pick_heap (vector<El>& data)
{// Precondition:
    assert (is_a_heap (data, make_slice (data)));
/*  Postcondition:
    data is sorted in increasing order, according to < and == on El (don't forget to implement < and ==)
*/
    for (int unsorted = data.size() - 1; unsorted > 0; unsorted--) {
        swap(data.at(0), data.at(unsorted));
        push_down(data, unsorted);
    }
}

void heap_sort(vector<El>& data)
{// Precondition:
    assert (true);
/*  Postcondition:
    data is sorted in increasing order, according to < and == on El (don't forget to implement < and ==)
*/
    build_heap(data);
    pick_heap(data);
}

/**********************************************************************************************************
 *
 * main function:
 *
 *********************************************************************************************************/
void write_csv_header(ofstream& os) {
    os << "sorting algorithm";
    for (int i = SLICE_STEP; i <= MAX_SLICE; i += SLICE_STEP) {
        os << ',' << i;
    }
    os << endl;
}

void measure_sorting_performance(const vector<El>& tracks, const string& algorithm_name, auto sort_fn, ofstream& os) {
    os << algorithm_name;
    vector<El> sl;
    for (int i = SLICE_STEP; i <= MAX_SLICE; i += SLICE_STEP) {
        Globalcounter = 0;
        sl.assign(tracks.begin(), tracks.begin() + i);
        sort_fn(sl);
        os << ',' << Globalcounter;
    }
    os << endl;
}


void generate_csv (const vector<El>& tracks, ofstream& os)
{// Precondition:
    assert (os.is_open());
    assert (ssize(tracks) >= MAX_SLICE);
/*  Postcondition:
    A CSV file has been written to `os` based on measuring the amount of operations needed to sort growing slices of `tracks`
*/
    measure_sorting_performance(tracks, "insertion sort", insertion_sort, os);
    measure_sorting_performance(tracks, "selection sort", selection_sort, os);
    measure_sorting_performance(tracks, "bubble sort", bubble_sort, os);
    measure_sorting_performance(tracks, "heap sort", heap_sort, os);
}

#ifndef TESTING
int main ()
{// Precondition:
    assert (true) ;
/*  Postcondition:
    the program has generated the csvs of measurements obtained by sorting growing slices of the music databases
*/
    ifstream tracks_file("Tracks.txt");
    ifstream sorted_file("Tracks_sorted.txt");
    ifstream random_file("Tracks_random.txt");
    ifstream reverse_file("Tracks_reverse.txt");
    ofstream tracks_csv("measurements_tracks.csv");
    ofstream sorted_csv("measurements_sorted.csv");
    ofstream random_csv("measurements_random.csv");
    ofstream reverse_csv("measurements_reverse.csv");

    if(!tracks_file.is_open()) {
        cout << "Failed to open Tracks.txt" << endl;
        return 1;
    } else if(!sorted_file.is_open()) {
        cout << "Failed to open Tracks_sorted.txt" << endl;
        return 1;
    } else if(!random_file.is_open()) {
        cout << "Failed to open Tracks_random.txt" << endl;
        return 1;
    } else if(!reverse_file.is_open()) {
        cout << "Failed to open Tracks_reverse.txt" << endl;
        return 1;
    }

    vector<Track> tracks;
    vector<Track> sorted;
    vector<Track> random;
    vector<Track> reverse;
    Track track;

    cout << "Loading databases..." << endl;
    while(tracks_file >> track) {
        tracks.push_back(track);
    }

    while(sorted_file >> track) {
        sorted.push_back(track);
    }

    while(random_file >> track) {
        random.push_back(track);
    }

    while(reverse_file >> track) {
        reverse.push_back(track);
    }

    cout << "Generating Tracks.txt measurements..." << endl;
    generate_csv(tracks, tracks_csv);
    cout << "Generating Tracks_sorted.txt measurements..." << endl;
    generate_csv(sorted, sorted_csv);
    cout << "Generating Tracks_random.txt measurements..." << endl;
    generate_csv(random, random_csv);
    cout << "Generating Tracks_reverse.txt measurements..." << endl;
    generate_csv(reverse, reverse_csv);

    return 0;
}
#endif
