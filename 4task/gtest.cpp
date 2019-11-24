#include <gtest/gtest.h>
#include "functor.hpp"

int function(int, float, short)
{
    return 666;
}

class Y
{ };

class X {
public:
    float process(Y& y)
    {
        (void)y;
        return 6.66;
    }
};

TEST(basic, fn)
{
    // обычные функции
    auto functor1 = make_functor(&function, 1, 2, 3);
    int x = functor1.call();
    (void)x;
}

TEST(basic, class)
{    
    // функции-члены
    auto functor2 = make_functor(&X::process, Y());
    X x;
    float y = functor2.call(x);
    (void)y;
}

TEST(basic, lambd)
{
    // лямбды
    Y y;
    auto functor3 = make_functor([](Y*) {}, y);
    functor3.call();
}
