//This is the implementation file cT.cpp of the class counTer.
//The interface of the class counTer is in the header file cT.h.

#include <iostream>
#include <cstdlib>//for exit
#include <cmath>//for math calculations
using namespace std;
#include "cT.h"

counTer::counTer(int maxValue)
:cents(0),dimes(0),dollars(0),tenDollars(0),centsMax(maxValue%10),dimesMax((maxValue%100)/10),dollarsMax(((maxValue%1000)/100)),tenDollarsMax((maxValue/1000))
{
	if(maxValue<0)
		{
			cout << "Illegal Counter Value!\n";
			exit(1);
		}
}
counTer::counTer()
:cents(0),dimes(0),dollars(0),tenDollars(0),centsMax(0),dimesMax(0),dollarsMax(0),tenDollarsMax(0)
{}
//reset
void counTer::reset()
{	
	cents=0;
	dimes=0;
	dollars=0;
	tenDollars=0;
	centsMax=0;
	dimesMax=0;
	dollarsMax=0;
	tenDollarsMax=0;
	counTer();
}

//reset with maximum values
void counTer::reset(int max)
{
	cents=0;
        dimes=0;
        dollars=0;
        tenDollars=0;
	centsMax=(max%10);
	dimesMax=((max%100)/10);
	dollarsMax=(((max%1000)/100));
	tenDollarsMax=((max/1000));
	if(max<0)
	{
		cout << "Illegal Counter Value!\n";
		exit(1);

	}
}

//gets increment orders from user
void counTer::input(char choice,int increment)
{
	switch(choice)
	{
		case 'a':
		if(increment > centsMax)
			increment = centsMax;	
		for(int i=0;i<increment;i++)
		{
			incr1();
		}
		break;
		case 's':
		if(increment > dimesMax)
			increment = dimesMax;	
		for(int i=0;i<increment;i++)
		{
			incr10();
		}
		break;
		case 'd':
		if(increment > dollarsMax)
			increment = dollarsMax;	
		for(int i=0;i<increment;i++)
		{
			incr100();
		}
		break;
		case 'f':
		if(increment > tenDollarsMax)
			increment = tenDollarsMax;	
		for(int i=0;i<increment;i++)
		{
			incr1000();
		}
		break;
		default:
		cout << "Unknown order give!";
	}
}


//checks for overflow
bool counTer::overflow(int value,int valueMax)
{
	if(value >= valueMax)
	return true;
	else
	return false;
}

//increments units by 1, except in cases of carryover
void counTer::incr1()
{
	bool over = overflow(cents,centsMax);
	if(!over)
		cents++;
	else
	{	cents=0;
		incr10();
	}
}

//increments tens by 1, except in cases of carryover
void counTer::incr10()
{
	bool over= overflow(dimes,dimesMax);
	if(!over)
		dimes++;
	else
	{
		dimes=0;
		incr100();
	}
}

//increments hundreds by 1, except in cases of carryover
void counTer::incr100()
{
	bool over= overflow(dollars,dollarsMax);
	if(!over)
		dollars++;
	else
	{
		dollars=0;
		incr1000();
	}
}

//increments thousand by 1, except in cases of carryover
void counTer::incr1000()
{
	bool over= overflow(tenDollars,tenDollarsMax);
	if(!over)
		tenDollars++;
	else
	{
		tenDollars=0;
		cout << "Red Light! Red Light! Over Flow!" <<endl;
		exit(1);
	}
}


//uses iostream
void counTer::output()
{
	cout	<< "Counter display:\n"
		<< "$" << tenDollars
		<< dollars << "." << dimes << cents <<endl;
}
