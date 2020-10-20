/*
** EPITECH PROJECT, 2019
** runner
** File description:
** 
*/

#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <SFML/Window.h>
#include <SFML/Audio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include "my.h"

#ifndef RUNNER_H
#define RUNNER_H

typedef struct component{
    char * name;
    sfIntRect box;
    sfVector2f scale;
    int deadly;
} component_t;

typedef struct component_list {
    struct component_list * next;
    sfSprite * sprite;
    sfIntRect box;
    sfVector2f vec;
    long time_divider;
    int * length;
    int deadly;
    sfVector2f p0;
} component_list_t;

typedef struct component_group{
    component_list_t * chain;
    int size;
} component_group_t;

typedef struct context{
    component_group_t * CASTLE_GRP;
    component_group_t * GROUND_GRP;
    component_group_t * GRMENU_GRP;
    component_group_t * RUNNER_GRP;
    component_group_t * FOND;
    sfRenderWindow *window;
    int f_rate;
    int status;
} context_t;

sfRenderWindow *create_window(sfRenderWindow *window);
sfSprite *get_fond(sfRenderWindow *window, char const *filepath);
void menu(sfRenderWindow *window, context_t *context);
int runner(sfRenderWindow *window, context_t *context);
int play(sfRenderWindow *window, context_t *context, sfVector2f n2dx);
sfText *getText();
void help();
context_t * init(const char *);
void (*mario_fn)(void *, void *);
void cg_step(void * s1, sfVector2f vector);
void mario_step(void * s, void * _a);
void mario_jump(void * s, void * qq);
void repeat(void * s1, void * a);
void repeat_castle(void *s1, void *a);
void repeat_fond(void *ss, void *a);
void cg_step_fn(component_group_t * s1, sfVector2f vector, void (*fn)(void *,
                                                                      void *));
void cg_draw(sfRenderWindow *window, component_group_t *s1);
void cg_draw_fn(sfRenderWindow *window, component_group_t * s1, void (*fn)
                (void *, void *));
int collision(context_t * context);
void put_text(sfRenderWindow *window, char *str, sfColor col, sfVector2f pos,
              sfVector2f scale);
context_t *reinit( context_t * context);

#endif
