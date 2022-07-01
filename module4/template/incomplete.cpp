
template <typename T> 
class B {
    typedef typename T::type Type;
    //Type* p_;
};

// class D : public B<D> {
//     typedef int type;
// };

class A {
public:
    typedef int type;
    type x_;
};

int main()
{
    B<A> b;

    //D d;

}