/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../propertyNames.h"

#include <gtest/gtest.h>

TEST(message_propertyNames_Test, throws_error_for_unknown_property)
{
  ASSERT_THROW(message::propertyName(message::Property(-1)), std::invalid_argument);
}

TEST(message_propertyNames_Test, has_a_name_for_brightness)
{
  ASSERT_EQ("brightness", message::propertyName(message::Property::Brightness));
}

TEST(message_propertyNames_Test, has_a_name_for_moisture)
{
  ASSERT_EQ("moisture", message::propertyName(message::Property::Moisture));
}

TEST(message_propertyNames_Test, has_a_name_for_info)
{
  ASSERT_EQ("info", message::propertyName(message::Property::Info));
}

TEST(message_propertyNames_Test, has_a_name_for_luminosity)
{
  ASSERT_EQ("luminosity", message::propertyName(message::Property::Luminosity));
}

TEST(message_propertyNames_Test, has_a_name_for_warning)
{
  ASSERT_EQ("warning", message::propertyName(message::Property::Warning));
}
