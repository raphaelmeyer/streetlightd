/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../CommandLineParser.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <set>
#include <string>

class CommandLineParser_Test:
    public testing::Test
{
public:
  std::stringstream output{};
  CommandLineParserImplementation testee{output};

};

TEST_F(CommandLineParser_Test, show_help_when_requested)
{
  const std::string ExpectedHelp {
    "usage: \n"
    "-t, --test  \n"
  };
  Poco::Util::OptionSet options;
  options.addOption(Poco::Util::Option{"test", "t", "", false});
  testee.parse({}, options);

  testee.printHelp();

  ASSERT_EQ(ExpectedHelp, output.str());
}

TEST_F(CommandLineParser_Test, is_not_valid_when_not_provided_all_arguments)
{
  Poco::Util::OptionSet options;
  options.addOption(Poco::Util::Option{"test", "t", "", true});

  testee.parse({}, options);

  ASSERT_FALSE(testee.isValid());
}

TEST_F(CommandLineParser_Test, is_not_valid_when_missing_required_arguments)
{
  Poco::Util::OptionSet options;
  options.addOption(Poco::Util::Option{"test", "t", "", true});

  testee.parse({}, options);

  ASSERT_FALSE(testee.isValid());
}

TEST_F(CommandLineParser_Test, is_not_valid_when_missing_option_argument)
{
  Poco::Util::OptionSet options;
  options.addOption(Poco::Util::Option{"test", "t", "", true}.argument("value"));

  testee.parse({"--test"}, options);

  ASSERT_FALSE(testee.isValid());
}

TEST_F(CommandLineParser_Test, is_not_valid_if_unknown_option_is_provided)
{
  Poco::Util::OptionSet options;
  options.addOption(Poco::Util::Option{"test", "t", "", false});

  testee.parse({"--unknown"}, options);

  ASSERT_FALSE(testee.isValid());
}

TEST_F(CommandLineParser_Test, return_the_specified_value)
{
  Poco::Util::OptionSet options;
  options.addOption(Poco::Util::Option{"test", "t", "", true}.argument("value"));

  testee.parse({"--test=theValue"}, options);

  ASSERT_TRUE(testee.isValid());
  ASSERT_EQ("theValue", testee.value("test"));
}

TEST_F(CommandLineParser_Test, can_not_get_value_if_value_does_not_exists)
{
  Poco::Util::OptionSet options;

  testee.parse({}, options);

  ASSERT_THROW(testee.value("test"), std::invalid_argument);
}

TEST_F(CommandLineParser_Test, value_with_default_returns_default_if_value_does_not_exists)
{
  Poco::Util::OptionSet options;

  testee.parse({}, options);

  ASSERT_EQ("default", testee.value("test", "default"));
}

TEST_F(CommandLineParser_Test, value_with_default_returns_value_if_value_exists)
{
  Poco::Util::OptionSet options;
  options.addOption(Poco::Util::Option{"test", "t", "", true}.argument("value"));

  testee.parse({"--test=hello"}, options);

  ASSERT_EQ("hello", testee.value("test", "default"));
}

TEST_F(CommandLineParser_Test, can_check_if_flag_is_set_or_not)
{
  Poco::Util::OptionSet options;
  options.addOption(Poco::Util::Option{"hello", ""});

  testee.parse({"--hello"}, options);

  ASSERT_TRUE(testee.contains("hello"));
  ASSERT_FALSE(testee.contains("world"));
}
