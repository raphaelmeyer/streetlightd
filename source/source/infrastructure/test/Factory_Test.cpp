/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../Factory.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>


class Factory_Test:
    public testing::Test
{
public:
  Factory<int> testee{};

};

TEST_F(Factory_Test, there_are_no_worker_by_default)
{
  ASSERT_EQ(std::set<std::string>{}, testee.workers());
}

TEST_F(Factory_Test, throw_error_when_no_worker_for_product_is_registered)
{
  ASSERT_THROW(testee.produce("quaxli"), std::invalid_argument);
}

TEST_F(Factory_Test, can_produce_produkt_with_registered_worker)
{
  testee.add("42", []{return 42;});

  const auto product = testee.produce("42");

  ASSERT_EQ(42, product);
}

TEST_F(Factory_Test, can_produce_produkt_with_multiple_registered_worker)
{
  testee.add("42", []{return 42;});
  testee.add("57", []{return 57;});

  ASSERT_EQ(42, testee.produce("42"));
  ASSERT_EQ(57, testee.produce("57"));
}
