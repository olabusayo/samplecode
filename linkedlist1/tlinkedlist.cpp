#ifndef TLINKEDLIST_H
#define TLINKEDLIST_H

//This is the implementation file for the list class
template<class T>
klist<T>::klist()
{
  head = new knode<T>;
  head->prev=head;
  head->next=head;
}
template<class T>
klist<T>::klist(T data)
{
  head = new knode<T>;
  head->item = data;
  head->prev=head;
  head->next=head;
}
template<class T>
klist<T>::klist(const klist<T>& list)
{
  
  head = new knode<T>;
  head->prev=head;
  head->next=head;
  knode<T> *hp;//main list  
  hp = list.head->next;
  while(hp != list.head)
  {
    insert_back(hp->item);
    hp=hp->next;
  }
}
template<class T>
klist<T> klist<T>::copy(klist<T> list)
{
  knode<T> *tp;
  tp=head;
  while(tp->next != head)
  {
    list.insert_back(tp->item);
    tp = tp->next;
  }
return list;
}

template<class T>
int klist<T>::size() const 
{
 
  int len = 0; 
  knode<T> *tp;
  
  tp = head;
  while (tp->next != head) 
  {
    tp = tp->next;
    len++;
  }

  return len;
}
template<class T>
bool klist<T>::empty() const
{
  int len = size();
  if(len == 0)
	return true;
  else
	return false;
}
template<class T>
void klist<T>::insert_front(const T& data)
{
  newnode = new knode<T>;
  newnode->item=data;
  newnode->prev = head;
  newnode->next = head->next;
  head->next->prev=newnode;
  head->next=newnode;
  cout << " "<< data << " inserted in front!" <<endl;
}
template<class T>
void klist<T>::insert_back(const T& data)
{
  newnode = new knode<T>;
  newnode->item=data;
  newnode->next = head;
  newnode->prev = head->prev;
  head->prev->next=newnode;
  head->prev=newnode;
  cout<<" " << data << " inserted in back!" <<endl;
}
template<class T>
const T& klist<T>::front() const
{
	  const T& val= head->next->item;
	  return val;
}
template<class T>
const T& klist<T>::back() 
{
 	const T& val = head->prev->item;
 	 return val;
	
}
template<class T>
typename klist<T>::iterator klist<T>::begin()
{
  return iterator(head->next);
}
template<class T>
typename klist<T>::iterator klist<T>::end()
{
  return iterator(head);
}
template<class T>
void klist<T>::output()
{
  if(!empty())
   {
     cout<<"\nYour list has these values "<<endl;
     knode<T> *p;
     p=head->next;
     T val;
     while(p!=head)
      {
        val=p->item;
        cout<<val<<" ";
        p=p->next;
      }
     cout<<"\n"<<endl;
   }
   else
   {
     cout<<"Your list is empty!"<<endl;
   }
}
template<class T>
knode<T>* klist<T>::insert(knode<T>* pointnode, const T& data)
{
 newnode = new knode<T>;
 newnode->item = data;
 *pointnode = *newnode;
 return newnode;
}
template<class T>
void klist<T>::erase(knode<T>* erasenode)
{ 
	knode<T> *tp;
	tp = erasenode;
	tp->prev->next=tp->next;
        tp->next->prev=tp->prev;
        cout << tp->item <<" has been deleted!"<<endl;
        delete tp;

}
template<class T>
void klist<T>::erase(knode<T>* fromnode, knode<T>* tonode)
{
  knode<T> *to;
  knode<T> *from;

 while(to != from)
 {
	to->prev->next=to->next;
        to->next->prev=to->prev;
        cout<<" " << to->item <<" has been deleted!"<<endl;
        delete to;

	to = to->next;
 }
}
template<class T>
void klist<T>::clear()
{
	knode<T> *tp;

	tp=head->next;
	while(tp != head)
	{
		tp->prev->next=tp->next;
		tp->next->prev=tp->prev;
		cout<<" " << tp->item <<" has been deleted!"<<endl;
		delete tp;
		 cout << "The first number in the list is " 
			<<front() <<endl;
    		cout << "The last number in the list is " <<back() <<endl;
		cout << "The size of the list is "<<size()<<endl;
		tp=head->next;
	}
	cout<<" " << tp->item <<" has been deleted!" <<endl;
	delete tp;
	cout<<"List has been cleared and is now empty!" <<endl;
	cout << "The size of the list is "<<size()<<endl;
	klist<T>();	
}
#endif
