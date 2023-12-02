/* P3:
 * File: calendar.cpp
 * ------------------
 * This file implements the p1calendar.h interface
 */

#include <string>
#include <iostream>
//#include "CSC3002OJActive/assignment2/lib.h" // for OJ test
//#include "CSC3002OJActive/assignment2/calendar.h" // for OJ test
//#include "lib.h" // For local test
#include "calendar.h" // For local test
using namespace std;


Month stringToMonth(string s)
{
   if (s == "JANUARY") {
      return JANUARY;
   }
   if (s == "FEBRUARY") {
      return FEBRUARY;
   }
   if (s == "MARCH") {
      return MARCH;
   }
   if (s == "APRIL") {
      return APRIL;
   }
   if (s == "MAY") {
      return MAY;
   }
   if (s == "JUNE") {
      return JUNE;
   }
   if (s == "JULY") {
      return JULY;
   }
   if (s == "AUGUST") {
      return AUGUST;
   }
   if (s == "SEPTEMBER") {
      return SEPTEMBER;
   }
   if (s == "OCTOBER") {
      return OCTOBER;
   }
   if (s == "NOVEMBER") {
      return NOVEMBER;
   }
   if (s == "DECEMBER") {
      return DECEMBER;
   }
}

/* TODO PART:
 * Implementation notes: monthToString
 * -----------------------------------
 * The monthToString function must return some value if the month does not
 * match any of the enumeration constants.  Here, as in the Direction
 * type, the function returns ???.
 */
string monthToString(Month month)
{
   // TODO
   switch (month)
   {
      case(1): return "JANUARY"; break;
      case(2): return "FEBRUARY"; break;
      case(3): return "MARCH"; break;
      case(4): return "APRIL"; break;
      case(5): return "MAY"; break;
      case(6): return "JUNE"; break;
      case(7): return "JULY"; break;
      case(8): return "AUGUST"; break;
      case(9): return "SEPTEMBER"; break;
      case(10): return "OCTOBER"; break;
      case(11): return "NOVEMBER"; break;
      case(12): return "DECEMBER"; break;
   }
   return "";
}

Month operator++(Month &month, int)
{
   // TODO
   if (month == DECEMBER)
   {
      month = JANUARY;
   }
   else
   {
      month = Month(month + 1);
   }
   return month;
}


/*
 * Implementation notes: Constructors
 * ----------------------------------
 * There are three constructors for the Date class.  The default
 * constructor creates a Date with a zero internal value that must
 * be assigned a new value before it is used.  The others initialize
 * the date from the arguments by calling the private initDate method.
 */

Date::Date()
{
   initDate(1, JANUARY, 1900);
}

Date::Date(int day, Month month, int year)
{
   initDate(day, month, year);
}

Date::Date(Month month, int day, int year)
{
   initDate(day, month, year);
}

/*
 * TODO function
 * Implementation notes: getDay, getMonth
 * --------------------------------------
 * 
 */

int Date::getDay()
{
   // TODO
   return day;
}

/*
 * TODO function
 * Method: getMonth
 * Usage: Month month = date.getMonth();
 * -------------------------------------
 * Returns the month.
 */

Month Date::getMonth()
{
   // TODO
   return month;
}

int Date::getYear()
{
   // TODO
   return year;
}


/*
 * TODO function
 * Implementation notes: toString
 * ------------------------------
 * The toString method uses the getters to perform the translation into
 * day/month/year values.
 */

string Date::toString()
{
   // TODO
   string date;
   string monthlist[] = 
   {
      ""
      "Jan",
      "Feb",
      "Mar",
      "Apr",
      "May",
      "Jun",
      "Jul",
      "Aug",
      "Sep",
      "Oct",
      "Nov",
      "Dec",
   };
   date = to_string(day) + "-" + monthlist[month] + "-" + to_string(year);
   return date;
}

void Date::initDate(int day, Month month, int yyyy)
{
   // TODO
   this -> day = day;
   this -> month = month;
   this -> year = yyyy;
}

Date operator+(Date date, int delta)
{
   // TODO
   for (int i = 1; i <= delta; i++)
   {
      date++;
   }
   int dayT = date.getDay();
   Month monthT = date.getMonth();
   int yearT = date.getYear();
   return Date(dayT, monthT, yearT);
}

Date operator-(Date date, int delta)
{
   // TODO
   for (int i = 1; i <= delta; i++)
   {
      date--;
   }
   int dayT = date.getDay();
   Month monthT = date.getMonth();
   int yearT = date.getYear();
   return Date(dayT, monthT, yearT);
}

