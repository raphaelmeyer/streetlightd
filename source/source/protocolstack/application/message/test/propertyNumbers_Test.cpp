/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../propertyNumbers.h"

#include <gtest/gtest.h>

TEST(message_propertyNumbers_Test, throws_error_for_unknown_property)
{
  ASSERT_THROW(message::propertyNumber(message::Property(-1)), std::invalid_argument);
}

TEST(message_propertyNumbers_Test, has_a_name_for_brightness)
{
  ASSERT_EQ(0, message::propertyNumber(message::Property::Brightness));
}

TEST(message_propertyNumbers_Test, has_a_name_for_moisture)
{
  ASSERT_EQ(4, message::propertyNumber(message::Property::Moisture));
}

TEST(message_propertyNumbers_Test, has_a_name_for_proximity)
{
  ASSERT_EQ(5, message::propertyNumber(message::Property::Proximity));
}

TEST(message_propertyNumbers_Test, has_a_name_for_info)
{
  ASSERT_EQ(1, message::propertyNumber(message::Property::Info));
}

TEST(message_propertyNumbers_Test, has_a_name_for_luminosity)
{
  ASSERT_EQ(2, message::propertyNumber(message::Property::Luminosity));
}

TEST(message_propertyNumbers_Test, has_a_name_for_warning)
{
  ASSERT_EQ(3, message::propertyNumber(message::Property::Warning));
}
