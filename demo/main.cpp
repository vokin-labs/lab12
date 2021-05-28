// Copyright 2021 MIX-1 <danilonil1@yandex.ru>

#include <header.hpp>
#include "Log.h"
#include "UsedMemory.h"
#include "PageContainer.h"
#include <boost/program_options.hpp>

namespace po = boost::program_options;

const char error_mes[] = "**********BAD SYNTAX**********\n"
                         "Look to --help or -h";

void CreatePo(po::options_description& desc,
               po::variables_map& vm,
               const int& argc, const char** argv){
  desc.add_options()
      ("help,h", "Help screen\n")

      ("log_debug,l", "Logger status (Release(if OFF) or Debug(if ON))\n")

      ("input,i", po::value<string>()->default_value("data.txt"),
       "Name of input file\n")

      ("threshold,t", po::value<int>()->default_value(1),
       "Enter number\n");
  store(parse_command_line(argc, argv, desc), vm);
  notify(vm);
}

int main(const int argc, const char* argv[]) {
  try{
    po::options_description desc{"Options"};
    po::variables_map vm;
    CreatePo(desc, vm, argc, argv);
    if(vm.count("help")){
      cout << desc << endl;
    } else if(argc > 1){
      Log::GetInstance().Setting(vm.count("log_status") == 1);
      UsedMemory used_memory;

      PageContainer page(&used_memory);
      std::ifstream in(vm["input"].as<string>());
      page.Load(in, vm["threshold"].as<int>());

      Log::GetInstance().Write(std::to_string(used_memory.Used()));

      page.PrintTable();

      page.Reload(vm["threshold"].as<int>());
      Log::GetInstance().Write(std::to_string(used_memory.Used()));
    } else {
      throw po::error(error_mes);
    }
  } catch (const po::error &ex) {
    cout << error_mes << "\n";
  }
}