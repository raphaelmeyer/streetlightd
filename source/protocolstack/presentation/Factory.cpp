/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Factory.h"

#include "Presentation.h"
#include "BinaryDecoder.h"
#include "BinaryEncoder.h"
#include "JsonDecoder.h"
#include "JsonEncoder.h"
#include "KeyValueDecoder.h"
#include "KeyValueEncoder.h"
#include "Null.h"

namespace presentation
{

Factory<presentation::EncoderAndDecoder> factory()
{
  Factory<presentation::EncoderAndDecoder> factory;
  factory.add("none", []{ return presentation::EncoderAndDecoder{presentation::null::encode, presentation::null::decode};});
  factory.add("binary", []{ return presentation::EncoderAndDecoder{Binary::encode, Binary::decode};});
  factory.add("key-value", []{ return presentation::EncoderAndDecoder{KeyValue::encode, KeyValue::decode};});
  factory.add("json", []{ return presentation::EncoderAndDecoder{Json::encode, Json::decode};});
  return factory;
}

}
