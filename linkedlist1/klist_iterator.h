#ifndef KLIST_ITERATOR_H
#define KLIST_ITERATOR_H
//iterator class for linked list
class iterator
{
public:
  friend class klist;
  typedef bidirectional_iterator_tag iterator_category;
  typedef ptrdiff_t difference_type;
  typedef T value_type;
  typedef T* pointer;
  typedef T& reference;
    iterator(): nodeptr(0) {} //constructor
    iterator(knode<T> ini) : nodeptr(ini) {}
    bool operator==(const iterator& rs) const
	{
	  return (nodeptr == rs.nodeptr);
	}//comparison
    bool operator!=(const iterator& rs) const
	{
	  return (nodeptr != rs.nodeptr);
	}//comparison
    T& operator*()
	{
	  if(nodeptr->next == nodeptr)
	      {
		cout<<"\nList is empty! No can do!"<<endl;
		exit(1);
              }
	 	  
                return (nodeptr->item);

        }//pointer operator 
    iterator& operator++()
	{ nodeptr=nodeptr->next;
	  return *this;
        }//prefix invrement
    iterator operator++(int)
	{
	  iterator tmp = *this;
	  nodeptr = nodeptr->next;
          return *this;
	}//postfix
    iterator& operator--()
	{
	  nodeptr=nodeptr->prev;
	  return *this;
	}//prefix
    iterator operator--(int)
	{
	  iterator tmp= *this;
	  nodeptr=nodeptr->prev;
	  return tmp;
	}//postfix
  private:
    knode<T> *nodeptr;//pointer to current node
    iterator(knode<T> *p): nodeptr(p) {};//p becomes nodeptr*/
};
#endif
