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
  EXPECT_CALL(format, incomingHeader()).Times(1);

  testee.incomingHeader();
}

TEST_F(message_Printer_Test, prints_footer_for_incoming)
{
  EXPECT_CALL(format, footer()).Times(1);

  testee.incomingFooter();
}

TEST_F(message_Printer_Test, prints_header_for_outgoing)
{
  EXPECT_CALL(format, outgoingHeader()).Times(1);

  testee.outgoingHeader();
}

TEST_F(message_Printer_Test, prints_footer_for_outgoing)
{
  EXPECT_CALL(format, footer()).Times(1);

  testee.outgoingFooter();
}

TEST_F(message_Printer_Test, prints_valid_double_value)
{
  const message::Value<double> value{0.42};

  EXPECT_CALL(format, value(testing::_, testing::_, 0.42)).Times(1);

  testee.property(message::Property::Info, value);
}

TEST_F(message_Printer_Test, prints_valid_string_value)
{
  const message::Value<std::string> value{"test"};

  EXPECT_CALL(format, value(testing::_, testing::_, "test")).Times(1);

  testee.property(message::Property::Info, value);
}

TEST_F(message_Printer_Test, does_not_print_invalid_value)
{
  const message::Value<double> value{};

  EXPECT_CALL(format, value(testing::_, testing::_, testing::An<double>())).Times(0);

  testee.property(message::Property::Info, value);
}

TEST_F(message_Printer_Test, uses_the_provided_key_when_writeing_the_key)
{
  const message::Value<double> value{0.42};

  EXPECT_CALL(format, value(testing::_, message::Property::Info, testing::An<double>())).Times(1);
  EXPECT_CALL(format, value(testing::_, message::Property::Brightness, testing::An<double>())).Times(1);
  EXPECT_CALL(format, value(testing::_, message::Property::Warning, testing::An<double>())).Times(0);

  testee.property(message::Property::Info, value);
  testee.property(message::Property::Brightness, value);
}

TEST_F(message_Printer_Test, first_is_the_first_time_true)
{
  const message::Value<double> value{0};

  EXPECT_CALL(format, value(true, message::Property::Info, testing::An<double>())).Times(1);
  EXPECT_CALL(format, value(false, message::Property::Info, testing::An<double>())).Times(0);

  testee.property(message::Property::Info, value);
}

TEST_F(message_Printer_Test, calls_the_separator_the_later_times_with_false)
{
  const message::Value<double> value{0};

  EXPECT_CALL(format, value(true, message::Property::Info, testing::An<double>())).Times(1);
  EXPECT_CALL(format, value(false, message::Property::Info, testing::An<double>())).Times(2);

  testee.property(message::Property::Info, value);
  testee.property(message::Property::Info, value);
  testee.property(message::Property::Info, value);
}
