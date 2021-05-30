// Copyright 2021 MIX-1 <danilonil1@yandex.ru>

#include "UsedMemory.h"

void UsedMemory::OnDataLoad(const std::vector<Item>& old_items,
                            const std::vector<Item>& new_items) {
  Log::GetInstance().WriteDebug("UsedMemory::OnDataLoad");
  for (const auto& item : new_items) {
    used_ += item.id.capacity();
    used_ += item.name.capacity();
    used_ += sizeof(item.score);
  }

  for (const auto& item : old_items) {
    used_ -= item.id.capacity();
    used_ -= item.name.capacity();
    used_ -= sizeof(item.score);
  }

  Log::GetInstance().Write("UsedMemory::OnDataLoad: new size = " +
                           std::to_string(used_));
}

void UsedMemory::OnRawDataLoad(const std::vector<std::string>& old_items,
                               const std::vector<std::string>& new_items) {
  Log::GetInstance().WriteDebug("UsedMemory::OnRawDataLoads");
  for (const auto& item : new_items) {
    used_ += item.capacity();
  }
  for (const auto& item : old_items) {
    used_ -= item.capacity();
  }
  Log::GetInstance().Write("UsedMemory::OnDataLoad: new size = " +
                           std::to_string(used_));
}

size_t UsedMemory::Used() const {
  return used_;
}
