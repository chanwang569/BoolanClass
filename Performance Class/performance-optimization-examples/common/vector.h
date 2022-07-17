// A simplistic vector implementation

#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>         // std::copy_n/fill_n/move/move_backward/min
#include <cassert>           // assert
#include <cstddef>           // std::ptrdiff_t/size_t
#include <initializer_list>  // std::initializer_list
#include <iterator>          // std::iterator_traits/advance
#include <limits>            // std::numeric_limits
#include <memory>            // std::allocator/allocator_traits
#include <stdexcept>         // std::length_error
#include <type_traits>       // std::enable_if_t/is_base_of_v
#include <utility>           // std::forward/move/swap

template <typename T, typename Allocator = std::allocator<T>>
class Vector : Allocator {
    using Allocator::allocate;
    using Allocator::deallocate;
    using allocator_traits = std::allocator_traits<Allocator>;

    static_assert(
        allocator_traits::propagate_on_container_move_assignment::value,
        "This Vector only supports allocators that propagate on container "
        "move assignment");

public:
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = pointer;
    using const_iterator = const_pointer;

    Vector() = default;
    explicit Vector(const Allocator& alloc) : Allocator(alloc) {}
    explicit Vector(size_type n, const Allocator& alloc = Allocator())
        : Allocator(alloc)
    {
        allocate_initially(n);
        try {
            for (; end_ != end_cap_; ++end_) {
                construct(end_);
            }
        }
        catch (...) {
            destroy(begin_, end_);
            deallocate(begin_, n);
            throw;
        }
    }
    Vector(size_type n, const T& value,
           const Allocator& alloc = Allocator())
        : Allocator(alloc)
    {
        allocate_initially(n);
        try {
            for (; end_ != end_cap_; ++end_) {
                construct(end_, value);
            }
        }
        catch (...) {
            destroy(begin_, end_);
            deallocate(begin_, n);
            throw;
        }
    }
    Vector(std::initializer_list<T> init,
           const Allocator& alloc = Allocator())
        : Allocator(alloc)
    {
        size_type sz = init.size();
        allocate_initially(sz);
        try {
            for (auto it = init.begin(), it_end = init.end(); it != it_end;
                 ++it, ++end_) {
                construct(end_, *it);
            }
        }
        catch (...) {
            destroy(begin_, end_);
            deallocate(begin_, sz);
            throw;
        }
    }
    Vector(const Vector& rhs) : Allocator(rhs.alloc())
    {
        size_type sz = rhs.size();
        if (sz != 0) {
            allocate_initially(sz);
            try {
                copy_construct(rhs.begin_, rhs.end_, begin_);
            }
            catch (...) {
                deallocate(begin_, sz);
                throw;
            }
            end_ = begin_ + sz;
        }
    }
    Vector(Vector&& rhs) noexcept : Allocator(std::move(rhs).alloc())
    {
        begin_ = rhs.begin_;
        end_ = rhs.end_;
        end_cap_ = rhs.end_cap_;
        rhs.begin_ = rhs.end_ = rhs.end_cap_ = nullptr;
    }
    Vector& operator=(const Vector& rhs) &
    {
        if (this != &rhs) {
            copy_assign_alloc(rhs);
            assign(rhs.begin(), rhs.end());
        }
        return *this;
    }
    Vector& operator=(Vector&& rhs) &
    {
        Vector(std::move(rhs)).swap(*this);
        return *this;
    }
    ~Vector()
    {
        if (begin_ != nullptr) {
            destroy(begin_, end_);
            deallocate(begin_, capacity());
        }
    }

    void swap(Vector& rhs) noexcept
    {
        using std::swap;
        swap(begin_, rhs.begin_);
        swap(end_, rhs.end_);
        swap(end_cap_, rhs.end_cap_);
        if constexpr (allocator_traits::propagate_on_container_swap::value) {
            swap(alloc(), rhs.alloc());
        }
    }

    void assign(size_type count, const T& value)
    {
        size_type offset = 0;
        if (count < capacity()) {
            std::fill_n(begin(), std::min(count, size()), value);
            if (count < size()) {
                destroy(begin() + count, end_);
                shrink(count);
                return;
            } else {
                offset = size();
            }
        } else {
            reset();
            allocate_initially(recommend_capacity(count));
        }
        for (; offset != count; ++offset) {
            construct(end_, value);
            ++end_;
        }
    }

