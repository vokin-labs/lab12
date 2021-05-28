// Copyright 2021 MIX-1 <danilonil1@yandex.ru>

#include "PageContainer.h"
void PageContainer::Load(std::istream& io, const float& threshold) {
  std::vector<std::string> raw_data;

  while (!io.eof()) {
    std::string line;
    std::getline(io, line, '\n');
    raw_data.push_back(std::move(line));
  }

  if (raw_data.size() < kMinLines) {
    throw std::runtime_error("too small input stream");
  }

  memory_counter_->OnRawDataLoad(raw_data_, raw_data);
  raw_data_ = std::move(raw_data);

  std::vector<Item> data;
  std::set<std::string> ids;
  for (const auto& line : raw_data_) {
    std::stringstream stream(line);

    Item item;
    stream >> item.id >> item.name >> item.score;

    if (auto&& [_, inserted] = ids.insert(item.id); !inserted) {
      throw std::runtime_error("already seen");
    }

    if (item.score > threshold) {
      data.push_back(std::move(item));
    } else {
      stat_sender_.Skip(item);
    }
  }

  if (data.size() < kMinLines) {
    throw std::runtime_error("oops");
  }

  memory_counter_->OnDataLoad(data_, data);
  stat_sender_.OnLoaded(data);
  data_ = std::move(data);
}

const Item& PageContainer::ByIndex(const size_t& i) const {
  return data_[i];
}

const Item& PageContainer::ById(const string& id) const {
  auto it = std::find_if(std::begin(data_), std::end(data_),
                         [&id](const auto& i) { return id == i.id; });
  return *it;
}
void PageContainer::Reload(const float& threshold) {
  std::vector<Item> data;
  std::set<std::string> ids;
  for (const auto& line : raw_data_) {
    std::stringstream stream(line);

    Item item;
    stream >> item.id >> item.name >> item.score;

    if (auto&& [_, inserted] = ids.insert(item.id); !inserted) {
      throw std::runtime_error("already seen");
    }

    if (item.score > threshold) {
      data.push_back(std::move(item));
    } else {
      stat_sender_.Skip(item);
    }
  }

  if (data.size() < kMinLines) {
    throw std::runtime_error("oops");
  }

  memory_counter_->OnDataLoad(data_, data);
  stat_sender_.OnLoaded(data);
  data_ = std::move(data);
}
size_t PageContainer::GetDataSize() const{
  return data_.size();
}
void PageContainer::PrintTable() const {
  std::cout << "|\tid\t |\t\tname\t\t|\tscore\t|\n";
  std::cout << "_________________________________________\n";
  for (size_t i = 0; i < GetDataSize(); ++i) {
    const auto& item = ByIndex(i);
    std::cout << "|   " << item.id << "\t |\t\t" << item.name << "\t\t|\t" << item.score << "\t\t|" << std::endl;
    const auto& item2 = ById(std::to_string(i));
    std::cout << "|   " << item2.id << "\t |\t\t" << item2.name << "\t\t|\t" << item2.score << "\t\t|" << std::endl;
  }
}
