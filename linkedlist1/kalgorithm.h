#ifndef KALGORITHM_H
#define KALGORITHM_H
//kilo's own algorithm collection
#include <iostream>
using namespace std;

template<class iIter, class oIter>
oIter prefix_sum(iIter start, iIter end, oIter result)
{
  typedef typename iterator_traits<oIter>::value_type value_type;
  if(start == end)
	return result;
  value_type __value=*start;
  *result=__value;
  while(++start != end)
  {
   __value = __value + *start;
  *++result = __value;
  }

return ++result;
}
#endif
