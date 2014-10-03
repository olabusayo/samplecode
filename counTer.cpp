
//Name:Olabusayo Kilo
//Date:2/25/2008
//Description:This class provides a simulation for a clicker that counts 
//up to a given max value.

#include <iostream>
using namespace std;

#include "cT.h"

int main( )
{
	int MAX_VALUE_OF_COUNTER,incVal,newMaxVal;
	char ans,nans,aans;//answer,newanswer,anotheranswer
	char command;
	cout << "Enter the maximum digit display of your counter: ";
	cin >> MAX_VALUE_OF_COUNTER;
	counTer count1(MAX_VALUE_OF_COUNTER);

	cout	<< "Your counter counts up to " << MAX_VALUE_OF_COUNTER
		<<endl;
		cout << " f, followed by a space and a number\n"
			<< " increments tens of dollars by that number!\n"
			<< " d, followed by a space and a number\n"
                        << " increments dollars by that number!\n"  	 
			<< " s, followed by a space and a number\n"
                        << " increments dimes by that number!\n" 
			<< " a, followed by a space and a number\n"
                        << " increments cents by that number!\n";

	do
	{
		
		cout<< " Enter your command: ";
		cin >> command >> incVal;
		count1.input(command,incVal); 
		count1.output();
		cout << " Do you wish to continue?(..y..|..n..)";
		cin >> ans;
	}
	while((ans == 'y')||(ans == 'Y'));
	cout << "Do you wish to reset the counter?(..y..|..n..)";
	cin >> nans;//new answer
	if((nans == 'y')||(nans == 'Y'))
	{
		cout << "Do you have a new max value?(..y..|..n..)";
	        cin >> aans;
		if((aans == 'y')||(aans == 'Y'))
		{
			cin >> newMaxVal;
			count1.reset(newMaxVal);
		}
		else
		{		
			count1.reset();
		}
		cout << "Reset Counter: \n";
		count1.output();
	}
	else
	{
		cout << "Thank you for using the counter!\n"
			<< "Final display:\n";
		count1.output();
	}
	return 0;
	
}
