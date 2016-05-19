/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../EnumOption.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <set>
#include <string>

TEST(EnumOption_Test, has_empty_fields_with_default_constructor)
{
  const cli::EnumOption testee;

  ASSERT_TRUE(testee.longName.empty());
  ASSERT_TRUE(testee.shortName.empty());
  ASSERT_TRUE(testee.values.empty());
}

TEST(EnumOption_Test, can_create_with_values)
{
  const std::set<std::string> expectedValues{"value1", "value2"};

  const cli::EnumOption testee{"hello long", "short", {"value1", "value2"}};

  ASSERT_EQ("hello long", testee.longName);
  ASSERT_EQ("short", testee.shortName);
  ASSERT_EQ(expectedValues, testee.values);
}

TEST(EnumOption_Test, can_convert_to_Poco_Pption_values)
{
  const cli::EnumOption testee{"hello long", "short", {"value1", "value2"}};

  const Poco::Util::Option option = testee.asOption();

  ASSERT_EQ("<hello long>", option.argumentName());
  ASSERT_EQ(true, option.argumentRequired());
  ASSERT_EQ("<hello long>: value1 value2", option.description());
  ASSERT_EQ("hello long", option.fullName());
  ASSERT_EQ(false, option.repeatable());
  ASSERT_EQ(true, option.required());
  ASSERT_EQ("short", option.shortName());
  ASSERT_EQ(true, option.takesArgument());
}

