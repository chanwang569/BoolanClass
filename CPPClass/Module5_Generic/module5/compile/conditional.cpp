
template <bool _Bp, class _If, class _Then>
struct  conditional {
    typedef _If type;
};


template <class _If, class _Then>
struct  conditional<false, _If, _Then> {
    typedef _Then type;
};


template<typename T>
class Cont {
private:
    T* elems;
public:

    typename std::conditional<std::is_move_constructible<T>::value,T&&,T&>::type foo();

    
};