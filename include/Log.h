// Copyright 2021 MIX-1 <danilonil1@yandex.ru>

#ifndef TEMPLATE_LOG_H
#define TEMPLATE_LOG_H
#include "header.hpp"

class Log {
 public:
  static Log& GetInstance();

  void Setting(const bool& level);

  void Write(std::string_view message) const;

  void WriteDebug(std::string_view message) const;

 private:
  Log() = default;
  Log( const Log&) = delete;
  Log& operator=( Log& ) = delete;

  bool level_{};
  mutable std::ostream* out_{};
};

struct Item {
  std::string id;
  std::string name;
  float score = 0;
};
#endif  // TEMPLATE_LOG_H
