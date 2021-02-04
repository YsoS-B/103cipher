/*
** EPITECH PROJECT, 2020
** encrypt
** File description:
** encrypt functions source code file.
*/

#include "../header/103cipher.h"

int usage(void)
{
    printf("USAGE\n"
           "    ./103cipher message key flag\n\n"
           "DESCRIPTION\n"
           "    message     a message, made of ASCII characters\n"
           "    key         the encryption key, made of ASCII characters\n"
           "    flag        0 for the message to be encrypted, 1 to be dec"
           "rypted\n");
    exit(0);
}

int params_check(int ac, char **av)
{
    (ac == 2 && av[1][0] == '-' && av[1][1] == 'h' && av[1][2] == '\0') ? usage() : 0;
    if (ac != 4 || !av[1][0] || !av[2][0] || !av[3][0] /*|| (av[3][0] != '0' && av[3][0] != '1') || av[3][1] != '\0'*/)
        exit(84);
}

int next_sqr(int nb)
{
    int sk = sqrt(nb);
    int sl = nb;
    int sm = sk * sk;
    while (sm != sl) {
        sl++;
        sk = sqrt(sl);
        sm = sk * sk;
    }
    return (sm);
}

int *key_matrix(char *key)
{
	int size = next_sqr(strlen(key));
    int *new;
    int i = 0;
    new = malloc(sizeof(int) * size);
    for (i = 0; key[i] != '\0'; i++)
        new[i] = key[i];
    if (i != size)
        for (i; i != size; i++)
            new[i] = 0;
    return (new);
}

int *msg_to_int(char *msg, char *key)
{
    int rep = sqrt(next_sqr(strlen(key)));
    int reptmp = rep;
    int len = strlen(msg) + ((strlen(msg) % rep == 0) ? 0: (reptmp - (strlen(msg) % rep)));
    int *new;
    int i = 0;
    new = malloc(sizeof(int) * len);
    for (i = 0; msg[i] != '\0'; i++)
        new[i] = msg[i];
	if (i != len)
        for (i; i != len; i++)
            new[i] = 0;
    return (new);
}

int msg_len(char *msg, char *key)
{
	int rep = sqrt(next_sqr(strlen(key)));
	int reptmp = rep;
	int len = strlen(msg) + ((strlen(msg) % rep == 0) ? 0: (reptmp - (strlen(msg) % rep)));
	return (len);
}

void encrypt(char *mmsg, char *kkey)
{
    int j, k, l, m, n = 0, matx = 0;
    int nsq = next_sqr(strlen(kkey));
    int rep = sqrt(nsq);
    int *key = key_matrix(kkey);
    int *msg = msg_to_int(mmsg, kkey);
    int len = msg_len(mmsg, kkey);
    printf("Key matrix:\n");
    for (int i = 0, j = 0; i != nsq; i++) {
        if (j + 1 == rep) {
            j = 0;
            printf("%d\n", key[i]);
        } else {
            printf("%d\t", key[i]);
            j++;
        }
    }
    printf("\nEncrypted message:\n");
    for (int i = 0, j = 0, l = 0; i != len; i += rep) {
        m = 0;
        while(m < rep) {
            k = 0;
            l = i;
            while (k < rep) {
                matx += msg[l] * key[m + (k * rep)];
                l++;
                k++;
            }
            n += 1;
            if (n != len)
                printf("%d ", matx);
            else
                printf("%d\n", matx);
            m++;
            matx = 0;
        }
    }
}
