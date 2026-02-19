#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

struct Length
{
	int minutes;							// #minutes (0..)
	int seconds;							// #seconds (0..59)
};

Length new_length (int min, int sec)
{
  // Precondition
  assert (0 <= min && 0 <= sec && sec < 60);

  Length len = { min, sec };
  return len;
}

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

struct TrackDisplay
{
	bool showArtist;						// if true, show name of artist
	bool showAlbum;							// if true, show cd title
	bool showYear;							// if true, show year of appearance
	bool showTrack;							// if true, show track number
	bool showTitle;							// if true, show track title
	bool showTags;                          // if true, show tags
	bool showLength;						// if true, show playing time
	bool showCountry;                       // if true, show countr(y/ies) of artist
};

bool match (string sub, string source)
{// Precondition:
    assert (true) ;
/*  Postcondition:
    Result is true only if sub is a literal (case sensitive) sub string of source.
*/
    return source.find(sub) != string::npos ;
}

ostream& operator<< (ostream& out, const Length length)
{// Precondition:
    assert (true) ;
/*  Postcondition:
    the value of length is shown via out in the format: minutes, ':', seconds (two digits)
*/
    out << length.minutes << ':';

    if(length.seconds < 10){
        out << '0';
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

Length operator+ (const Length& a, const Length& b)
{// Precondition:
    assert (0 <= a.minutes && 0 <= a.seconds && a.seconds < 60 && 0 <= b.minutes && 0 <= b.seconds && b.seconds < 60) ;
/*  Postcondition:
    Result is the sum of a and b.
*/
    int min, sec;

    min = a.minutes + b.minutes;
    sec = a.seconds + b.seconds;

    if(sec >= 60){
        min++;
        sec -= 60;
        
    }
    return {min,sec};
}

void show_track (Track track, TrackDisplay lt, ostream& os)
{// Precondition:
    assert (true) ;
/*  Postcondition:
    only the members of track are shown for which the corresponding member in lt is true.
*/
    if (lt.showArtist) {
        os << track.artist << endl;
    }
    if (lt.showAlbum) {
        os << track.cd << endl;
    }
    if (lt.showYear) {
        os << track.year << endl;
    }
    if (lt.showTrack) {
        os << track.track << endl;
    }
    if (lt.showTitle) {
        os << track.title << endl;
    }
    if (lt.showTags) {
        os << track.tags << endl;
    }
    if (lt.showLength) {
        os << track.time << endl;
    }
    if (lt.showCountry) {
        os << track.country << endl;
    }
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

int match_tracks (const vector<Track>& tracks, string title, bool display)
{// Precondition:
    assert (true);
/*  Postcondition:
    return value is the number of tracks in `tracks` that have a title matching `title`
    if `display` is true, all matched tracks have been printed to `cout`
*/
    TrackDisplay lt = {true, true, true, true, true, true, true, true};
    int count_same = 0;

    for(const Track& track : tracks){
        if(match(title, track.title)){
            count_same++;

            if(display){
                show_track (track, lt, cout);
            }
        }
        
    }
    return count_same;
    
}

bool not_existing(const vector<string>& names_matched, string artist){
    for(const string&  ex_artist : names_matched){
        if(ex_artist == artist){
            return false;
        }
    }
    return true;
}


int match_artists (const vector<Track>& tracks, string artist, bool display)
{// Precondition:
    assert (true);
/*  Postcondition:
    return value is the number of tracks in `tracks` that have an artist matching `artist`, where each artist is only matched once
    if `display` is true, all matched tracks have been printed to `cout`
*/
    TrackDisplay lt = {true, false, false, false, false, false, false, false};
    vector<string> names_matched;
    int count_same = 0;
    

    for(const Track& track : tracks){
        if(match(artist, track.artist)){

            if(not_existing(names_matched, track.artist)){
                names_matched.push_back(track.artist);
                count_same++;
                if(display){
                    show_track (track, lt, cout);
                }
                
            }
        }
    }
    return count_same;

}

int match_cds (const vector<Track>& tracks, string artist, bool display)
{// Precondition:
    assert (true);
/*  Postcondition:
    return value is the number of tracks in `tracks` that have an artist matching `artist`, where each (artist, cd) pair is only matched once
    if `display` is true, all matched tracks have been printed to `cout`
*/
    TrackDisplay lt = {true, true, true, false, false, false, false, false};
    vector<string> cd;
    int count_same = 0;
    

    for(const Track& track : tracks){
        if(match(artist, track.artist)){
            if(not_existing(cd, track.cd)){
                cd.push_back(track.cd);
                count_same++;
                if(display){
                    show_track (track, lt, cout);
                }
                
            }
        }
    }
    return count_same;

}

int number_of_cds (const vector<Track>& tracks)
{// Precondition:
    assert (true);
/*  Postcondition:
    return value is the number of tracks in `tracks` that have an unique (artist, cd) pair, where each pair is counted once
*/
    vector<string> cd;
    int count_same = 0;
    
    for(const Track& track : tracks){
        if(not_existing(cd, track.cd)){
            cd.push_back(track.cd);
            count_same++;
                
        }
    }
    return count_same;
}

int read_tracks (string filename, vector<Track>& tracks, bool show_content)
{// Precondition:
    assert (true);
/*  Postcondition:
    tracks is a copy of the tracks that are found in the file with file name filename, and result
    is the number of tracks that have been read.
    Only if show_content, then all read tracks are shown on screen.
*/
    ifstream in(filename);
    if(!in){
        return 0;
    }
    
    int read = 0;
    Track track;
    TrackDisplay lt = {true, true, true, true, true, true, true, true};

    while(in >> track){
        tracks.push_back(track);
        read++;
        if(show_content){
            show_track(track, lt, cout);
        }

    }
    
    return read;
}

#ifndef TESTING
int main ()
{// Precondition:
    assert (true) ;
/*  Postcondition:
    the music database "Tracks.txt" has been read (if present and correctly formatted),
    and the number of tracks read has been printed to `cout`,
    and the user has entered commands, ending with "stop"
*/
    const string TRACKS_FILE = "Tracks.txt";
    vector<Track> tracks;
    string command;

    cout << "Attempting to read tracks from " << TRACKS_FILE << endl;
    cout << "Read " << read_tracks(TRACKS_FILE, tracks, false) << " tracks" << endl;

    do {
        cout << "\nEnter one of the following commands:\n";
        cout << "- tracks <title>   - Show all tracks whose title matches <title>\n";
        cout << "- artists <artist> - Show all tracks whose artist matches <artist>\n";
        cout << "- cds <artist>     - Show all albums whose artist matches <artist>\n";
        cout << "- #cds             - Total number of albums\n";
        cout << "- stop             - Stop and exit" << endl;
        cout << "> ";
        cin >> command;

        if(command == "tracks") {
            string title;
            cin >> ws; // skip whitespace before title
            getline(cin, title);
            int matches = match_tracks(tracks, title, true);
            cout << "\nFound " << matches << " match(es)" << endl;
        } else if(command == "artists") {
            string artist;
            cin >> ws; // skip whitespace before artist
            getline(cin, artist);
            int matches = match_artists(tracks, artist, true);
            cout << "\nFound " << matches << " match(es)" << endl;
        } else if(command == "cds") {
            string artist;
            cin >> ws; // skip whitespace before artist
            getline(cin, artist);
            int matches = match_cds(tracks, artist, true);
            cout << "\nFound " << matches << " match(es)" << endl;
        } else if(command == "#cds") {
            int cds = number_of_cds(tracks);
            cout << "\nFound " << cds << " unique albums" << endl;
        } else if(command != "stop") {
            cout << "Unknown command '" << command << "', please try again" << endl;
        }
    } while(command != "stop");

	return 0;
}
#endif
