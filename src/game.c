/*
** EPITECH PROJECT, 2020
** game
** File description:
** 
*/

#include "../include/runner.h"

void menu(sfRenderWindow *window, context_t *context)
{
    sfVector2f mario_menu = {250, 200}, scale = {2, 4},
        play = {550, 500}, scale_play = {1, 0.7f},
        quit = {0, 950}, scale_quit = {1, 0.7f};
    sfVector2f z = {1, 0};
    sfVector2f dx = {-1, 0};
    cg_draw(window, context->FOND);
    cg_draw(window, context->CASTLE_GRP);
    cg_draw(window, context->GRMENU_GRP);
    cg_draw(window, context->RUNNER_GRP);
    put_text(window, "My Mario Runner", sfRed, mario_menu, scale);
    put_text(window, "Press space to play", sfWhite, play, scale_play);
    put_text(window, "Press q to quit", sfBlack, quit, scale_quit);
    cg_step_fn(context->RUNNER_GRP, z, mario_step);
}

int play(sfRenderWindow *window, context_t *context, sfVector2f n2dx)
{
    sfVector2f ndx = {n2dx.x / 2, 0}, z = {0, 0}, nf = {-1, 0};
    cg_draw(window, context->FOND);
    cg_draw(window, context->CASTLE_GRP);
    cg_draw(window, context->GROUND_GRP);
    cg_draw(window, context->RUNNER_GRP);
    if (context->status == 1) {
        int i = collision(context);
        if (mario_fn == mario_jump)
            z.y = 8 * 120 / context->f_rate;
        else if (i == 0) {
            z.y = 200;
            context->status = 2;
        } else if ( i == -1)
            context->status = 2;
        cg_step_fn(context->FOND, nf, repeat_fond);
        cg_step_fn(context->RUNNER_GRP, z, mario_fn);
        cg_step_fn(context->GROUND_GRP, n2dx, repeat);
        cg_step_fn(context->CASTLE_GRP, ndx, repeat_castle);
    }
    return context->status;
}
