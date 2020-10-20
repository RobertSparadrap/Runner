/*
** EPITECH PROJECT, 2019
** get_next_line
** File description:
** 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H
#ifndef READ_SIZE
#define READ_SIZE 200
#endif
char *mcpy(char *a, char *b, int n);
char *get_next_line(int fd);

#endif
