//
// Copyright (c) 2022 David Holmes (dholmes at dholmes dot us)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "game_ui.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

#include <spdlog/spdlog.h>

#include <functional>

namespace galaxy {

using namespace ftxui;

struct title_callbacks {
    std::function<void()> new_game;
    std::function<void()> load_game;
    std::function<void()> quit;
};

Component title_screen(title_callbacks callbacks)
{
    constexpr const int menu_width{20};
    constexpr const int menu_height{5};
    static const std::vector<std::string> menu_entries{"New Game", "Load Game",
                                                       "Quit"};
    class impl : public ftxui::ComponentBase {
       public:
        explicit impl(title_callbacks callbacks)
            : callbacks_{std::move(callbacks)}
        {
            auto menu_action{[&] {
                switch (menu_selected_) {
                    case 0:
                        callbacks_.new_game();
                        break;
                    case 1:
                        callbacks_.load_game();
                        break;
                    case 2:
                        callbacks_.quit();
                        break;
                    default:
                        spdlog::info("Clicked Unknown");
                        // TODO: Throw
                        break;
                }
            }};
            menu_option_.on_enter = menu_action;
            Add(menu_);
        }

        ftxui::Element Render() override
        {
            return menu_->Render() | border | center |
                   size(Direction::WIDTH, Constraint::EQUAL, menu_width) |
                   size(Direction::HEIGHT, Constraint::EQUAL, menu_height) |
                   align_right;
        }

       private:
        title_callbacks callbacks_;
        int menu_selected_{0};
        ftxui::MenuOption menu_option_;
        ftxui::Component menu_{
            ftxui::Menu(&menu_entries, &menu_selected_, &menu_option_)};
    };

    return Make<impl>(std::move(callbacks));
}

void run_game(const std::vector<ftxui::Event>& events)
{
    auto screen{ftxui::ScreenInteractive::Fullscreen()};

    title_callbacks callbacks{
        .new_game = [] { spdlog::info("Clicked New Game"); },
        .load_game = [] { spdlog::info("Clicked Load Game"); },
        .quit = screen.ExitLoopClosure()};
    ftxui::Component component{title_screen(std::move(callbacks))};

    // Inject events for test automation
    for (const auto& event : events) {
        screen.PostEvent(event);
    }

    screen.Loop(component);
}

void run_game()
{
    run_game({});
}

}  // namespace galaxy
