// g++ -O2 -DNDEBUG -std=c++17 -pthread -I../common 04_pooled_allocator.cpp
//

#include <array>     // std::array
#include <iomanip>   // std::setw
#include <iostream>  // std::cout/endl
#include <memory>    // std::allocator/allocator_traits
#include <random>    // std::default_random_engine/uniform_int_distribution
#include <set>       // std::set
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

template <typename T>
memory_pool<T>& get_thread_local_memory_pool()
{
    thread_local memory_pool<T> pool;
    return pool;
}

template <typename T, typename Base = std::allocator<T>>
struct pooled_allocator : private Base {
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using value_type = T;

    using propagate_on_container_copy_assignment =
        typename std::allocator_traits<
            Base>::propagate_on_container_copy_assignment;
    using propagate_on_container_move_assignment =
        typename std::allocator_traits<
            Base>::propagate_on_container_move_assignment;
    using propagate_on_container_swap =
        typename std::allocator_traits<Base>::propagate_on_container_swap;
    using is_always_equal =
        typename std::allocator_traits<Base>::is_always_equal;

    template <class U>
    struct rebind {
        using other = pooled_allocator<U>;
    };

    T* allocate(size_t n)
    {
        if (n == 1) {
            return get_thread_local_memory_pool<T>().allocate();
        } else {
            return Base::allocate(n);
        }
    }

    void deallocate(T* p, size_t n)
    {
        if (n == 1) {
            return get_thread_local_memory_pool<T>().deallocate(p);
        } else {
            return Base::deallocate(p, n);
        }
    }
};

#define LEN 500

std::set<int> s1;
std::set<int, std::less<int>, pooled_allocator<int>> s2;

int main()
{
    // Linux shows a performance difference, depending on whether there
    // have been more than one thread.
    std::thread t{[] {}};
    t.join();

    std::default_random_engine engine;
    std::uniform_int_distribution<int> dist;
    std::array<int, LEN> rand_nums{};
    for (int& num : rand_nums) {
        num = dist(engine);
    }

    {
        auto t1 = rdtsc();
        for (int num : rand_nums) {
            s1.insert(num);
        }
        auto t2 = rdtsc();
        std::cout << "It took " << std::setw(4)
                  << (t2 - t1) / LEN
                  << " cycles by average to insert a number to"
                     "        set<int>"
                  << std::endl;
    }

    {
        auto t1 = rdtsc();
        for (int num : rand_nums) {
            s2.insert(num);
        }
        auto t2 = rdtsc();
        std::cout << "It took " << std::setw(4)
                  << (t2 - t1) / LEN
                  << " cycles by average to insert a number to"
                     " pooled set<int>"
                  << std::endl;
    }

    std::cout << '\n';

    {
        auto t1 = rdtsc();
        while (!s1.empty()) {
            s1.erase(s1.begin());
        }
        auto t2 = rdtsc();
        std::cout << "It took " << std::setw(4)
                  << (t2 - t1) / LEN
                  << " cycles by average to erase  a number from"
                     "        set<int>"
                  << std::endl;
    }

    {
        auto t1 = rdtsc();
        while (!s2.empty()) {
            s2.erase(s2.begin());
        }
        auto t2 = rdtsc();
        std::cout << "It took " << std::setw(4)
                  << (t2 - t1) / LEN
                  << " cycles by average to erase  a number from"
                     " pooled set<int>"
                  << std::endl;
    }

    std::cout << '\n';

    {
        auto t1 = rdtsc();
        for (int num : rand_nums) {
            s1.insert(num);
        }
        auto t2 = rdtsc();
        std::cout << "It took " << std::setw(4)
                  << (t2 - t1) / LEN
                  << " cycles by average to insert a number again to"
                     "        set<int>"
                  << std::endl;
    }

    {
        auto t1 = rdtsc();
        for (int num : rand_nums) {
            s2.insert(num);
        }
        auto t2 = rdtsc();
        std::cout << "It took " << std::setw(4)
                  << (t2 - t1) / LEN
                  << " cycles by average to insert a number again to"
                     " pooled set<int>"
                  << std::endl;
    }

    std::cout << '\n';
}