int operator-(Date d1, Date d2)
{
   // TODO
   int gapDay = d1.getDay() - d2.getDay();
   // obtain difference of index of d1 and d2's month
   int gapMonth = static_cast<int>(d1.getMonth()) - static_cast<int>(d2.getMonth());
   int gapYear = d1.getYear() - d2.getYear();
   if (gapDay < 0)
   {
      gapDay += daysInMonth(d1.getMonth(), d1.getYear());
      gapMonth -= 1;
   }
   if (gapMonth < 0)
   {
      gapMonth += 12;
      gapYear -= 1;
   }
   int bigYear = d1.getYear();
   int smallYear = d2.getYear();
   // if d1.year() is bigger than d2.year than flag=1
   int flag = 1;
   if (gapYear < 0)
   {
      bigYear = d2.getYear();
      smallYear = d1.getYear();
      flag = -1;
   }
   int daycount = 0;
   for (int i = smallYear + 1; i <= bigYear -1;  i++)
   {
      if (isLeapYear(i))
      // add 366 days for leap years and 365 for normal years
      {
         daycount += 366;
      }
      else
      {
         daycount += 365;
      }
   }
   daycount = daycount * flag;
   // days between d2.day() to the end of the month
   daycount += daysInMonth(d2.getMonth(), d2.getYear() - d2.getDay()); 
   Month nextmonth2 = static_cast<Month>(d2.getMonth() + 1);
   for (Month i = nextmonth2; i < 12; i++)
   {
      // days between d2.day() to the end of the month
      daycount += daysInMonth(i, d2.getYear());
   }
   Month beforemonth1 = static_cast<Month>((d1.getMonth() + 11) % 12);
   for (Month i = static_cast<Month>(0); i <= beforemonth1; i++)
   {
      // days between two days
      daycount += daysInMonth(i, d1.getYear());
   }
   daycount += d1.getDay();
   return daycount;
}  


Date &operator+=(Date &date, int delta)
{
   // TODO
   for (int i = 1; i <= delta; i++)
   {
      date = date++;
   }
   int dayT = date.getDay();
   Month monthT = date.getMonth();
   int yeatT = date.getYear();
   date = Date(dayT, monthT, yeatT);
   return date;
}

Date &operator-=(Date &date, int delta)
{
   // TODO
   for (int i = 1; i <= delta; i++);
   {
      date = date--;
   }
   int dayT = date.getDay();
   Month monthT = date.getMonth();
   int yeatT = date.getYear();
   date = Date(dayT, monthT, yeatT);
   return date;
}

Date operator++(Date &date)
{
   // TODO
   int dayT = date.getDay();
   Month monthT = date.getMonth();
   int yearT = date.getYear();
   if (dayT < daysInMonth(monthT, yearT))
   {
      dayT++;
   }
   else
   {
      // reach the end of a month
      if (monthT == DECEMBER)
      {
         monthT = JANUARY;
         yearT++;
      }
      else
      {
         monthT++;
      }
      dayT = 1;
   }
   date = Date(dayT, monthT, yearT);
   return date;
}

Date operator++(Date &date, int)
{
   // TODO
   int dayT = date.getDay();
   Month monthT = date.getMonth();
   int yearT = date.getYear();
   Date dateOri = date;
   if (dayT < daysInMonth(monthT, yearT))
   {
      dayT++;
   }
   else
   {
      // reach the end of a month
      if (monthT == DECEMBER)
      {
         monthT = JANUARY;
         yearT++;
      }
      else
      {
         monthT++;
      }
      dayT = 1;
   }
   date = Date(dayT, monthT, yearT);
   return dateOri;
}

Date operator--(Date &date)
{
   // TODO
   int dayT = date.getDay();
   Month monthT = date.getMonth();
   int yearT = date.getYear();
   if (dayT > 1)
   {
      dayT--;
   }
   else
   {
      // reach the end of a month
      if (monthT == JANUARY)
      {
         monthT = DECEMBER;
         yearT--;
      }
      else
      {
         monthT = Month(monthT - 1);
      }
      dayT = daysInMonth(monthT, yearT);
   }
   date = Date(dayT, monthT, yearT);
   return date;
}

Date operator--(Date &date, int)
{
  // TODO
   int dayT = date.getDay();
   Month monthT = date.getMonth();
   int yearT = date.getYear();
   Date dateOri  = date;
   if (dayT > 1)
   {
      dayT--;
   }
   else
   {
      // reach the end of a month
      if (monthT == JANUARY)
      {
         monthT = DECEMBER;
         yearT--;
      }
      else
      {
         monthT = Month(monthT - 1);
      }
      dayT = daysInMonth(monthT, yearT);
   }
   date = Date(dayT, monthT, yearT);
   return dateOri;
}

