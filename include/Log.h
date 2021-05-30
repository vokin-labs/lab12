// Copyright 2021 MIX-1 <danilonil1@yandex.ru>

#ifndef TEMPLATE_LOG_H
#define TEMPLATE_LOG_H
#include "header.h"

class Log {
 public:
  static Log& GetInstance();

  void Setting(bool level);

  void Write(const std::string_view& message) const;

  void WriteDebug(const std::string_view& message) const;

 private:
  Log(): level_(false), out_(&std::cout){};

  Log( const Log&) = delete;
  Log& operator=( Log& ) = delete;

  bool level_ = false;
  mutable std::ostream* out_;
};

struct Item {
  std::string id;
  std::string name;
  float score = 0;
};
#endif  // TEMPLATE_LOG_H
