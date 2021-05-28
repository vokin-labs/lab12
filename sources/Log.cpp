// Copyright 2021 MIX-1 <danilonil1@yandex.ru>

#include "Log.h"
void Log::Write(std::string_view message) const {
  *out_ << "[info] " << message << std::endl;
}
void Log::WriteDebug(std::string_view message) const {
  if (level_) *out_ << "[debug] " << message << std::endl;
}
Log& Log::GetInstance() {
  static Log  instance;
  return instance;
}
void Log::Setting(const bool& level) {
  level_ = level;
  out_ = &std::cout;
}
