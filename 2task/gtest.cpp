#include <gtest/gtest.h>
#include "tuple.hpp"

TEST(basic, init)
{
    Tuple<int> tuple;
    ASSERT_EQ(tuple.getIndexOf<int>(), 0);
    ASSERT_EQ(tuple.getIndexOf<int64_t>(), -1);

    Tuple<int32_t, Tuple<int64_t> > tuple2;
    ASSERT_EQ(tuple2.getIndexOf<int32_t>(), 0);
    ASSERT_EQ(tuple2.getIndexOf<int64_t>(), 1);
    ASSERT_EQ(tuple2.getIndexOf<float>(), -1);

    struct Tuple<int8_t, Tuple<float, Tuple<int32_t, Tuple<int64_t> > > > tuple3 =
        tuple2.push<float>().push<int8_t>();
    ASSERT_EQ(tuple3.getIndexOf<int8_t>(), 0);
    ASSERT_EQ(tuple3.getIndexOf<float>(), 1);
    ASSERT_EQ(tuple3.getIndexOf<int32_t>(), 2);
    ASSERT_EQ(tuple3.getIndexOf<int64_t>(), 3);
    ASSERT_EQ(tuple3.getIndexOf<double>(), -1);
}