    // Standard vector requires input iterators, but has overloads to deal
    // with different types of iterators.  The current implmentation
    // supports only forward iterators for simplicity.
    template <typename ForwardIt,
              std::enable_if_t<
                  std::is_base_of_v<std::forward_iterator_tag,
                                    typename std::iterator_traits<
                                        ForwardIt>::iterator_category>,
                  bool> = true>
    void assign(ForwardIt first, ForwardIt last)
    {
        auto count = static_cast<size_type>(std::distance(first, last));
        if (count <= capacity()) {
            auto copy_count = std::min(count, size());
            std::copy_n(first, copy_count, begin());
            if (count == size()) {
                return;
            }
            if (count < size()) {
                destroy(begin() + count, end_);
                shrink(count);
                return;
            }
            std::advance(first, static_cast<difference_type>(copy_count));
        } else {
            reset();
            allocate_initially(recommend_capacity(count));
        }
        while (first != last) {
            *end_++ = *first++;
        }
    }

    void assign(std::initializer_list<T> ilist)
    {
        assign(ilist.begin(), ilist.end());
    }

    allocator_type get_allocator() const noexcept { return alloc(); }

    iterator begin() noexcept { return begin_; }
    const_iterator begin() const noexcept { return begin_; }
    iterator end() noexcept { return end_; }
    const_iterator end() const noexcept { return end_; }

    reference operator[](size_type pos) { return begin_[pos]; }
    const_reference operator[](size_type pos) const { return begin_[pos]; }

    reference front() noexcept { return *begin_; }
    const_reference front() const noexcept { return *begin_; }
    reference back() noexcept { return *(end_ - 1); }
    const_reference back() const noexcept { return *(end_ - 1); }

    pointer data() noexcept { return begin_; }
    const_pointer data() const noexcept { return begin_; }

    bool empty() const noexcept { return end_ == begin_; }
    size_type size() const noexcept
    {
        return static_cast<size_type>(end_ - begin_);
    }
    size_type capacity() const noexcept
    {
        return static_cast<size_type>(end_cap_ - begin_);
    }
    size_type max_size() const noexcept
    {
        return std::min<size_type>(
            allocator_traits::max_size(alloc()),
            std::numeric_limits<difference_type>::max());
    }
    void shrink_to_fit()
    {
        if (size() != capacity()) {
            Vector(*this).swap(*this);
        }
    }

    void clear() noexcept
    {
        if (!empty()) {
            shrink(0);
        }
    }
    iterator erase(const_iterator pos)
    {
        assert(begin_ <= pos && pos < end_);
        if (pos < end_ - 1) {
            move_range_backward(pos + 1, end_, const_cast<T*>(pos));
        }
        shrink(size() - 1);
        return begin_ + (pos - begin_);
    }
    iterator erase(const_iterator first, const_iterator last)
    {
        assert(begin_ <= first && first <= last && last <= end_);
        auto len = static_cast<size_type>(last - first);
        if (last < end_) {
            move_range_backward(last, end_, const_cast<T*>(first));
        }
        shrink(size() - len);
        return begin_ + (first - begin_);
    }

    iterator insert(const_iterator pos, const T& value)
    {
        auto offset = static_cast<size_type>(pos - begin());
        if (pos == end()) {
            push_back(value);
        } else {
            if (need_alloc()) {
                insert_realloc_at(offset, value);
            } else {
                pointer ptr = begin_ + offset;
                const_pointer value_ptr = std::addressof(value);
                if (pos <= value_ptr && value_ptr < end_) {
                    ++value_ptr;
                }
                construct(end_, back());
                ++end_;
                move_range_forward(ptr, end_ - 1, ptr + 1);
                *ptr = *value_ptr;
            }
        }
        return begin() + offset;
    }

    iterator insert(const_iterator pos, T&& value)
    {
        auto offset = static_cast<size_type>(pos - begin());
        if (pos == end()) {
            push_back(std::move(value));
        } else {
            if (need_alloc()) {
                insert_realloc_at(offset, std::move(value));
            } else {
                pointer ptr = begin_ + offset;
                construct(end_, back());
                ++end_;
                move_range_forward(ptr, end_ - 1, ptr + 1);
                *ptr = std::move(value);
            }
        }
        return begin() + offset;
    }

    // Standard vector requires input iterators, but has overloads to deal
    // with different types of iterators.  The current implmentation
    // supports only forward iterators for simplicity.
    template <typename ForwardIt,
              std::enable_if_t<
                  std::is_base_of_v<std::forward_iterator_tag,
                                    typename std::iterator_traits<
                                        ForwardIt>::iterator_category>,
                  bool> = true>
    iterator insert(const_iterator pos, ForwardIt first, ForwardIt last)
    {
        auto offset = static_cast<size_type>(pos - begin());
        auto len = static_cast<size_type>(std::distance(first, last));
        reserve(recommend_capacity(size() + len));
        copy_construct(first, last, end_);
        T* new_pos = data() + offset;
        T* new_end = end() + len;
        std::rotate(new_pos, end_, new_end);
        end_ = new_end;
        return new_pos;
    }

