/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../Printer.h"
#include "PrintFormat_Mock.h"
#include "../Value.h"
#include "../Property.h"
#include "../Incoming.h"
#include "../Outgoing.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <functional>

class message_Printer_Test :
    public testing::Test
{
public:
  testing::NiceMock<PrintFormatMock> format;
  message::Printer testee{format};

};

TEST_F(message_Printer_Test, prints_header_for_incoming)
{
  EXPECT_CALL(format, writeIncomingHeader()).Times(1);

  testee.incomingHeader();
}

TEST_F(message_Printer_Test, prints_footer_for_incoming)
{
  EXPECT_CALL(format, writeFooter()).Times(1);

  testee.incomingFooter();
}

TEST_F(message_Printer_Test, prints_header_for_outgoing)
{
  EXPECT_CALL(format, writeOutgoingHeader()).Times(1);

  testee.outgoingHeader();
}

TEST_F(message_Printer_Test, prints_footer_for_outgoing)
{
  EXPECT_CALL(format, writeFooter()).Times(1);

  testee.outgoingFooter();
}

TEST_F(message_Printer_Test, prints_valid_double_value)
{
  const message::Value<double> value{0.42};
  EXPECT_CALL(format, writeValue(0.42)).Times(1);

  testee.visit(message::Property::Info, value);
}

TEST_F(message_Printer_Test, prints_valid_string_value)
{
  const message::Value<std::string> value{"test"};
  EXPECT_CALL(format, writeValue("test")).Times(1);

  testee.visit(message::Property::Info, value);
}

TEST_F(message_Printer_Test, does_not_print_invalid_value)
{
  const message::Value<double> value{};
  EXPECT_CALL(format, writeKey(testing::_)).Times(0);

  testee.visit(message::Property::Info, value);
}

TEST_F(message_Printer_Test, uses_the_provided_key_when_writeing_the_key)
{
  const message::Value<double> value{0.42};
  EXPECT_CALL(format, writeKey(message::Property::Info)).Times(1);
  EXPECT_CALL(format, writeKey(message::Property::Brightness)).Times(1);
  EXPECT_CALL(format, writeKey(message::Property::Warning)).Times(0);

  testee.visit(message::Property::Info, value);
  testee.visit(message::Property::Brightness, value);
}

TEST_F(message_Printer_Test, calls_the_separator_the_first_time_with_true)
{
  const message::Value<double> value{0};
  EXPECT_CALL(format, writeSeparator(true)).Times(1);
  EXPECT_CALL(format, writeSeparator(false)).Times(0);

  testee.visit(message::Property::Info, value);
}

TEST_F(message_Printer_Test, calls_the_separator_the_later_times_with_false)
{
  const message::Value<double> value{0};
  EXPECT_CALL(format, writeSeparator(true)).Times(1);
  EXPECT_CALL(format, writeSeparator(false)).Times(2);

  testee.visit(message::Property::Info, value);
  testee.visit(message::Property::Info, value);
  testee.visit(message::Property::Info, value);
}

TEST_F(message_Printer_Test, calls_all_functions_to_print_full_property)
{
  const message::Value<double> value{1};

  EXPECT_CALL(format, writeSeparator(testing::_)).Times(1);
  EXPECT_CALL(format, writeKey(testing::_)).Times(1);
  EXPECT_CALL(format, writeKeyValueSeparator()).Times(1);
  EXPECT_CALL(format, writeValue(1)).Times(1);

  testee.visit(message::Property::Info, value);
}
