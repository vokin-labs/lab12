// Copyright 2021 MIX-1 <danilonil1@yandex.ru>

#include "PageContainer.h"

const Item& PageContainer::ByIndex(const size_t& i) const {
  return data_[i];
}

const Item& PageContainer::ById(const string& id) const {
  auto it = std::find_if(std::begin(data_), std::end(data_),
                         [&id](const auto& i) { return id == i.id; });
  return *it;
}

void PageContainer::PrintTable() const {
  std::cout << "|\tid\t |\t\tname\t\t|\tscore\t|\n";
  string separator = "_________________________________________\n";
  std::cout << separator;
  for (size_t i = 0; i < data_.size(); ++i) {
    const auto& item = ByIndex(i);
    std::cout << "|   " << item.id << "\t |\t\t" <<
        item.name << "\t\t|\t" << item.score << "\t\t|" << std::endl;
    const auto& item2 = ById(std::to_string(i));
    std::cout << "|   " << item2.id << "\t |\t\t" <<
        item2.name << "\t\t|\t" << item2.score << "\t\t|" << std::endl;
    std::cout << separator;
  }
}

void PageContainer::RawLoad(std::istream& file) {
  std::vector<std::string> raw_data;

  if(!file) throw std::runtime_error("file don`t open");

  if(file.peek() == EOF)  throw std::runtime_error("file is empty");

  Log::GetInstance().WriteDebug("file open");

  while (!file.eof()) {
    std::string line;
    std::getline(file, line, '\n');
    if(IsCorrect(line)) raw_data.push_back(std::move(line));
  }

  if (raw_data.size() < kMinLines) {
    throw std::runtime_error("too small input stream");
  }

  memory_counter_->OnRawDataLoad(raw_data_, raw_data);
  raw_data_ = std::move(raw_data);
}

void PageContainer::DataLoad(const float& threshold) {
  Histogram::GetInstance().NewLap();
  std::vector<Item> data;
  std::set<std::string> ids;
  float sum = 0;
  size_t counter = 0;
  for (const auto& line : raw_data_) {
    std::stringstream stream(line);

    Item item;
    stream >> item.id >> item.name >> item.score;

    if (auto&& [_, inserted] = ids.insert(item.id); !inserted) {
      throw std::runtime_error("already seen");
    }

    if (item.score > threshold) {
      data.push_back(std::move(item));
      sum += item.score;
      ++counter;
    } else {
      stat_sender_->Skip(item);
      Histogram::GetInstance().PlusNumSkip();
    }
  }
  Histogram::GetInstance().SetAvg(sum/counter);
  if (data.size() < kMinLines) {
    throw std::runtime_error("correct items less then const");
  }

  memory_counter_->OnDataLoad(data_, data);
  stat_sender_->OnLoaded(data);
  data_ = std::move(data);
}

bool PageContainer::IsCorrect(string& line) {
  size_t counter = 0;
  bool status = true;
  for(auto& ch : line){
    if(ch == ' ') {
      ++counter;
    } else if(counter == 0) {
      status = (ch >= '0' && ch <= '9') && status;
    } else if(counter == 1) {
      status = ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) && status;
    } else if(counter == 2) {
      status = (ch >= '0' && ch <= '9') && status;
    }
  }
  status = status && (counter == 2);
  return status;
}
size_t PageContainer::GetRawDataSize() const { return raw_data_.size(); }
size_t PageContainer::GetDataSize() const { return data_.size(); }
PageContainer::~PageContainer() {
  delete memory_counter_;
  delete stat_sender_;
}
