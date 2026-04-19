#include <string>
#include <vector>

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

using namespace std;
using namespace ftxui;

int main()
{   
    auto signup_screen = ScreenInteractive::TerminalOutput();
    string username, password, confirm_password, dob, msg;

    InputOption o_username;
    o_username.placeholder = "Set username";
    InputOption o_pwd;
    o_pwd.placeholder = "Set password";
    o_pwd.password = true;
    InputOption o_confirmpwd;
    o_confirmpwd.placeholder = "Confirm your password";
    o_confirmpwd.password = true;
    InputOption o_dob;
    o_dob.placeholder = "Set date of birth";

    auto i_username = Input(&username, o_username);
    auto i_password = Input(&password, o_pwd);
    auto i_confirmpwd = Input(&confirm_password, o_confirmpwd);
    auto i_dob = Input(&dob, o_dob);

    auto button_submit = Button
    (
        "Signup",
        [&]
        {
            if(username.empty() || password.empty() || confirm_password.empty() || dob.empty())
            {
                msg = "All fields are required.";
                return;
            }
            else if(password != confirm_password)
            {
                msg = "Passwords dont match.";
                return;
            }
            else
            {
                msg = "Signup successful.";
            }

        }
    );


    auto container = Container::Vertical
    (
        {
            i_username,
            i_password,
            i_confirmpwd,
            i_dob,
            button_submit
        }
    );

    auto render = Renderer
    (
        container, [&]
        {
            auto window_header = window
            (
                text(""), hbox
                (
                    {
                        filler(),
                        text("SIGNUP") | bold,
                        filler()
                    }
                )
            );

            auto window_username = window
            (
                text(" Username ") | italic,
                vbox
                (
                    {
                        i_username->Render()
                    }
                )
            );

            auto window_pwd = window
            (
                text(" Password ") | italic,
                vbox
                (
                    {
                        i_password->Render()
                    }
                )
            );
            auto window_cpwd = window
            (
                text(" Confirm password ") | italic,
                vbox
                (
                    {
                        i_confirmpwd->Render()
                    }
                )
            );
            auto window_dob = window
            (
                text(" Date of birth ") | italic,
                hbox
                (
                    {
                        i_dob->Render()
                    }
                )
            );
            auto box_button = hbox
            (
                {
                    filler(),
                    button_submit->Render(),
                    filler()
                }
            );
            auto box_msg = hbox
            (
                {
                    filler(),
                    text(msg) | color(Color::Yellow),
                    filler()
                }
            );

            return vbox
            (
                {
                    window_header,
                    window_username,
                    window_pwd,
                    window_cpwd,
                    window_dob,
                    box_button,
                    box_msg
                }
            );
        }
    );

    signup_screen.Loop(render);
    
    return 0;
}