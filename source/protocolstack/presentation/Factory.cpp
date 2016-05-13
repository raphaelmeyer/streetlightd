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

class Null :
    public Presentation
{
public:
  Null() :
    Presentation{null::encode, null::decode}
  {
  }
};

class Binary :
    public Presentation
{
public:
  Binary() :
    Presentation{binary::encode, binary::decode}
  {
  }
};

class KeyValue :
    public Presentation
{
public:
  KeyValue() :
    Presentation{keyvalue::encode, keyvalue::decode}
  {
  }
};

class Json :
    public Presentation
{
public:
  Json() :
    Presentation{json::encode, json::decode}
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
