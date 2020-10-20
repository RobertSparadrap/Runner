/*
** EPITECH PROJECT, 2020
** game_function
** File description:
** 
*/

#include "../include/runner.h"

void cg_step(void *ss, sfVector2f vector)
{
    component_group_t *s1 = (component_group_t *) ss;
    if (!s1)
        return;
    if (!s1->chain)
        return;
    component_list_t *s = s1->chain;
    while (s) {
        sfSprite_move(s->sprite, vector);
        s = s->next;
    }
}

void mario_step(void *s1, void *_a)
{
    component_list_t *s = (component_list_t *) s1;
    static int i = 0;
    if (i++ % s->time_divider != 0)
        return;
    s->box.left += 60;
    if (s->box.left == 420)
        s->box.left = 0;
}

void mario_jump(void *s1, void *qq)
{
    static sfSound *sound_jump;
    static int play = 1;
    if(s1 == NULL) { sound_jump = (sfSound *)qq;
        return;
    }
    if(sfSound_getStatus(sound_jump) != sfPlaying && play) {
        play = 0;
        sfSound_play(sound_jump);
    }
    static int up = -1, n = 120;
    component_list_t *s = (component_list_t *) s1;
    int dy = s->vec.y;
    static float height = 2500.f;
    s->box.left = n;
    s->vec.x = 0;
    sfVector2f pos = sfSprite_getPosition(s->sprite);
    s->vec.y = up * dy / ((int) ((500 - pos.y) / 100 + 1));
    if (pos.y + s->vec.y > 500) s->vec.y = 500 - pos.y;
    if (pos.y <= height) { up = 1;
        n = 360;
    }
    if (pos.y >= 500.f && up == 1) {
        sfSound_stop(sound_jump);
        play = 1;
        mario_fn = mario_step;
        up = -1;
        n = 120;
        height = 120;
    }
}

void repeat_fond(void *ss, void *a)
{
    component_list_t *s1 = (component_list_t *) ss;
    sfSprite *s = s1->sprite;
    sfVector2f pos;
    pos = sfSprite_getPosition(s);
    if (pos.x <= -2100.f)
        pos.x = 2100;
    sfSprite_setPosition(s, pos);
}

void repeat_castle(void *ss, void *a)
{
    component_list_t *s1 = (component_list_t *) ss;
    sfSprite *s = s1->sprite;
    sfVector2f pos;
    pos = sfSprite_getPosition(s);
    if (pos.x <= -3850.f)
        pos.x = 3850;
    sfSprite_setPosition(s, pos);
}

void repeat(void *ss, void *a)
{
    component_list_t *s1 = (component_list_t *) ss;
    sfSprite *s = s1->sprite;
    sfVector2f pos;
    pos = sfSprite_getPosition(s);
    if (pos.x <= -480.f)
        pos.x = 240 * (*(s1->length) - 2) + (pos.x - 480.f);
    sfSprite_setPosition(s, pos);
}

void cg_step_fn(component_group_t *s1, sfVector2f vector,
                void (*fn)(void *, void *))
{
    if (!s1)
        return;
    component_list_t *s = s1->chain;
    while (s) {
        s->vec = vector;
        fn(s, NULL);
        sfSprite_move(s->sprite, s->vec);
        s = s->next;
    }
}

int collision(context_t *context)
{
    sfFloatRect s, c;
    sfFloatRect r = sfSprite_getGlobalBounds(
        context->RUNNER_GRP->chain->sprite);
    component_list_t *a = context->GROUND_GRP->chain;
    int i = 0;
    while (1) {
        s = sfSprite_getGlobalBounds(a->sprite);
        sfBool intersect = sfFloatRect_intersects(&r, &s, &c);
        if (intersect & c.width > 20) i++;
        if (intersect)
            if (a->deadly)
                if (c.width * c.height > a->deadly)
                    return -1;
        if (!a->next)
            break;
        a = a->next;
    }
    return i;
}

void cg_draw(sfRenderWindow *window, component_group_t *s1)
{
    if (!s1)
        return;
    if (!s1->chain)
        return;
    component_list_t *s = s1->chain;
    while (s) {
        sfSprite_setTextureRect(s->sprite, s->box);
        sfRenderWindow_drawSprite(window, s->sprite, NULL);
        s = s->next;
    }
}

void cg_draw_fn(sfRenderWindow *window, component_group_t *s1,
                void (*fn)(void *, void *))
{
    if (!s1)
        return;
    if (!s1->chain)
        return;
    component_list_t *s = s1->chain;
    while (s) {
        fn(s, NULL);
        sfSprite_setTextureRect(s->sprite, s->box);
        sfRenderWindow_drawSprite(window, s->sprite, NULL);
        s = s->next;
    }
}
