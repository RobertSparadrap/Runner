/*
** EPITECH PROJECT, 2019
** struct
** File description:
** 
*/

#include "../include/runner.h"
#include "../include/get_next_line.h"

component_t SPRITE_GRD = {"graphics/ground3.png", {58, 0, 80, 60}, {3, 3}, 0};
component_t SPRITE_GRD1 = {"graphics/ground3.png", {0, 0, 48, 60}, {4, 4}, 0};
component_t SPRITE_BKG = {"graphics/fond.png", {0, 0, 1100, 1200}, {2, 2}, 0};
component_t SPRITE_CST = {"graphics/mario_map.png", {0, 0, 1835, 1000}, {2.1,
                                                                         2.1},0};
component_t SPRITE_MRJ = {"graphics/Mario3.png", {0, 0, 60, 95}, {4, 4}, 0};
component_t SPRITE_STN = {"graphics/stones.png", {1260, 80, 270, 136}, {.8, .8},
                          5000};
component_t SPRITE_TUY = {"graphics/tuyau.png", {0, 0, 1150, 1150}, {0.2, 0.3},
                          5000};

const int f_rate0 = 120;

void cg_add(component_group_t *grp, component_t component, sfVector2f position,
            long time_divider)
{
    component_list_t *clt = malloc(sizeof(component_list_t));
    clt->length = &(grp->size);
    sfTexture *texture_g = sfTexture_createFromFile(component.name, NULL);
    sfSprite *sprite_g = sfSprite_create();
    sfSprite_setScale(sprite_g, component.scale);
    sfSprite_setTexture(sprite_g, texture_g, sfTrue);
    sfSprite_setPosition(sprite_g, position);
    clt->next = NULL;
    clt->p0 = position;
    clt->sprite = sprite_g;
    clt->box = component.box;
    clt->time_divider = time_divider;
    clt->deadly = component.deadly;
    if (grp->chain) {
        component_list_t *c = grp->chain;
        while (c->next)
            c = c->next;
        c->next = clt;
    } else
        grp->chain = clt;
}

char *my_split(char *str, char del)
{
    static char *a;
    if (str != NULL)
        a = str;
    char *ret = a;
    while (*a != del && *a != '\n' && *a != '\0')
        a++;
    *a++ = '\0';
    return ret;
}

void getFromMap(component_group_t *s, char const *filename)
{
    int dx = 240;
    sfVector2f vec;
    int map = open(filename, O_RDONLY);
    char *header = get_next_line(map);
    char *pos = my_split(header, ' ');
    vec.y = (float) my_getnbr(pos);
    int i = 0;
    char *line = NULL;
    while (vec.y) {
        line = get_next_line(map);
        for (int y = 0; line[y]; y++) {
            vec.x = dx * y;
            if (line[y] == '0')
                cg_add(s, SPRITE_GRD, vec, 0);
            if (line[y] == '1')
                cg_add(s, SPRITE_STN, vec, 0);
            if (line[y] == '2')
                cg_add(s, SPRITE_TUY, vec, 0);
        }
        i++;
        pos = my_split(NULL, ' ');
        vec.y = (float) my_getnbr(pos);
    }
    if (line)
        s->size = my_strlen(line);
}

context_t *create_init_context()
{
    context_t *context = malloc(sizeof(context_t));
    context->RUNNER_GRP = malloc(sizeof(component_group_t));
    context->CASTLE_GRP = malloc(sizeof(component_group_t));
    context->GROUND_GRP = malloc(sizeof(component_group_t));
    context->GRMENU_GRP = malloc(sizeof(component_group_t));
    context->FOND = malloc(sizeof(component_group_t));
    context->RUNNER_GRP->chain = NULL;
    context->CASTLE_GRP->chain = NULL;
    context->GROUND_GRP->chain = NULL;
    context->GRMENU_GRP->chain = NULL;
    context->RUNNER_GRP->size = 0;
    context->CASTLE_GRP->size = 0;
    context->GROUND_GRP->size = 0;
    context->GRMENU_GRP->size = 0;
    context->FOND->size = 0;
    context->f_rate = f_rate0;
    context->status = 0 ;
    return context;
}

context_t *init(char const *filepath)
{
    sfVector2f vec_c = {0, 350}, vec_c2 = {3850, 350};
    sfVector2f vec_r = {90, 500}, vec = {0, 860}, vec_f = {0, 0}, vec_f2 = {2100, 0};
    context_t *context = create_init_context();
    cg_add(context->RUNNER_GRP, SPRITE_MRJ, vec_r, 15);
    cg_add(context->CASTLE_GRP, SPRITE_CST, vec_c, 0);
    cg_add(context->CASTLE_GRP, SPRITE_CST, vec_c2, 0);
    cg_add(context->FOND, SPRITE_BKG, vec_f, 0);
    cg_add(context->FOND, SPRITE_BKG, vec_f2, 0);
    for (int i = 0; i < 12; i++) {
        vec.x = 240 * i;
        cg_add(context->GRMENU_GRP, SPRITE_GRD, vec, 0);
    }
    getFromMap(context->GROUND_GRP, filepath);
    return context;
}

context_t *reinit(context_t * context)
{
    sfVector2f vec_r = {90, 500}, vec = {0, 860};
    sfSprite_setPosition(context->RUNNER_GRP->chain->sprite, vec_r);
    component_list_t *s =  context->GROUND_GRP->chain;
    context->f_rate = f_rate0;
    while(1) {
        sfSprite_setPosition(s->sprite, s->p0);
        if (s->next == NULL) break;
        s = s->next;
    }
    return context;
}
