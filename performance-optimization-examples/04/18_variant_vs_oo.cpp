// g++ -O2 -std=c++17 18_variant_vs_oo.cpp
//

#include <cassert>   // assert
#include <chrono>    // std::chrono::duration/duration_cast/steady_clock
#include <iostream>  // std::cout/endl
#include <memory>    // std::unique_ptr/make_unique
#include <ratio>     // std::milli
#include <variant>   // std::variant
#include <vector>    // std::vector

using namespace std;
using std::chrono::duration_cast;
using std::chrono::steady_clock;
using float_ms = std::chrono::duration<double, std::milli>;

#define SHAPE_COUNT 500000

enum shape_id {
    ID_CIRCLE = 1,
    ID_RECTANGLE = 2,
    ID_TRIANGLE = 3,
};

namespace oo_test {

volatile int circle_count;
volatile int rectangle_count;
volatile int triangle_count;

class shape {
public:
    shape() = default;
    shape(const shape&) = delete;
    shape& operator=(const shape&) = delete;
    virtual ~shape() = default;
    virtual void do_something() = 0;
};

class circle : public shape {
public:
    circle(int value) : value_(value) {}
    void do_something() override
    {
        circle_count = circle_count + value_;
    }

private:
    int value_;
};

class rectangle : public shape {
public:
    rectangle(int value) : value_(value) {}
    void do_something() override
    {
        rectangle_count = rectangle_count + value_;
    }

private:
    int value_;
};

class triangle : public shape {
public:
    triangle(int value) : value_(value) {}
    void do_something() override
    {
        triangle_count = triangle_count + value_;
    }

private:
    int value_;
};

void test()
{
    cout << "OO test:      ";
    using shape_type = unique_ptr<shape>;

    vector<shape_type> shapes;
    for (int i = 0; i < SHAPE_COUNT; ++i) {
        shapes.push_back(make_unique<circle>(ID_CIRCLE));
        shapes.push_back(make_unique<rectangle>(ID_RECTANGLE));
        shapes.push_back(make_unique<triangle>(ID_TRIANGLE));
    }

    auto t1 = steady_clock::now();
    for (auto& ptr : shapes) {
        ptr->do_something();
    }
    auto t2 = steady_clock::now();
    cout << "Iterating over " << shapes.size() << " shapes took "
         << duration_cast<float_ms>(t2 - t1).count()
         << " ms" << endl;

    assert(circle_count    == SHAPE_COUNT * ID_CIRCLE);
    assert(rectangle_count == SHAPE_COUNT * ID_RECTANGLE);
    assert(triangle_count  == SHAPE_COUNT * ID_TRIANGLE);
}

} // namespace oo_test

namespace variant_test {

volatile int circle_count;
volatile int rectangle_count;
volatile int triangle_count;

class circle {
public:
    circle(int value) : value_(value) {}
    void do_something()
    {
        circle_count = circle_count + value_;
    }

private:
    int value_;
};

class rectangle {
public:
    rectangle(int value) : value_(value) {}
    void do_something()
    {
        rectangle_count = rectangle_count + value_;
    }

private:
    int value_;
};

class triangle {
public:
    triangle(int value) : value_(value) {}
    void do_something()
    {
        triangle_count = triangle_count + value_;
    }

private:
    int value_;
};

void test()
{
    cout << "variant test: ";
    using shape_type = variant<circle, rectangle, triangle>;

    vector<shape_type> shapes;
    for (int i = 0; i < SHAPE_COUNT; ++i) {
        shapes.emplace_back(circle(ID_CIRCLE));
        shapes.emplace_back(rectangle(ID_RECTANGLE));
        shapes.emplace_back(triangle(ID_TRIANGLE));
    }

    auto t1 = steady_clock::now();
    for (auto& shape : shapes) {
        visit([](auto& x) { x.do_something(); }, shape);
    }
    auto t2 = steady_clock::now();
    cout << "Iterating over " << shapes.size() << " shapes took "
         << duration_cast<float_ms>(t2 - t1).count() << " ms" << endl;

    assert(circle_count    == SHAPE_COUNT * ID_CIRCLE);
    assert(rectangle_count == SHAPE_COUNT * ID_RECTANGLE);
    assert(triangle_count  == SHAPE_COUNT * ID_TRIANGLE);
}

} // namespace variant_test

int main()
{
    oo_test::test();
    variant_test::test();
}
