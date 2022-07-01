#include <iostream>
#include <string>
#include <memory>
#include <vector>
using namespace std;


struct T1 {};
struct T2 {};

template <typename T>
struct traits {
    typedef T1 tag;
};
template <>
struct traits<std::string> {
    typedef T2 tag;
};

template<typename Iterator>
struct iterator_traits {
  using iterator_category  = typename Iterator::iterator_category;
  using value_type         = typename Iterator::value_type;
  using difference_type    = typename Iterator::difference_type;
  using pointer            = typename Iterator::pointer;
  using reference          = typename Iterator::reference;
};

template<typename Iterator>
struct  iterator_traits<Iterator*>
{
    typedef ptrdiff_t difference_type;
    typedef typename remove_cv<Iterator>::type value_type;
    typedef Iterator* pointer;
    typedef Iterator& reference;
    typedef random_access_iterator_tag iterator_category;
    typedef contiguous_iterator_tag    iterator_concept;
};
