// Copyright 2021 MIX-1 <danilonil1@yandex.ru>

#ifndef TEMPLATE_PAGECONTAINER_H
#define TEMPLATE_PAGECONTAINER_H
#include "header.h"
#include "Log.h"
#include "StatSender.h"
#include "UsedMemory.h"
#include "Histogram.h"
#include <set>
#include <sstream>
#include <algorithm>

constexpr size_t kMinLines = 10;

class PageContainer {
 public:
  void RawLoad(std::istream& file);

  [[nodiscard]] const Item& ByIndex(const size_t& i) const;

  [[nodiscard]] const Item& ById(const std::string& id) const;

  [[nodiscard]] size_t GetRawDataSize() const;

  [[nodiscard]] size_t GetDataSize() const;

  void DataLoad(const float& threshold);

  static bool IsCorrect(string& line);

  void PrintTable() const;

  explicit PageContainer(UsedMemory* memory_counter = new UsedMemory(),
                         StatSender* stat_sender = new StatSender())
      : memory_counter_(memory_counter), stat_sender_(stat_sender){}

  ~PageContainer();
 private:
  UsedMemory* memory_counter_;
  StatSender* stat_sender_;
  std::vector<Item> data_;
  std::vector<std::string> raw_data_;
};
#endif  // TEMPLATE_PAGECONTAINER_H
