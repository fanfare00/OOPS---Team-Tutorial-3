////////////////////////////////////////////////////////////////////////////////
///		
///		P#3TT - Operator Overloading and Macros
///
///			Author:				James McCarthy
///			Class:				CISC 205 - OOPS Fall 2014
///			Instructor:			Professor Forman
///		
////////////////////////////////////////////////////////////////////////////////

/*Macros, also known as pre-processor directives - 
these are fragments of code or full statements that get inserted into
the source code at compile time.*/

/*A for each loop for iterating over a list of items, notice that there's no 
semi colon here. Also the type is not defined here either*/
#define foreach(list, index) for(index = 0; index < list.size(); index++)

/* a for loop that can be told to loop N number of times*/
#define forloop(n, i) for (i = 0; i < n; i++)

/*special macro functions that handle setting and printing data from the JTime class*/
#define parseTime(aTime, input) aTime.minutes = input%100; aTime.hours = input/100;
#define printTime(aTime) cout << setfill('0') << setw(2) << aTime.hours << ":" << setfill('0') << setw(2) << aTime.minutes;

/*a macro that can be used to perform operations on user input regardless of
type and without storing it inside a variable. 

For example, instead of something like...
	
	int userInput;
	cin << userInput;
	function(userInput);

...you can just type function(userInput(int));

*/
#define userInput(type) get<type>(std::cin)


#define print( x ) cout << #x "\n\n"
#define nextline() cout << 

#include <iostream>
#include <string>
#include <iomanip> 
#include <vector>

using namespace std;


////////////////////////////////////////////////////////////////////////////////
////	JTime class
///			a class that holds hours and minutes and the special operator functions
///			to manipulate the data in the context of time
////////////////////////////////////////////////////////////////////////////////

class JTime
{
public:
	int hours;
	int minutes;

//Member function operators cannot have more than 1 argument
//The first argument is implicity *this while the second is supplied
	//JTime operator+(JTime &t1, JTime &t2);

//Do this instead
	JTime operator+(const JTime& t);
	JTime operator-(const JTime& t);
	
};

JTime JTime::operator+(const JTime& t)
{
	JTime temp = *this;  
	temp.minutes += t.minutes;
	temp.hours += temp.minutes / 60;
	temp.minutes %= 60;
	temp.hours += t.hours;

	//?: is a non-redefineable operator
	temp.hours >= 13 ? temp.hours -= 12 : (temp.hours < 1 ? temp.hours += 12 : temp.hours);
	
	
	return temp;
}

JTime JTime::operator-(const JTime& t)
{
	JTime temp = *this;
	temp.minutes -= t.minutes;
	temp.hours -= temp.minutes / 60;
	temp.minutes %= 60;
	temp.hours -= t.hours;
	return temp;
}

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
/// CUSTOM DEFINED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

//manipulation of the addition operator += to add strings to a list of strings
void operator+=(vector<string>& things, string aThing)
{
	things.push_back(aThing);
}

//manipulation of the subtraction operator -= to substract strings to a list of strings
void operator-=(vector<string>& things, int thingIndex)
{
	things.erase(things.begin() + thingIndex);
}

//A template to allow the use of cin without creating a variable
template<class T>
T get(std::istream& is)
{
	T result;
	is >> result;
	return result;
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
	


	////////////////////////////////////////////////////////////////////////////
	//	EXAMPLE #1
	//	Operator Overloading - Minus
	////////////////////////////////////////////////////////////////////////////

		JTime bewitchingHour;
		bewitchingHour.hours = 12;
		bewitchingHour.minutes = 45;

		JTime currentTime;
		int input;

	////////////////////////////////////////////////////////////////////////////

		cout << "Lets find out how much time is left until the bewitching hour:\n\n";

		cout << "Enter the current time in the format HHMM like 1245: ";

		input = userInput(int);

		parseTime(currentTime, input);

		cout << "\n\nTime until the bewitching hour: \n";
		
		cout << "\n\t" << abs((currentTime - bewitchingHour).hours) << " hours and "
			 << abs((currentTime - bewitchingHour).minutes) << " minutes.\n\n";

	////////////////////////////////////////////////////////////////////////////
	//	EXAMPLE #2
	//	Operator Overloading - Plus
	////////////////////////////////////////////////////////////////////////////

		JTime startTime;
		JTime endTime;

	////////////////////////////////////////////////////////////////////////////

			
		print("""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""");

		print(Lets find out what time your movie gets out);
		print(Enter the starting time of the movie in the format HHMM: );
		
		input = userInput(int);

		parseTime(startTime, input);

		print(Enter the duration of the movie in the format HHMM: );

		input = userInput(int);

		parseTime(endTime, input);

		print( "\nYour movie will end at " << (startTime + endTime).hours << ":" << (startTime + endTime).minutes );

		print(hmmm that time looks strange lets try that again);

		print( Your movie will end at: );

		printTime((startTime + endTime));

		
	////////////////////////////////////////////////////////////////////////////
	//	EXAMPLE #3
	//	Operator Overloading - Addition
	////////////////////////////////////////////////////////////////////////////

		vector<string> snacks;
		string aSnack;
		int i;

	////////////////////////////////////////////////////////////////////////////

		cout << "\n\n---------------------------------------------------------------\n";
		cout << "You're allowed to get four snacks at your movie, let's make a list.\n\n";

		//notice how there's not a semi-colon here
		//forloop is not a complete statement, its a code fragment
		//at compile time, its replaced with (for i = 0; i < n; i++)

		forloop(4, i)
			cout << "Enter snack choice #" << (i+1) << ": ",
			snacks += userInput(string);

		//for loops only work on a single statement without braces
		//the comma operator is used to combine the two statements
		//although I could have just used braces instead

		cout << "\nOkay, so here's your list of snacks:\n";
		//again, no semi-colon
		foreach(snacks, i)
			cout << "\t" << (i+1) << ". " + snacks[i] + "\n";

	////////////////////////////////////////////////////////////////////////////
	//	EXAMPLE #4
	//	Operator Overloading - Subtraction
	////////////////////////////////////////////////////////////////////////////

		cout << "---------------------------------------------------------------\n";
		cout << "Actually, I lied earlier. You're only allowed to get three snacks.\n\n";

		cout << "Enter the number of the snack you want to get rid of: ";
		i = userInput(int);

		cout << "\n\nAlright, let's get rid of the " + snacks[i-1] + ". That leaves you with: \n";

		snacks -= (i - 1);

		foreach(snacks, i)
			cout << "\t" << (i + 1) << ". " + snacks[i] + "\n";

	cin.ignore();
	cin.ignore();
	return 0;
}