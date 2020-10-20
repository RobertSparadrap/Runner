/*
** EPITECH PROJECT, 2019
** get_next_line
** File description:
** get_next_line
*/

#include "../include/get_next_line.h"

char *mcpy(char *a, char *b, int n)
{
    for (int i = 0; i < n ; i++)
        *(b+i) = *(a+i);
    return b;
}

char *append_str(char *buffer, char **iline, size_t l_pos, size_t b_eol,
                 size_t b_pos)
{
    char *tmp = malloc(l_pos);
    if (l_pos > 0)
        mcpy(*iline, tmp, l_pos);
    free(*iline);
    char *line = malloc(l_pos + b_eol - b_pos + 2);
    if (l_pos > 0)
        mcpy(tmp, line, l_pos);
    mcpy(buffer + b_pos, line + l_pos, b_eol - b_pos);
    free(tmp);
    return line;
}

char *get_next_line(int fd)
{
    static char *buffer = NULL;
    static size_t b_pos = 0, b_eol = 0, r = 1;
    static ssize_t size;
    int p = 0, l_pos = 0;
    char *line = NULL;
    if (!buffer) buffer = malloc(READ_SIZE + 2);
    while (1) {
        if (r) {
            size = read(fd, buffer, READ_SIZE);
            if (size == 0) break;
            b_eol = b_pos = 0;
        }
        while (1)
            if (buffer[b_eol] == 0 || b_eol == size || buffer[b_eol++] == '\n') break;
        line = append_str(buffer, &line, l_pos, b_eol, b_pos);
        l_pos += b_eol - b_pos;
        if (line[l_pos - 1] == '\n') { line[l_pos] = 0;
            p = 1;
        }
        r = (b_eol == size);
        b_pos = b_eol;
        if (p) return line;
    }
    return line;
}
