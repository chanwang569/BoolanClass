// g++ -O2 -DNDEBUG -std=c++17 -pthread -I../common 03_memory_pool.cpp
//

#include <array>     // std::array
#include <iostream>  // std::cout/endl
#include <thread>    // std::thread
#include <assert.h>  // assert
#include <stddef.h>  // size_t
#include "rdtsc.h"   // rdtsc

template <typename T>
struct memory_config {
    static constexpr size_t chunk_size = 64;
};

template <typename T>
struct memory_chunk {
    union node {
        T data;
        node* next;
        node() {}
        ~node() {}
        node(const node&) = delete;
        node& operator=(const node&) = delete;
    };
    std::array<node, memory_config<T>::chunk_size> storage_;
    memory_chunk();
};

template <typename T>
memory_chunk<T>::memory_chunk()
{
    for (size_t i = 0; i < storage_.size() - 1; ++i) {
        storage_[i].next = &storage_[i + 1];
    }
    storage_[storage_.size() - 1].next = nullptr;
}

template <typename T>
class memory_pool {
public:
    memory_pool() = default;
    memory_pool(const memory_pool&) = delete;
    memory_pool& operator=(const memory_pool&) = delete;
    T* allocate();
    void deallocate(T* ptr);

private:
    typename memory_chunk<T>::node* free_list_{};
};

template <typename T>
T* memory_pool<T>::allocate()
{
    if (free_list_ == nullptr) {
        free_list_ = (new memory_chunk<T>)->storage_.data();
    }
    T* result = &free_list_->data;
    assert(reinterpret_cast<uintptr_t>(result) % sizeof(T*) == 0);
    free_list_ = free_list_->next;
    return result;
}

template <typename T>
void memory_pool<T>::deallocate(T* ptr)
{
    assert(reinterpret_cast<uintptr_t>(ptr) % sizeof(T*) == 0);
    auto free_item = reinterpret_cast<typename memory_chunk<T>::node*>(ptr);
    free_item->next = free_list_;
    free_list_ = free_item;
}

class Obj1 {
public:
    Obj1() {}
    ~Obj1() {}
};

class Obj2 {
public:
    Obj2() {}
    ~Obj2() {}
    void* operator new(size_t size);
    void operator delete(void* ptr) noexcept;
};

memory_pool<Obj2> inst;

void* Obj2::operator new(size_t size)
{
    assert(size == sizeof(Obj2));
    (void)size;
    return inst.allocate();
}

void Obj2::operator delete(void* ptr) noexcept
{
    inst.deallocate(static_cast<Obj2*>(ptr));
}

#define LEN 500
#define LOOPS 10000

std::array<Obj1*, LEN> ptr_array1{};
std::array<Obj2*, LEN> ptr_array2{};

int main()
{
    // Linux shows a performance difference, depending on whether there
    // have been more than one thread.
    std::thread t{[] {}};
    t.join();

    {
        auto t1 = rdtsc();
        for (int i = 0; i < LOOPS; ++i) {
            for (int j = 0; j < LEN; ++j) {
                ptr_array1[j] = new Obj1;
            }
            for (int j = 0; j < LEN; ++j) {
                delete ptr_array1[j];
            }
        }
        auto t2 = rdtsc();
        std::cout << (t2 - t1) / LOOPS / LEN
                  << " cycles for each allocation and deallocations on Obj1"
                  << std::endl;
    }

    {
        auto t1 = rdtsc();
        for (int i = 0; i < LOOPS; ++i) {
            for (int j = 0; j < LEN; ++j) {
                ptr_array2[j] = new Obj2;
            }
            for (int j = 0; j < LEN; ++j) {
                delete ptr_array2[j];
            }
        }
        auto t2 = rdtsc();
        std::cout << (t2 - t1) / LOOPS / LEN
                  << " cycles for each allocation and deallocations on Obj2"
                  << std::endl;
    }
}
