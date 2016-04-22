/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../Printer.h"
#include "../DebugFormat.h"
#include "../Value.h"
#include "../Property.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <functional>

class message_DebugFormat_Test :
    public testing::Test
{
public:
  std::stringstream output{};
  message::Printer::PropertyNameGetter propertyGetter{[](message::Property){return "name";}};
  message::DebugFormat testee{output, propertyGetter};

};

TEST_F(message_DebugFormat_Test, uses_value_from_propertyGetter_to_write_key)
{
  testee.writeKey(message::Property::Info);

  ASSERT_EQ("name", output.str());
}

TEST_F(message_DebugFormat_Test, writes_correct_key_value_separator)
{
  testee.writeKeyValueSeparator();

  ASSERT_EQ("=", output.str());
}

TEST_F(message_DebugFormat_Test, writes_double_value_correct)
{
  testee.writeValue(0.3);

  ASSERT_EQ("\"0.300000\"", output.str());
}

TEST_F(message_DebugFormat_Test, writes_string_value_correct)
{
  testee.writeValue("hi");

  ASSERT_EQ("\"hi\"", output.str());
}

TEST_F(message_DebugFormat_Test, does_not_write_separator_the_first_time)
{
  testee.writeSeparator(true);

  ASSERT_EQ("", output.str());
}

TEST_F(message_DebugFormat_Test, writes_correct_separator_later_times)
{
  testee.writeSeparator(false);

  ASSERT_EQ(" ", output.str());
}
