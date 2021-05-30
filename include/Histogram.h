// Copyright 2021 MIX-1 <danilonil1@yandex.ru>

#ifndef TEMPLATE_HISTOGRAM_H
#define TEMPLATE_HISTOGRAM_H
class Histogram{
 public:
  static Histogram& GetInstance();

  [[nodiscard]] int GetNumSkip() const;

  [[nodiscard]] float GetAvg() const;

  void SetAvg(const float& avg_);

  void PlusNumSkip();

  void NewLap();
 private:
  Histogram() = default;
  Histogram( const Histogram&) = delete;
  Histogram& operator=( Histogram& ) = delete;

  int num_skip = 0;
  float avg = 0;
};
#endif  // TEMPLATE_HISTOGRAM_H
