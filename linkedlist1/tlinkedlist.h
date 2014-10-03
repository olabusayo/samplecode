#ifndef TLINKEDLISTS_H
#define TLINKEDLISTS_H
//program to demonstrate linked lists
#include <iostream>
using namespace std;

//Structure for nodes:
template<class T>
struct knode
{
  T item;     // data 
  knode<T> *prev;  // points to left neighbor
  knode<T> *next;  //points to right neighbor
};
template<class T>
class klist
{
public:
  klist();//default constructor
  klist(T data);//constuctor for provided data
  klist(const klist<T>& list);//copy constructor
  int size() const;//returns the number of data items in a list
  bool empty() const;   //returns true if the list is empty
  void insert_front(const T&); 
    //insert date item to front of list
  void insert_back(const T& data); 
    //insert data item to tail of list
  const T& front() const;
    //fetch the first  stored in list
  const T& back();
    //fetch last data item stored in list
  knode<T>* insert(knode<T>* pointnode, const T& data);
    //insert a data item at the pointed position,
    //and return a pointer pointing at the inserted integer
  klist<T> copy(klist<T> list);//copy
  void output();//output
  void erase(knode<T>* erasenode);
   //delete an integer at the pointed position
  void erase(knode<T>*, knode<T>*);
    // delete everything between the pointed positions (which includes
    //the integer pointed by the first pointer, but does not 
    //include the integer pointed by the second pointer);
  void clear();// delete all data items;
  #include "klist_iterator.h"
  iterator begin();
  iterator end();


private:
   knode<T> *head;	//points to head of file
   knode<T> *newnode; //points to new node in file
};	
#include "tlinkedlist.cpp"
#endif
