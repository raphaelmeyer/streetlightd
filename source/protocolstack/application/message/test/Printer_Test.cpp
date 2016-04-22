/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../Printer.h"
#include "../Value.h"
#include "../Property.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <functional>

class message_Printer_Test :
    public testing::Test
{
public:
  std::stringstream output{};
  message::Printer::PropertyNameGetter propertyGetter{[](message::Property){return "name";}};
  message::Printer testee{output, propertyGetter};

};

TEST_F(message_Printer_Test, prints_valid_double_value)
{
  const message::Value<double> value{0.42};

  testee.visit(message::Property::Info, value);

  ASSERT_EQ("name=\"0.420000\"", output.str());
}

TEST_F(message_Printer_Test, does_not_print_invalid_double_value)
{
  const message::Value<double> value{};

  testee.visit(message::Property::Info, value);

  ASSERT_EQ("", output.str());
}

TEST_F(message_Printer_Test, prints_valid_string_value)
{
  const message::Value<std::string> value{"test"};

  testee.visit(message::Property::Info, value);

  ASSERT_EQ("name=\"test\"", output.str());
}

TEST_F(message_Printer_Test, adds_spaces_between_values)
{
  const message::Value<std::string> value{"test"};

  testee.visit(message::Property::Info, value);
  testee.visit(message::Property::Info, value);
  testee.visit(message::Property::Info, value);

  ASSERT_EQ("name=\"test\" name=\"test\" name=\"test\"", output.str());
}

TEST_F(message_Printer_Test, does_not_add_spaces_for_invalid_values)
{
  const message::Value<std::string> value{};

  testee.visit(message::Property::Info, value);
  testee.visit(message::Property::Info, value);
  testee.visit(message::Property::Info, value);

  ASSERT_EQ("", output.str());
}
