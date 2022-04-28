//
// Copyright (c) 2022 David Holmes (dholmes at dholmes dot us)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <game_ui.hpp>

#include <ftxui/component/event.hpp>

#define CATCH_CONFIG_NO_WINDOWS_SEH
#include <catch2/catch.hpp>

// Special prototype that injects events for automation
namespace galaxy {
void run_game(std::vector<ftxui::Event> events);
}  // namespace galaxy

TEST_CASE("Can exit title screen", "[ui]")
{
    galaxy::run_game({ftxui::Event::End, ftxui::Event::Return});
    REQUIRE(true);  // If we get here, the test passed
}
