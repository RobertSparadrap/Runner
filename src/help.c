/*
** EPITECH PROJECT, 2019
** help
** File description:
** 
*/

#include <stdlib.h>
#include <stdio.h>
#include "../include/my.h"

void help()
{
    my_printf("\n Peach s'est encore fait captuer !\n");
    my_printf("Bowser l'a amener dans son chateau, Mario doit faire tout le chemin jusqu'au chateau sans se blesser.\n");
    my_printf("\n  Dans le menu, appuyez sur ESPACE pour commencer le jeu et aller sauver Peach ou appuyez sur Q pour la laisser tomber.\n");
    my_printf("Pendant que Mario court pour sauver Peach, appuyez sur ESPACE pour sauter et esquiver les obstacles \n\n");
    my_printf("\n pour commencer a jouer, lancer le jeu avec './my_runner map', vous pouviez quitter le jeu a tout instant avec Q.\n");
    my_printf("Lorsque vous avez perdu, vous pouvez apuyer sue SPACE pour recommencer\n");
    my_printf("La map disponible pour lancer le jeu est maps/level1.map\n\n");
    my_printf("Donc pour lancer le jeu il faut taper: my_runner maps/level1.map\n\n");
}
