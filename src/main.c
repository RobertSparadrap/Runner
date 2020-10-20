/*
** EPITECH PROJECT, 2019
** main
** File description:
** 
*/

#include "../include/runner.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        my_printf("Pour commencer le jeu, il faut choisir la map, taper: ./my_runner maps/level1.map\n\n");
        return 84;
    }
    if (argv[1][0] == '-' && argv[1][1] == 'h')
        help();
    else {
        sfRenderWindow *window;
        context_t *context = init(argv[1]);
        window = create_window(window);
        sfRenderWindow_setMouseCursorVisible(window, sfFalse);
        runner(window, context);
        sfRenderWindow_destroy(window);
    }
    return 0;
}
