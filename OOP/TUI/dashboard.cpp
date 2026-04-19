#include <string>
#include <vector>

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

using namespace ftxui;
using namespace std;

int main()
{
    vector<string> options = 
    {
        "1. Deposit",
        "2. Withdraw",
        "3. Transfer",
        "4. Logout",
    };
    vector<string> profile = 
    {
        "Username    : Toffeek",
        "Balance     : Tk67.00",
        "Account no  : Toffeek",
    };

    vector<string> recent_transactions = 
    {
        "Deposit Tk1000",
        "Withdraw Tk500",
        "Transfer Tk5000 to Sadnan",
        "Withdraw Tk1000",
        "Deposit Tk1000",
        "Withdraw Tk500",
        "Transfer Tk5000 to Sadnan",
        "Withdraw Tk1000",
        "Deposit Tk1000",
        "Withdraw Tk500",
        "Transfer Tk5000 to Sadnan",
        "Withdraw Tk1000",
    };

    int selected = 0;
    auto dashboard = ScreenInteractive::TerminalOutput();
    MenuOption option;
    option.on_enter = [&]
    {
        if(selected == 3)
        {
            dashboard.ExitLoopClosure()();
        }
    };

    auto menu = Menu(&options, &selected, option);
    auto container = Container::Vertical
    (
        {
            menu
        }
    );

    Elements profile_elems;
    for(const string& line : profile)
    {
        profile_elems.push_back(text(line));
    }

    Elements trx_elems;
    for(const string& line : recent_transactions)
    {
        trx_elems.push_back(text(line));
    }

    auto component = Renderer 
    ( 
        container, [&]
        {
            auto header = window
            (
                text(""),
                hbox
                (
                    {
                        filler(),
                        text("USER DASHBOARD") | bold,
                        filler(),
                    }
                )
            );

            auto main_box = window
            (
                text(" select an operation") | italic,
                hbox
                (
                    {
                        menu->Render()
                    }
                )
            );

            auto profile_box = window
            (
                text(" profile "),
                vbox(profile_elems)
            );
            auto trx_box = window
            (
                text(" recent transactions ") | italic,
                vbox(trx_elems)  | frame | size(HEIGHT, EQUAL, 5)
            );
            auto left_boxes =
                vbox
                (
                    {
                        profile_box,
                        trx_box
                    }
                );
            
            auto body =
                hbox
                (
                    {
                        main_box | size(WIDTH, EQUAL, 40),
                        left_boxes | flex
                    }
                );

            return vbox
            (
                {
                    header,
                    body
                }
            );
        } 
    );

    dashboard.Loop(component);

    return 0;
}