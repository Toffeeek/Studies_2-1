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
    vector<string> _options = 
    {
        "1. Login",
        "2. Signup",
        "3. Admin Login",
        "4. Admin Signup",
        "5. Exit"
    };
    vector<string> _desc =
    {
        "Login as an existing user",
        "Signup as a new user, user must be over the age of 18",
        "Login with admin priviledges, only mean for admin level employees",
        "Apply for registration as an admin; registration will be approved after verification from the server",
        "Close the application and return to homescreen"
    };

    int selected = 0;
    auto baseScreen = ScreenInteractive::TerminalOutput();
    
    MenuOption option;
    option.on_enter = [&]
    {
        if(selected == 4)
        {
            baseScreen.ExitLoopClosure()();
        }
    };

    auto menu = Menu(&_options, &selected, option);
    auto container = Container::Vertical
    (
        {
            menu,
        }
    );

    auto component = Renderer
    (
        container, [&]
        {
            auto header_box = window
            (
                text(" welcome to ") | italic,
                hbox
                (
                    {
                        filler(),
                        text("AOZORA BANK") | bold,
                        filler()
                    }
                )
            );

            auto left_box = window
            (
                text(" menu ") | italic,
                menu->Render()   
            );

            auto right_box = window
            (
                text(" description ") | italic,
                paragraph(_desc[selected]) | size(WIDTH, EQUAL, 40)
            );

            auto body = hbox
            (
                {
                    left_box | flex,
                    right_box | flex
                }
            );

            return vbox
            (
                {
                    header_box,
                    body,
                }
            );

        }
    );

    baseScreen.Loop(component);
    return 0;
}