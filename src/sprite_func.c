/*
** EPITECH PROJECT, 2020
** sprite function
** File description:
** 
*/

#include "../include/runner.h"

sfRenderWindow *create_window(sfRenderWindow *window)
{
    sfVideoMode video_mode;
    video_mode.height = 1080;
    video_mode.width = 1920;
    window = sfRenderWindow_create(video_mode, "mario", sfDefaultStyle, NULL);
    sfRenderWindow_setFramerateLimit(window, 120);
    sfRenderWindow_setKeyRepeatEnabled(window, sfFalse);
    return window;
}

sfSprite *get_fond(sfRenderWindow *window, char const *filepath)
{
    sfVector2f scale;
    sfTexture *texture_f;
    sfSprite *sprite_f;
    scale.x = 2;
    scale.y = 2;
    texture_f = sfTexture_createFromFile(filepath, NULL);
    sprite_f = sfSprite_create();
    sfSprite_setScale(sprite_f, scale);
    sfSprite_setTexture(sprite_f, texture_f, sfTrue);
    return sprite_f;
}

sfSprite *
get_sprite(sfRenderWindow *window, char const *filepath, float x, float y)
{
    sfVector2f scale = {x, y};
    scale.x = x;
    scale.y = y;
    sfTexture *texture_g = sfTexture_createFromFile(filepath, NULL);
    sfSprite *sprite_g = sfSprite_create();
    sfSprite_setScale(sprite_g, scale);
    sfSprite_setTexture(sprite_g, texture_g, sfTrue);
    return sprite_g;
}

void event_close(sfRenderWindow *window)
{
    sfEvent event;
    sfEventType type;
    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
        if (sfKeyboard_isKeyPressed(sfKeyQ))
            sfRenderWindow_close(window);
    }
}

sfText *getText()
{
    sfText *text;
    sfFont *font;
    font = sfFont_createFromFile("graphics/SuperMario256.ttf");
    text = sfText_create();
    sfText_setString(text, "0");
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 70);
    return text;
}

void put_text(sfRenderWindow *window, char *str, sfColor col, sfVector2f pos,
              sfVector2f scale)
{
    sfText *text = getText();
    sfText_setString(text, str);
    sfText_setColor(text, col);
    sfText_setPosition(text, pos);
    sfText_setScale(text, scale);
    sfRenderWindow_drawText(window, text, NULL);
}
