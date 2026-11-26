#ifndef INPUT_H
#define INPUT_H

enum menu_result { MENU_CHOICE, MENU_QUIT, MENU_EOF };
enum menu_result read_menu_choice(int min, int max, int *choice);

#endif
