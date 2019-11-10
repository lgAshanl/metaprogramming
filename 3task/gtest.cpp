#include <gtest/gtest.h>
#include "genScatterHierarchy.hpp"
#include <string.h>


template <class T>
struct Holder {
    T value;
};

TEST(basic, init)
{
    using WidgetInfo1 = GenScatterHierarchy<TypeList<int>, Holder>;
    WidgetInfo1 obj1;
    (void)obj1;

    using WidgetInfo2 = GenScatterHierarchy<TypeList<int, std::string>, Holder>;
    WidgetInfo2 obj2;
    (void)obj2;

    using WidgetInfo3 = GenScatterHierarchy<TypeList<int, std::string, double>, Holder>;
    WidgetInfo3 obj3;
    (void)obj3;
}

TEST(basic, eq1)
{
    using WidgetInfo = GenScatterHierarchy<TypeList<int>, Holder>;
    WidgetInfo obj;

    obj.LeftBase::value = 666;

    ASSERT_EQ(obj.at<0>(), 666);
    ASSERT_NE(obj.at<0>(), 333);
}

TEST(basic, eq2)
{
    using WidgetInfo = GenScatterHierarchy<TypeList<int, std::string>, Holder>;
    WidgetInfo obj;
    obj.LeftBase::value = 10;
    obj.RightBase::value = "asd";

    ASSERT_EQ(obj.at<0>(), 10);
    ASSERT_NE(obj.at<0>(), 666);
    ASSERT_EQ(obj.at<1>(), "asd");
    ASSERT_NE(obj.at<1>(), "qwerty");
}

TEST(basic, eq3)
{
    using WidgetInfo = GenScatterHierarchy<TypeList<int, std::string, double>, Holder>;
    WidgetInfo obj;

    obj.LeftBase::value = 100;
    obj.RightBase::LeftBase::value = "qwerty";
    obj.RightBase::RightBase::value = 1.57;

    ASSERT_EQ(obj.at<0>(), 100);
    ASSERT_NE(obj.at<0>(), 666);
    ASSERT_EQ(obj.at<1>(), "qwerty");
    ASSERT_NE(obj.at<1>(), "asd");
    ASSERT_EQ(obj.at<2>(), 1.57);
    ASSERT_NE(obj.at<2>(), 3.14);
}
