/*
** EPITECH PROJECT, 2020
** 103cipher
** File description:
** 103cipher header file.
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

void encrypt(char *mmsg, char *kkey);
void decrypt(char *mmsg, char *kkey);
int usage(void);
int params_check(int, char **);
int message_length(char *);
int *get_message(char *);