bool operator==(Date d1, Date d2)
{
   // TODO
   return d1.getDay() == d2.getDay() && d1.getMonth() == d2.getMonth() && d1.getYear() == d2.getYear();
}

bool operator!=(Date d1, Date d2)
{
   // TODO
   return !operator == (d1, d2);
}

bool operator<(Date d1, Date d2)
{
   // TODO
   return (d1.getYear() < d2.getYear()) || 
   (d1.getYear() == d2.getYear() && d1.getMonth() < d2.getMonth()) ||
   (d1.getYear() == d2.getYear() && d1.getMonth() == d2.getMonth() && d1.getDay() < d2.getDay());
}

bool operator<=(Date d1, Date d2)
{
   // TODO
   return operator < (d1, d2) || operator == (d1, d2);
}

bool operator>(Date d1, Date d2)
{
   // TODO
   return (d1.getYear() > d2.getYear()) || 
   ((d1.getYear() == d2.getYear() && d1.getMonth() > d2.getMonth())) ||
   (d1.getYear() == d2.getYear() && d1.getMonth() == d2.getMonth() && d1.getDay() > d2.getDay());
}

bool operator>=(Date d1, Date d2)
{
   // TODO
   // return true if == or > stands
   return operator == (d1, d2) || operator > (d1, d2);
}

std::ostream &operator<<(std::ostream &os, Date date){
   // TODO
   os << date.toString();
   return os;
}

/*
 * TODO function
 * Implementation notes: daysInMonth
 * ---------------------------------
 * This function is a reasonably literal translation of the old rhyme:
 *
 *    Thirty days has September
 *    April, June, and November
 *    All the rest have 31
 *    Excepting February alone
 *    Which has 28 in fine
 *    And each leap year 29
 */

int daysInMonth(Month month, int year)
{
   // TODO
   switch(month)
   {
      case(1): return 31; break;
      case(2):
      if (isLeapYear(year))
      {
         return 29;
      }
      else
      {
         return 28;
      }
      case(3): return 31; break;
      case(4): return 30; break;
      case(5): return 31; break;
      case(6): return 30; break;
      case(7): return 31; break;
      case(8): return 31; break;
      case(9): return 30; break;
      case(10): return 31; break;
      case(11): return 30; break;
      case(12): return 31; break;
   }
   return 0;
}

/* TODO PART:
 * Implementation notes: isLeapYear
 * --------------------------------
 * This function simply encodes the rule for determining leap years:
 * a leap year is any year divisible by 4, except for years ending in 00,
 * in which case the year must be divisible by 400.
 */

bool isLeapYear(int year)
{
   // TODO
   if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
   {
      return true;
   }
   return false;
}

/* DO NOT modify this main() part */
int main()
{
   int id;
   cin >> id;
   int day, year;
   string mon;
   cin >> day >> mon >> year;

   if (id == 1)
   {
      for (Month month = JANUARY; month <= DECEMBER; month = Month(month + 1))
      {
         cout << monthToString(month) << " has " << daysInMonth(month, year)
              << " days." << endl;
      }
   }
   else if (id == 2)
   {
      Date moonLanding(day, stringToMonth(mon), year);
      cout << "moonLanding = " << moonLanding.toString() << endl;
   }
   else if (id == 3)
   {
      Date moonLanding(day, stringToMonth(mon), year);
      cin >> mon >> day >> year;
      Date kennedyAssassination(stringToMonth(mon), day, year);
      cin >> mon >> day >> year;
      Date newYearsEve(stringToMonth(mon), day, year);
      cin >> day >> mon >> year;
      Date inaugurationDay(day, stringToMonth(mon), year);
      cin >> day >> mon >> year;
      Date electionDay(day, stringToMonth(mon), year);
      cout << "moonLanding = " << moonLanding << endl;
      cout << "kennedyAssassination = " << kennedyAssassination << endl;
      cout << boolalpha;
      cout << "moonLanding < kennedyAssassination = "
           << (moonLanding < kennedyAssassination) << endl;
      cout << "moonLanding > kennedyAssassination = "
           << (moonLanding > kennedyAssassination) << endl;
      cout << "moonLanding == kennedyAssassination = "
           << (moonLanding == kennedyAssassination) << endl;
      cout << "moonLanding == moonLanding = "
           << (moonLanding == moonLanding) << endl;
      cout << "inaugurationDay - electionDay = "
           << (inaugurationDay - electionDay) << endl;
      Date day = newYearsEve;
      cout << "New Year's Eve = " << day++ << endl;
      cout << "New Year's Day = " << day << endl;
      for (Date d = electionDay; d <= inaugurationDay; d++)
      {
         cout << d << endl;
      }
   }
}


