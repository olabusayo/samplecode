#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main( )
{
string word, newWord, reType, realWord;
int answer, action;

cout << "Enter any word of your choice: ";
cin >> word;

if( (word == "gateway") || (word == "delldell") || (word == "inspiron") || 
(word == "ubuntu") )
	cout << "friend" << endl;
else
{	
	cerr << "That word is not in the dictionary!" << endl;
	cout << "Do you want to: \n"
		<< "1: Change the word to something in the dictionary\n"
		<< "2: Retype the Word\n"
		<< "3: Add the word to the dictionary\n";
	cin >> answer;

switch (answer)
{
case 1:
	{
	cout << "Do you want to change it to: \n"
		<< "1: gateway\n" << "2: delldell\n" 
		<< "3: inspiron\n" << "4: ubuntu\n";
	cin >> action;
	if (action == 1)
		(realWord="gateway");
	else if(action == 2)
		(realWord="delldell");
	else if(action == 3)
		(realWord="inspiron");
	else if(action == 4)
		(realWord="ubuntu");
	cout << "So you meant "<< realWord <<endl;
	break;
	}
case 2: 
	{
	cout << "Retype word: ";
	cin >> reType;
	cout << "You have retyped " << reType << endl;
	break;
	}
case 3:
	{
	cout << word << "Your word is now part of the dictionary"<< endl;
	break;
	}
default:
	cout << "None" << endl;
	break;
}//end switch

}//end else	

}