    template <typename... Args>
    iterator emplace(const_iterator pos, Args&&... args)
    {
        auto offset = static_cast<size_type>(pos - begin());
        if (pos == end()) {
            emplace_back(std::forward<Args>(args)...);
        } else {
            if (need_alloc()) {
                insert_realloc_at(offset, std::forward<Args>(args)...);
            } else {
                pointer ptr = begin_ + offset;
                construct(end_, std::forward<Args>(args)...);
                ++end_;
                std::rotate(ptr, end_ - 1, end_);
            }
        }
        return begin() + offset;
    }

    template <typename... Args>
    void emplace_back(Args&&... args)
    {
        if (need_alloc()) {
            size_type old_size = size();
            size_type new_capacity = recommend_capacity(old_size + 1);
            T* new_begin = allocate(new_capacity);
            T* new_end = new_begin + old_size;

            try {
                construct(new_end, std::forward<Args>(args)...);
                if constexpr (std::is_nothrow_move_constructible_v<T>) {
                    move_construct(begin_, end_, new_begin);
                } else {
                    try {
                        copy_construct(begin_, end_, new_begin);
                    }
                    catch (...) {
                        destroy(new_end);
                        throw;
                    }
                }
            }
            catch (...) {
                deallocate(new_begin, new_capacity);
                throw;
            }

            ++new_end;
            destroy(begin_, end_);
            deallocate(begin_, capacity());
            begin_ = new_begin;
            end_ = new_end;
            end_cap_ = new_begin + new_capacity;
        } else {
            construct(end_, std::forward<Args>(args)...);
            ++end_;
        }
    }

    void push_back(const T& value) { emplace_back(value); }
    void push_back(T&& value) { emplace_back(std::move(value)); }
    void pop_back() { shrink(size() - 1); }

    void reserve(size_type new_capacity)
    {
        size_type old_capacity = capacity();
        if (new_capacity <= old_capacity) {
            return;
        }
        T* new_begin = allocate(new_capacity);
        T* new_end = new_begin + size();

        if constexpr (std::is_nothrow_move_constructible_v<T>) {
            move_construct(begin_, end_, new_begin);
        } else {
            try {
                copy_construct(begin_, end_, new_begin);
            }
            catch (...) {
                deallocate(new_begin, new_capacity);
                throw;
            }
        }

        destroy(begin_, end_);
        deallocate(begin_, old_capacity);
        begin_ = new_begin;
        end_ = new_end;
        end_cap_ = new_begin + new_capacity;
    }

    void resize(size_type new_size)
    {
        size_type old_size = size();
        if (new_size > old_size) {
            if (new_size <= capacity()) {
                append(new_size);
            } else {
                append_realloc(new_size);
            }
        } else if (new_size < old_size) {
            shrink(new_size);
        }
    }
    void resize(size_type new_size, const value_type& value)
    {
        size_type old_size = size();
        if (new_size > old_size) {
            if (new_size <= capacity()) {
                append(new_size, value);
            } else {
                append_realloc(new_size, value);
            }
        } else if (new_size < old_size) {
            shrink(new_size);
        }
    }

private:
    template <typename... Args>
    void insert_realloc_at(size_type offset, Args&&... args)
    {
        size_type old_size = size();
        size_type new_capacity = recommend_capacity(old_size + 1);
        T* new_begin = allocate(new_capacity);
        T* new_end = new_begin + old_size;
        try {
            construct(new_begin + offset, std::forward<Args>(args)...);
            if constexpr (std::is_nothrow_move_constructible_v<T>) {
                move_construct(begin_, begin_ + offset, new_begin);
                move_construct(begin_ + offset, end_,
                                     new_begin + offset + 1);
            } else {
                try {
                    copy_construct(begin_, begin_ + offset, new_begin);
                    try {
                        copy_construct(begin_ + offset, end_,
                                             new_begin + offset + 1);
                    }
                    catch (...) {
                        destroy(begin_, begin_ + offset);
                        throw;
                    }
                }
                catch (...) {
                    destroy(new_begin + offset);
                    throw;
                }
            }
        }
        catch (...) {
            deallocate(new_begin, new_capacity);
            throw;
        }
        ++new_end;
        destroy(begin_, end_);
        deallocate(begin_, capacity());
        begin_ = new_begin;
        end_ = new_end;
        end_cap_ = new_begin + new_capacity;
    }

    void move_range_forward(const_iterator first, const_iterator last,
                            iterator d_first)
    {
        std::move_backward(first, last, d_first + (last - first));
    }
    void move_range_backward(const_iterator first, const_iterator last,
                             iterator d_first)
    {
        std::move(first, last, d_first);
    }

