// Copyright 2021 MIX-1 <danilonil1@yandex.ru>

#include "StatSender.h"
void StatSender::OnLoaded(const std::vector<Item>& new_items) {
  Log::GetInstance().WriteDebug("StatSender::OnDataLoad");

  AsyncSend(new_items, "/items/loaded");
}

void StatSender::Skip(const Item& item) {
  AsyncSend({item}, "/items/skiped");
}

void StatSender::AsyncSend(const std::vector<Item>& items,
                           std::string_view path) {
  Log::GetInstance().Write(path);
  Log::GetInstance().Write("send stat " + std::to_string(items.size()));

  for (const auto& item : items) {
    Log::GetInstance().WriteDebug("send: " + item.id);
    // ... some code
    fstr << item.id << item.name << item.score;
    fstr.flush();
  }
}
