//Olabusayo Kilo
//3/5/2008
//HW5:class for the implementation of a linked list
#include <iostream>
#include <cstdlib>
#include <sys/time.h>//for time of day
#include <ctime>//for seed
#include <list>
#include <numeric>
#include "tlinkedlist.h"
#include "tlinkedlist.cpp"
#include <algorithm>
#include "kalgorithm.h"

using namespace std;

int main()
{
klist<int> intlist;
klist<int>::iterator iter;
list<int> stlList;
list<int>::iterator stliter;
timeval tim;
//time
        gettimeofday(&tim, NULL);
        double t1=tim.tv_sec+(tim.tv_usec/1000000.0);

//driver
for(int i=1;i<10;i++)
{
	intlist.insert_back(i);
}
cout<<"List before Partial Sum:";
intlist.output();
partial_sum(intlist.begin(),intlist.end(),intlist.begin());
cout<<"List after Partial Sum:";
intlist.output();


for(int i=1;i<10;i++)
{
	stlList.push_back(i);
}
stliter = stlList.begin();
cout<<"stlList has these values:"<<endl;
while(stliter != stlList.end())
{
 cout<<*stliter<<" ";
 stliter++;
}
cout<<" "<<endl;

cout<<"\nstlList now has these values:"<<endl;
prefix_sum(stlList.begin(),stlList.end(),stlList.begin());
stliter = stlList.begin();
while(stliter != stlList.end())
{
 cout<<*stliter<<" ";
 stliter++;
}
cout<<" "<<endl;
//time
  gettimeofday(&tim, NULL);
  double t2=tim.tv_sec+(tim.tv_usec/1000000.0);
  printf("%.6lf seconds elapsed\n", t2-t1);

return 0;
}
