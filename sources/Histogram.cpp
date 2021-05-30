//
// Created by aleksandr on 29.05.2021.
//

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
