
#include <cstdlib>
#include <cassert>
#include <iostream>

template <typename T>
struct DeleteByOperator {

    void operator()(T* p) const { 
        delete p;
    }
};


template <typename T>
struct DeleteByFree {
    void operator()(T* p) const {
        p->~T();
        free(p);
    }
};

template <typename T>
struct DeleteDestructorOnly {
    void operator()(T* p) const {
        p->~T();
    }
};

//函数指针
typedef void (*delete_int_t)(int*);
void delete_int(int* p) { delete p; }
template <typename T> void delete_T(T* p) { delete p; }


template <typename T, typename DeletionPolicy= DeleteByOperator<T>>
class SmartPtr {
public:
    explicit SmartPtr(T* p = nullptr,
                      const DeletionPolicy& deletion_policy = DeletionPolicy()
        ) : p_(p),
            deletion_policy_(deletion_policy)
    {}
    ~SmartPtr() { 
        deletion_policy_(p_);
    }
    void release() { p_ = NULL; }
    T* operator->() { return p_; }
    const T* operator->() const { return p_; }
    T& operator*() { return *p_; }
    const T& operator*() const { return *p_; }

private:
    T* p_;//8byte
    DeletionPolicy deletion_policy_;//1 byte
    SmartPtr(const SmartPtr&) = delete;
    SmartPtr& operator=(const SmartPtr&) = delete;
};

class MyClass{ };

int main() {
    
    SmartPtr<MyClass, DeleteByOperator<MyClass>> 
        p1(new C, DeleteByOperator<MyClass>());

    SmartPtr p2(new MyClass, DeleteByOperator<MyClass>());
    
    SmartPtr<MyClass> p3(new MyClass);
   

    SmallHeap h;
    SmartPtr<int,DeleteSmallHeap<int>> 
        q{new(&h) int(42), DeleteSmallHeap<int>(h)};
    

    SmartPtr<int, delete_int_t> p4(new int(42), delete_int);
    

    SmartPtr<int, delete_int_t> p5(new int(42), delete_T<int>);
   

}
