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
#include "../propertyNames.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <functional>

class message_DebugFormat_Test :
    public testing::Test
{
public:
  std::stringstream output{};
  message::DebugFormat testee{output};

};

TEST_F(message_DebugFormat_Test, writes_string_value)
{
  testee.value(true, message::Property::Info, "hi");

  ASSERT_EQ("info=\"hi\"", output.str());
}

TEST_F(message_DebugFormat_Test, writes_double_value)
{
  testee.value(true, message::Property::Warning, 0.3);

  ASSERT_EQ("warning=\"0.3\"", output.str());
}

TEST_F(message_DebugFormat_Test, adds_separator_for_second_and_later_values)
{
  testee.value(false, message::Property::Moisture, "hi");

  ASSERT_EQ(" moisture=\"hi\"", output.str());
}
