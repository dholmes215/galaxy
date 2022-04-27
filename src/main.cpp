#include <docopt/docopt.h>
#include <fmt/format.h>

#include <map>
#include <stdexcept>
#include <string>

// This file will be generated automatically when you run the CMake
// configuration step. It creates a namespace called `galaxy`. You can modify
// the source template at `configured_files/config.hpp.in`.
#include <internal_use_only/config.hpp>

void run() {}

int main(int argc, const char** argv)
{
    try {
        static constexpr auto USAGE =
            R"(

    Usage:
          intro
          intro (-h | --help)
          intro --version
 Options:
          -h --help     Show this screen.
          --version     Show version.
)";

        std::map<std::string, docopt::value> args =
            docopt::docopt(USAGE, {std::next(argv), std::next(argv, argc)},
                           true,  // show help if requested
                           fmt::format("{} {}", galaxy::cmake::project_name,
                                       galaxy::cmake::project_version));

        run();
    }
    catch (const std::exception& e) {
        fmt::print("Unhandled exception in main: {}", e.what());
    }
}
