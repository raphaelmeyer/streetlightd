/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef FACTORY_H
#define FACTORY_H

#include <string>
#include <map>
#include <set>
#include <stdexcept>
#include <functional>
#include <algorithm>

template<class T>
class Factory
{
public:
  typedef std::function<T()> Worker;

  virtual ~Factory() = default;

  void add(const std::string &product, Worker worker)
  {
    this->worker[product] = worker;
  }

  virtual std::set<std::string> workers() const
  {
    std::set<std::string> result{};
    std::transform(worker.begin(), worker.end(), std::inserter(result, result.end()), [](const auto &pair){return pair.first;});
    return result;
  }

  virtual T produce(const std::string &product) const
  {
    const auto pos = worker.find(product);
    if (pos == worker.end()) {
      throw std::invalid_argument("no worker for product: " + product);
    }
    return pos->second();
  }

private:
  std::map<std::string, Worker> worker;

};

#endif
