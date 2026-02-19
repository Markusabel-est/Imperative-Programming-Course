#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

enum Month
{
  January = 1, February, March, April, May, June,
  July, August, September, October, November, December
};

/* The function easter_base uses the Meeus/Jones/Butcher formula to compute
   the number that is used to determine on which month (easter_month below)
   and day (easter_day below) Easter is in the given year.
*/
int easter_base (int year)
{
  const int A = year % 19;
  const int B = year / 100;
  const int C = year % 100;
  const int D = B / 4;
  const int E = B % 4;
  const int F = (B + 8) / 25;
  const int G = (B - F + 1) / 3;
  const int H = (19 * A + B - D - G + 15) % 30;
  const int I = C / 4;
  const int K = C % 4;
  const int L = (32 + 2 * E + 2 * I - H - K) % 7;
  const int M = (A + 11 * H + 22 * L) / 451;
  return H + L - 7 * M + 114;
}

/* The result of easter_year is the day number of the month in which Easter
   occurs in the given year.
*/
int calculate_easter_day (int year)
{
  return (easter_base (year) % 31) + 1 ;
}

/* The result of easter_month is the month in which Easter occurs in the given
   year.
*/
Month calculate_easter_month (int year)
{
  return static_cast<Month> (easter_base (year) / 31) ;
}

/********************************************************************
  Assignment part 1: Leap years
********************************************************************/
bool is_leap_year (int year)
{
  //checks if the year id devisble by four
  if(year % 4 == 0 ){
    //if it is devisble by four then checks if it is one of the years multible of 100
    if (year % 100 == 0 && year % 400 != 0){
      return false;
    }
    else{
      return true;
    }
  }
  else{
    return false;
  }
}

int number_of_days_in_month (int year, Month month)
{
  switch (month){
    
    case February:
      if(is_leap_year(year)){
        return 29;
      }
      else{
        return 28;
      }
    case April:
    case June:
    case September:
    case November:
      return 30;
    default:
      return 31;
    
  }
  
  
}

void run_tests_part_one ()
{
  if (!is_leap_year (400))
    cout << "Test \"is_leap_year (400)\" failed" << endl;

  if (number_of_days_in_month (2000, February) != 29)
    cout << "Test \"number_of_days_in_month (2000, February)\" failed" << endl;

  if (is_leap_year (1700))
    cout << "Test \"is_leap_year (1700)\" failed" << endl;
  
  if (is_leap_year (2013))
    cout << "Test \"is_leap_year (2013)\" failed" << endl;
  
  if (number_of_days_in_month (2013, February) != 28)
    cout << "Test \"number_of_days_in_month (2013, February)\" failed" << endl;
  if (number_of_days_in_month (2013, June) != 30)
    cout << "Test \"number_of_days_in_month (2013, June)\" failed" << endl;
  if (number_of_days_in_month (2013, October) != 31)
    cout << "Test \"number_of_days_in_month (2013, October)\" failed" << endl;


  if (number_of_days_in_month (2012, February) != 29)
    cout << "Test \"number_of_days_in_month (2012, February)\" failed" << endl;
  if (number_of_days_in_month (2012, September) != 30)
    cout << "Test \"number_of_days_in_month (2012, September\" failed" << endl;
  if (number_of_days_in_month (2012, December) != 31)
    cout << "Test \"number_of_days_in_month (2012, December)\" failed" << endl;
  

}

/********************************************************************
  Assignment part 2: Holy days based on Easter
********************************************************************/
string get_date(int easter_day, Month easter_month, int year, int num_of_days){
   

    // we see if the day is befor or after easter
    if(num_of_days < 0){

        //while loop runs until we get to th day
      while(num_of_days < 0){
        // adds and removes numbers every time loop
        easter_day--;
        num_of_days++;
        // if it gets to the first day of the month then changes the month
        if (easter_day == 0){
          easter_month = static_cast<Month>(easter_month-1);
          easter_day = number_of_days_in_month(year, easter_month);

        }
      }
    }
    else{
      while(num_of_days > 0){
        easter_day++;
        num_of_days--;
        if (easter_day == number_of_days_in_month(year, easter_month)){
          easter_month = static_cast<Month>(easter_month + 1);
          easter_day = 0;

        }
      }
    }
   
    string response = to_string(easter_day) + "-" + to_string(easter_month);
    return response;
    
}