    size_type recommend_capacity(size_type new_size)
    {
        const size_type ms = max_size();
        if (new_size > ms) {
            throw std::length_error("Vector");
        }
        const size_type cap = capacity();
        if (new_size <= cap) {
            return cap;
        }
        if (cap >= ms / 2) {
            return ms;
        }
        return std::max(2 * cap, new_size);
    }

    bool need_alloc() const { return end_ == end_cap_; }

    allocator_type& alloc() & { return *this; }
    allocator_type&& alloc() && { return std::move(*this); }
    const allocator_type& alloc() const & { return *this; }

    void copy_assign_alloc(const Vector& rhs)
    {
        if constexpr (allocator_traits::
                          propagate_on_container_copy_assignment::value) {
            if (alloc() != rhs.alloc()) {
                reset();
            }
            alloc() = rhs.alloc();
        }
    }

    template <typename... Args>
    void construct(T* ptr, Args&&... args)
    {
        allocator_traits::construct(alloc(), ptr,
                                    std::forward<Args>(args)...);
    }

    void destroy(T* ptr) { allocator_traits::destroy(alloc(), ptr); }
    void destroy(T* begin, T* end)
    {
        for (T* ptr = end; ptr != begin;) {
            destroy(--ptr);
        }
    }

    void shrink(size_type new_size)
    {
        assert(new_size < size());
        T* new_end = begin_ + new_size;
        destroy(new_end, end_);
        end_ = new_end;
    }

    void reset()
    {
        if (begin_ != nullptr) {
            clear();
            deallocate(begin_, capacity());
            begin_ = end_ = end_cap_ = nullptr;
        }
    }

    void allocate_initially(size_type n)
    {
        if (n > max_size()) {
            throw std::length_error("Vector");
        }
        assert(begin_ == nullptr);
        begin_ = allocate(n);
        end_ = begin_;
        end_cap_ = begin_ + n;
    }

    template <typename InputIt>
    void copy_construct(InputIt begin, InputIt end, T* target)
    {
        T* ptr = target;
        try {
            while (begin != end) {
                construct(ptr, *begin);
                ++begin;
                ++ptr;
            }
        }
        catch (...) {
            destroy(target, ptr);
            throw;
        }
    }
    template <typename InputIt>
    void move_construct(InputIt begin, InputIt end, T* target) noexcept
    {
        T* ptr = target;
        while (begin != end) {
            construct(ptr, std::move(*begin));
            ++begin;
            ++ptr;
        }
    }

    void append(size_type new_size)
    {
        T* new_end = begin_ + new_size;
        T* construct_begin = begin_ + size();
        T* ptr = construct_begin;
        try {
            while (ptr != new_end) {
                construct(ptr++);
            }
        }
        catch (...) {
            destroy(construct_begin, ptr);
            throw;
        }
        end_ = new_end;
    }
    void append(size_type new_size, const value_type& value)
    {
        T* new_end = begin_ + new_size;
        T* construct_begin = begin_ + size();
        T* ptr = construct_begin;
        try {
            while (ptr != new_end) {
                construct(ptr++, value);
            }
        }
        catch (...) {
            destroy(construct_begin, ptr);
            throw;
        }
        end_ = new_end;
    }
    void append_realloc(size_type new_size)
    {
        size_type new_capacity = recommend_capacity(new_size);
        T* new_begin = allocate(new_capacity);
        T* new_end = new_begin + new_size;
        T* construct_begin = new_begin + size();
        T* ptr = construct_begin;
        try {
            while (ptr != new_end) {
                construct(ptr++);
            }
            copy_construct(begin_, end_, new_begin);
        }
        catch (...) {
            destroy(construct_begin, ptr);
            deallocate(new_begin, new_capacity);
            throw;
        }
        destroy(begin_, end_);
        deallocate(begin_, capacity());
        begin_ = new_begin;
        end_ = new_end;
        end_cap_ = new_begin + new_capacity;
    }
    void append_realloc(size_type new_size, const value_type& value)
    {
        size_type new_capacity = recommend_capacity(new_size);
        T* new_begin = allocate(new_capacity);
        T* new_end = new_begin + new_size;
        T* construct_begin = new_begin + size();
        T* ptr = construct_begin;
        try {
            while (ptr != new_end) {
                construct(ptr++, value);
            }
            copy_construct(begin_, end_, new_begin);
        }
        catch (...) {
            destroy(construct_begin, ptr);
            deallocate(new_begin, new_capacity);
            throw;
        }
        destroy(begin_, end_);
        deallocate(begin_, capacity());
        begin_ = new_begin;
        end_ = new_end;
        end_cap_ = new_begin + new_capacity;
    }

    T* begin_{};
    T* end_{};
    T* end_cap_{};
};

#endif // VECTOR_H
