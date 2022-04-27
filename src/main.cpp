//
// Copyright (c) 2022 David Holmes (dholmes at dholmes dot us)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "game_ui.hpp"

#include <docopt/docopt.h>
#include <fmt/format.h>

#include <map>
#include <stdexcept>
#include <string>

// This file will be generated automatically when you run the CMake
// configuration step. It creates a namespace called `galaxy`. You can modify
// the source template at `configured_files/config.hpp.in`.
#include <internal_use_only/config.hpp>

int main(int argc, const char** argv)
{
    try {
        static constexpr auto USAGE{
            R"(

    Usage:
          galaxy
          galaxy (-h | --help)
          galaxy --version
 Options:
          -h --help     Show this screen.
          --version     Show version.
)"};

        std::map<std::string, docopt::value> args{
            docopt::docopt(USAGE, {std::next(argv), std::next(argv, argc)},
                           true,  // show help if requested
                           fmt::format("{} {}", galaxy::cmake::project_name,
                                       galaxy::cmake::project_version))};

        galaxy::run_game();
    }
    catch (const std::exception& e) {
        fmt::print("Unhandled exception in main: {}", e.what());
    }
}
