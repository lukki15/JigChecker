#include <jigchecker/version.h>  // for JIGCHECKER_VERSION

#include <cxxopts.hpp>  // for value, OptionAdder, Options, OptionV...
#include <iostream>     // for operator<<, endl, basic_ostream, cout
#include <memory>       // for shared_ptr, __shared_ptr_access
#include <string>       // for string, operator<<, char_traits

auto main(int argc, char** argv) -> int {
  cxxopts::Options options(*argv, "A program to welcome the world!");

  std::string language;
  std::string name;

  // clang-format off
  options.add_options()
    ("h,help", "Show help")
    ("v,version", "Print the current version number")
    ("n,name", "Name to greet", cxxopts::value(name)->default_value("World"))
    ("l,lang", "Language code to use", cxxopts::value(language)->default_value("en"))
  ;
  // clang-format on

  auto result = options.parse(argc, argv);

  if (result["help"].as<bool>()) {
    std::cout << options.help() << std::endl;
    return 0;
  }

  if (result["version"].as<bool>()) {
    std::cout << "JigChecker, version " << JIGCHECKER_VERSION << std::endl;
    return 0;
  }

  return 0;
}
