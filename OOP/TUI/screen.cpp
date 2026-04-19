#include <ncurses.h>
#include <vector>
#include <string>

int main() {
    std::vector<std::string> items = {
        "Option 1",
        "Option 2",
        "Option 3",
        "Option 4"
    };

    std::vector<std::string> art = {
        "   /\\_/\\\\",
        "  ( o.o )",
        "   > ^ <"
    };

    int selected = 0;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    while (true) {
        clear();

        for (int i = 0; i < (int)items.size(); i++) {
            if (i == selected) {
                attron(A_REVERSE);
                mvprintw(i, 0, "> %s", items[i].c_str());
                attroff(A_REVERSE);
            } else {
                mvprintw(i, 0, "  %s", items[i].c_str());
            }
        }

        int artCol = 25;
        for (int i = 0; i < (int)art.size(); i++) {
            mvprintw(i, artCol, "%s", art[i].c_str());
        }

        int ch = getch();

        if (ch == KEY_UP) {
            selected = (selected - 1 + items.size()) % items.size();
        } else if (ch == KEY_DOWN) {
            selected = (selected + 1) % items.size();
        } else if (ch == '\n') {
            break;
        }
    }

    endwin();
    return 0;
}