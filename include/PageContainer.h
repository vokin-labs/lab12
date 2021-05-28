// Copyright 2021 MIX-1 <danilonil1@yandex.ru>

#ifndef TEMPLATE_PAGECONTAINER_H
#define TEMPLATE_PAGECONTAINER_H
#include "header.hpp"
#include "Log.h"
#include "StatSender.h"
#include "UsedMemory.h"
#include <set>
#include <sstream>
#include <algorithm>

constexpr size_t kMinLines = 10;

class PageContainer {
 public:
  void Load(std::istream& io, const float& threshold);

  const Item& ByIndex(const size_t& i) const;

  const Item& ById(const std::string& id) const;

  void Reload(const float& threshold);

  size_t GetDataSize() const;

  void PrintTable() const;

  PageContainer(UsedMemory* memory_counter)
      : memory_counter_(memory_counter) {}

 private:
  UsedMemory* memory_counter_;
  StatSender stat_sender_;
  std::vector<Item> data_;
  std::vector<std::string> raw_data_;
};
#endif  // TEMPLATE_PAGECONTAINER_H
