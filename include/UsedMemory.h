// Copyright 2021 MIX-1 <danilonil1@yandex.ru>

#ifndef TEMPLATE_USEDMEMORY_H
#define TEMPLATE_USEDMEMORY_H
#include "header.hpp"
#include "Log.h"

class UsedMemory {
 public:

  void OnDataLoad(const std::vector<Item>& old_items,
                  const std::vector<Item>& new_items);

  void OnRawDataLoad(const std::vector<std::string>& old_items,
                     const std::vector<std::string>& new_items);

  [[nodiscard]] size_t Used() const;

 private:
  size_t used_ = 0;
};
#endif  // TEMPLATE_USEDMEMORY_H
