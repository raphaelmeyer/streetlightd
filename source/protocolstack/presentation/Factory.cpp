/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Factory.h"

#include "Presentation.h"
#include "BinaryParser.h"
#include "BinaryEncoder.h"
#include "JsonParser.h"
#include "JsonEncoder.h"
#include "KeyValueParser.h"
#include "KeyValueEncoder.h"
#include "Null.h"

namespace presentation
{

class Null :
    public Presentation
{
public:
  Null() :
    Presentation{null::encode, new null::Parser()}
  {
  }
};

/**
 * Own binary representation that never should be used.
 */
class Binary :
    public Presentation
{
public:
  Binary() :
    Presentation{binary::encode, new binary::Parser()}
  {
  }
};

/**
 * Own representation of key-value pairs that never should be used.
 */
class KeyValue :
    public Presentation
{
public:
  KeyValue() :
    Presentation{keyvalue::encode, new keyvalue::Parser()}
  {
  }
};

/**
 * Json representation for usage with the cloud.
 */
class Json :
    public Presentation
{
public:
  Json() :
    Presentation{json::encode, new json::Parser()}
  {
  }
};

Factory<Presentation*> factory()
{
  Factory<Presentation*> factory;
  factory.add("none", []{ return new presentation::Null();});
  factory.add("binary", []{ return new Binary();});
  factory.add("key-value", []{ return new KeyValue();});
  factory.add("json", []{ return new Json();});
  return factory;
}

}
