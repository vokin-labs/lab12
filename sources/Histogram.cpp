// Copyright 2021 MIX-1 <danilonil1@yandex.ru>

#include "Histogram.h"
int Histogram::GetNumSkip() const {
  return num_skip;
}
Histogram& Histogram::GetInstance() {
  static Histogram instance;
  return instance;
}
void Histogram::SetAvg(const float& avg_) {
  avg = avg_;
}
void Histogram::PlusNumSkip() {
  ++num_skip;
}
void Histogram::NewLap() {
  num_skip = 0;
}
float Histogram::GetAvg() const {
  return avg;
}
