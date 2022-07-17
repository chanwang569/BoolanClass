#include "short_alloc.h"
#include <iostream>
#include <new>
#include <vector>


std::size_t memory = 0;
std::size_t alloc = 0;

void* operator new(std::size_t s) 
{
    memory += s;
    ++alloc;
    return malloc(s);
}

void  operator delete(void* p) noexcept
{
    --alloc;
    free(p);
}

void memuse()
{
    std::cout << "memory = " << memory << '\n';
    std::cout << "alloc = " << alloc << '\n';
}

template <class T, std::size_t BufSize = 200>
using SmallVector = std::vector<T, short_alloc<T, BufSize, alignof(T)>>;

int main()
{
    
    SmallVector<int>::allocator_type::arena_type a;
   
    SmallVector<int> v{a};
  
    v.push_back(1);
    memuse();
    v.push_back(2);
    memuse();
    v.push_back(3);
    memuse();
    v.push_back(4);
    memuse();
    
    for (auto i : v)
        std::cout << i << ' ';
    std::cout << '\n';
}