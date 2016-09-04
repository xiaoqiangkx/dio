//
// Created by parallels on 9/4/16.
//

#define BOOST_TEST_MODULE My_Test
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(first_test)
{
    int i = 1;
    BOOST_TEST(i);
    BOOST_TEST(i == 1);
}

