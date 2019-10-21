#include <gtest/gtest.h>
#include "csvreader.hpp"

TEST(basic, init)
{
    csvreader<int32_t, int32_t, double> csv{};
    
    ASSERT_TRUE(csv.read_file("./gtest/init"));
	
    ASSERT_EQ(csv[0].at<0>(), 1);
    ASSERT_EQ(csv[0].at<1>(), 3);
    ASSERT_EQ(csv[0].at<2>(), 5.0);
    ASSERT_EQ(csv[1].at<0>(), 2);
    ASSERT_EQ(csv[1].at<1>(), 4);
    ASSERT_EQ(csv[1].at<2>(), 7.5);
    ASSERT_THROW(csv[2].at<2>(), std::range_error);
}

// Пример использования ReadCSV
TEST(basic, init2)
{
    std::vector<Tuple<int32_t, int32_t, double>> lines = ReadCSV<int32_t, int32_t, double>("./gtest/init");
	
    ASSERT_EQ(lines[0].at<0>(), 1);
    ASSERT_EQ(lines[0].at<1>(), 3);
    ASSERT_EQ(lines[0].at<2>(), 5.0);
    ASSERT_EQ(lines[1].at<0>(), 2);
    ASSERT_EQ(lines[1].at<1>(), 4);
    ASSERT_EQ(lines[1].at<2>(), 7.5);
    //ASSERT_THROW(lines[2].at<2>(), std::range_error); //no range test
}

TEST(basic, auto)
{
    csvreader<uint32_t, std::string, std::string, std::string, double> csv{};
    
    ASSERT_TRUE(csv.read_file("./gtest/auto.csv"));
	
    ASSERT_EQ(csv[0].at<0>(), 1997);
    ASSERT_EQ(csv[0].at<1>(), std::string("Ford"));
    ASSERT_EQ(csv[0].at<2>(), std::string("E350"));
    ASSERT_EQ(csv[0].at<3>(), std::string("ac"));
    ASSERT_EQ(csv[0].at<4>(), 3000.05);

    ASSERT_EQ(csv[1].at<0>(), 1999);
    ASSERT_EQ(csv[1].at<1>(), std::string("Chevy"));
    ASSERT_EQ(csv[1].at<2>(), std::string("Venture"));
    ASSERT_EQ(csv[1].at<3>(), std::string("\"\""));
    ASSERT_EQ(csv[1].at<4>(), 4900.01);

    ASSERT_EQ(csv[2].at<0>(), 1996);
    ASSERT_EQ(csv[2].at<1>(), std::string("Jeep"));
    ASSERT_EQ(csv[2].at<2>(), std::string("WRANGLER"));
    ASSERT_EQ(csv[2].at<3>(), std::string("roof"));
    ASSERT_EQ(csv[2].at<4>(), 4799.00);

    ASSERT_THROW(csv[3].at<2>(), std::range_error);
}

TEST(basic, empty)
{
    csvreader<uint32_t, std::string, std::string, std::string, double> csv{};
    
    ASSERT_TRUE(csv.read_file("./gtest/empty"));
}

TEST(basic, bad_line)
{
    csvreader<int32_t, int32_t, double> csv{};
    ASSERT_FALSE(csv.read_file("./gtest/bad_line"));
}

TEST(basic, invalid_pattern)
{
    csvreader<int32_t, int32_t, double> csv{};
    ASSERT_FALSE(csv.read_file("./gtest/auto.csv"));
}
