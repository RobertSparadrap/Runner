/*
** EPITECH PROJECT, 2019
** runner
** File description:
** 
*/

#include "../include/runner.h"

int event_loop(sfRenderWindow *window, sfEvent event, int game_state)
{
    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed)
            game_state = -1;
        if (sfKeyboard_isKeyPressed(sfKeyQ))
            game_state = -1;
        switch(game_state) {
        case 1:
            if (sfKeyboard_isKeyPressed(sfKeySpace) &&
                (mario_fn == mario_step))
                mario_fn = mario_jump;
            break;
        case 2:
            if (sfKeyboard_isKeyPressed(sfKeySpace))
                game_state = -3;
            break;
        case 0:
            if (sfKeyboard_isKeyPressed(sfKeySpace)) {
                mario_fn = mario_step;
                game_state = 1;
            }
        }
        break;
    }
    return game_state;
}

sfText *render_score(int score)
{
    sfText *score_text = getText();
    char str[5] = {0};
    if (score > 9 && score < 100) {
        str[0] = (score / 10 + '0');
        str[1] = (score % 10 + '0');
    } else if (score > 99 && score < 1000) {
        str[0] = (score / 100 + '0');
        str[1] = ((score / 10) % 10 + '0');
        str[2] = (score % 10 + '0');
    } else if (score > 999) {
        str[0] = (score / 1000 + '0');
        str[1] = ((score / 100) % 10 + '0');
        str[2] = ((score / 10) % 10 + '0');
        str[3] = (score % 10 + '0');
    } else
        str[0] = (score % 10 + '0');
    sfText_setString(score_text, str);
    return score_text;
}

int runner(sfRenderWindow *window, context_t *context)
{
    static int mb = 1, gb = 0, rb = 0;
    sfVector2f n2dx = {-3 * 120 / context->f_rate, 0};
    sfVector2f text_vec = {300, 400}, scale = {3.2f, 3.2f}, text_s = {200, 0};
    int score = 0;
    sfEvent event;
    sfMusic *music_game = sfMusic_createFromFile("graphics/musicDS.ogg");
    sfMusic *music_menu = sfMusic_createFromFile("graphics/menu_music.ogg");
        sfSoundBuffer *sound_jump_buffer = sfSoundBuffer_createFromFile
            ("graphics/smb_saut.ogg");
        static sfSound *sound_jump;
        sound_jump  = sfSound_create();
        sfSound_setBuffer(sound_jump, (sfSoundBuffer*) sound_jump_buffer);
        sfSound_setLoop(sound_jump, sfFalse);
        mario_jump(NULL, sound_jump);
        sfText *text = getText(), *text_space = getText();;
        sfText_setScale(text, scale);
        sfText_setPosition(text, text_vec);
        sfText_setPosition(text_space, text_s);
        sfText_setColor(text, sfRed);
        sfText_setString(text, "Game Over");
        sfText_setString(text_space, "press space to restart");
        mario_fn = mario_step;
        while (sfRenderWindow_isOpen(window)) {
            context->status = event_loop(window, event, context->status);
            switch(context->status) {
            case 0:
                if(mb) { mb--;
                    sfMusic_play(music_menu);
                    gb++;
                }
                sfRenderWindow_clear(window, sfBlack);
                menu(window, context);
                break;
            case 1:
                if(gb) {
                    gb--;
                    sfMusic_pause(music_menu);
                    sfMusic_play(music_game);
                    rb++;
                }
                context->f_rate =  120 - (int)(++score/ 120);
            case 2:
                n2dx.x = -3 * 120 / context->f_rate;
                context->status = play(window, context, n2dx);
                sfRenderWindow_drawText(window, render_score
                                        (score/context->f_rate), NULL);
                if(context->status == 1) break;
                sfRenderWindow_drawText(window, text, NULL);
                sfRenderWindow_drawText(window, text_space, NULL);
                break;
            case -1:
                sfRenderWindow_close(window);
                break;
            case -3:
                if(rb) { rb--;
                    score = 0;
                    mb++;
                }
                context = reinit(context);
                score = 0;
                context->status = 0;
                break;
            }
            sfRenderWindow_display(window);
        }
        sfMusic_destroy(music_game);
        sfMusic_destroy(music_menu);
        sfSound_destroy(sound_jump);
        sfSoundBuffer_destroy(sound_jump_buffer);
}
