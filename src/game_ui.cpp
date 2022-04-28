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

class title_screen : public ftxui::ComponentBase {
   public:
    struct menu_callbacks {
        std::function<void()> new_game;
        std::function<void()> load_game;
        std::function<void()> quit;
    };

    explicit title_screen(menu_callbacks callbacks)
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
               size(Direction::WIDTH, Constraint::EQUAL, menu_width_) |
               size(Direction::HEIGHT, Constraint::EQUAL, menu_height_) |
               align_right;
    }

   private:
    static constexpr const int menu_width_{20};
    static constexpr const int menu_height_{5};

    menu_callbacks callbacks_;

    static const std::vector<std::string>* menu_entries()
    {
        static const std::vector<std::string> out{"New Game", "Load Game",
                                                  "Quit"};
        return &out;
    }

    int menu_selected_{0};
    ftxui::MenuOption menu_option_;
    ftxui::Component menu_{
        ftxui::Menu(menu_entries(), &menu_selected_, &menu_option_)};
};

void run_game(const std::vector<ftxui::Event>& events)
{
    auto screen{ftxui::ScreenInteractive::Fullscreen()};

    title_screen::menu_callbacks callbacks{
        .new_game = [] { spdlog::info("Clicked New Game"); },
        .load_game = [] { spdlog::info("Clicked Load Game"); },
        .quit = screen.ExitLoopClosure()};
    ftxui::Component component{
        std::make_shared<title_screen>(std::move(callbacks))};

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