string show_carnival (int easter_day, Month easter_month, int year)
{
  return get_date(easter_day, easter_month, year, -49);
}

string show_good_friday (int easter_day, Month easter_month, int year)
{
 
  return get_date(easter_day, easter_month, year, -2);
}

string show_easter (int easter_day, Month easter_month)
{
  string answer = to_string(easter_day) + "-" + to_string(easter_month);
  return answer;
}

string show_whitsuntide (int easter_day, Month easter_month, int year)
{
  return get_date(easter_day, easter_month, year, 49);
}

string show_ascension_day (int easter_day, Month easter_month, int year)
{
  return get_date(easter_day, easter_month, year, 39);
}

void show_holy_days (int year)
{
   int easter_day = calculate_easter_day (year);
   Month easter_month = calculate_easter_month (year);
   

   cout << "Easter is on date " << show_easter (easter_day, easter_month) << endl;
   cout << "Carnival is on date " << show_carnival ( easter_day,  easter_month,  year) << endl;
   cout << "Good Friday is on date " << show_good_friday ( easter_day,  easter_month,  year) << endl;
   cout << "Whitsuntide is on date " << show_whitsuntide ( easter_day, easter_month, year) << endl;
   cout << "Ascension is on date " << show_ascension_day ( easter_day, easter_month, year) << endl;

}

void run_tests_part_two ()
{
  /* Remove the comment once you start to work on part two */
  if (show_carnival (4, April, 2010) != "14-2")
    cout << "Test \"show_carnival (4, April, 2010)\" failed" << endl;
  if (show_carnival (16, April, 2010) != "26-2")
    cout << "Test \"show_carnival (20, April, 2010)\" failed" << endl;
  if (show_carnival (16, April, 400) != "27-2")
    cout << "Test \"show_carnival (16, April, 400)\" failed" << endl;


  /* Add 2 tests for show_good_friday */
  if (show_good_friday(6, April, 2021) != "4-4")
    cout << "Test \"show_good_friday (6, April, 2020)\" failed" << endl;
  if (show_good_friday(2, April, 2020) != "31-3")
    cout << "Test \"show_good_friday (2, April, 2020)\" failed" << endl;

  /* Add 2 tests for show_easter */
  if (show_easter(22, April) != "22-4")
    cout << "Test \"show_easter (22, April, 2020)\" failed" << endl;
  if (show_easter(7, April) != "7-4")
    cout << "Test \"show_easter (7, April, 2020)\" failed" << endl;


  /* Add 2 tests for show_whitsuntide */
  if (show_whitsuntide(18, April, 2020) != "6-6")
    cout << "Test \"show_whitsuntide (22, April, 2020)\" failed" << endl;
  if (show_whitsuntide(21, April, 400) != "9-6")
    cout << "Test \"show_whitsuntide (7, April, 2020)\" failed" << endl;

  /* Add 2 tests for show_ascension_day */
  if (show_ascension_day(13, April, 2020) != "22-5")
    cout << "Test \"show_ascension_day(22, April, 2020)\" failed" << endl;
  if (show_ascension_day(21, April, 400) != "30-5")
    cout << "Test \"show_ascension_day (7, April, 2020)\" failed" << endl;
    

  /* Make sure you have good test coverage */
}


#ifndef TESTING
int main()
{
  /* Ask the user if we should run the tests */
  char tests;
  cout << "Do you want to run the tests? " << endl;
  cout << "If you want to run test type Y but if not type N " << endl;
  cin >> tests;
  if (tests == 'y' || tests == 'Y')
  {
    run_tests_part_one ();
    run_tests_part_two ();
    
  }
  
   int input;
   cout << "Do you want to know the holidays, if yes write a year" << endl;
   cin >> input;
   show_holy_days (input);

    

  /* Add your code for the user interface here */
  return 0;
}
#endif
