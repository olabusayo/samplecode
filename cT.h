//This is the header file cT.h. This is the interface for the class 
//counTer.

#include <iostream>
using namespace std;

class counTer
{
public:
	counTer(int maxValue);//initializes maximum number display
	counTer();//initializes maximum number display to 0
	
	void reset();
	//sets the counter display to 0.
	void reset(int max);
	//sets counter display to 0 but also sets maxi number display
	void incr1();
	//increments units or cents by 1
	void incr10();
	//increments tens or dimes by 1
	void incr100();
	//incrmements hundreds or dollars by 1
	void incr1000();
	//increments thousands or tens of dollars by 1
	bool overflow(int value,int valueMax);
	//detects overflow
	void input(char choice,int increment);
	//gets directions from user
	void output();
	//displays counter;
	int MAX_VALUE_OF_COUNTER;
private:
	int cents,dimes,dollars,tenDollars;
	int centsMax,dimesMax,dollarsMax,tenDollarsMax;
};
