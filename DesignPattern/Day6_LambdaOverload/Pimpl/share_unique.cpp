


class Base{
public:
    ~Base()
    {

    }

};

class Sub: public Base{
public:
    ~Sub()
    {
        
    }
};

template<typename T>
class unique_ptr{
    unique_ptr(T* pt){}

}

template<typename T>
class shared_ptr{

    template<typename U>
    shared_ptr(U* pt){}

}

int main(){

    unique_ptr<Base> up1=make_unique<Sub>();
    //~Base();

    shared_ptr<Base> up1=make_shared<Sub>();
    //~Sub();


}