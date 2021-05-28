// Copyright 2021 MIX-1 <danilonil1@yandex.ru>

#ifndef TEMPLATE_STATSENDER_H
#define TEMPLATE_STATSENDER_H
#include "header.hpp"
#include "Log.h"
#include <fstream>
#include <string_view>

class StatSender {
 public:

  void OnLoaded(const std::vector<Item>& new_items);

  void Skip(const Item& item);

 private:
  void AsyncSend(const std::vector<Item>& items, std::string_view path);

  std::ofstream fstr{"network", std::ios::binary};
};
#endif  // TEMPLATE_STATSENDER_H
