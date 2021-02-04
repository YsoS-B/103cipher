/*
** EPITECH PROJECT, 2020
** main
** File description:
** main function of 103cipher project.
*/

#include "../header/103cipher.h"

int message_length(char *msg)
{
    int	length = 1;
    for	(int i = 0; msg[i] != '\0'; i++)
        (msg[i] == ' ')	? length++ : 0;
    return (length);
}

int *get_message(char *msg)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int length = message_length(msg);
    char *temp;
    int add = (length % 3 == 0) ? 0 : (3 - (length % 3));
    int *message = malloc(sizeof(int) * (length + add + 1));
    for (i = 0; i != length; i++) {
        temp = malloc(sizeof(char) * 7);
        for (k = 0; msg[j] != ' ' && msg[j] != '\0'; j++)
            temp[k++] = msg[j];
        temp[k] = '\0';
        j++;
        message[i] = atoi(temp);
    }
    free(temp);
    return (message);
}

double *reverse(double *tab)
{
    double *new = malloc(sizeof(int) * 9);
    new[0] = tab[0];
    new[1] = tab[3];
    new[2] = tab[6];
    new[3] = tab[1];
    new[4] = tab[4];
    new[5] = tab[7];
    new[6] = tab[2];
    new[7] = tab[5];
    new[8] = tab[8];
    return (new);
}

int *str_to_int(char *str)
{
	int add = 0;
	int len = strlen(str);
    int *new;
    (len >= 2 && len <= 4) ? add = (len % 2 == 0) ? 0: (2 - (len % 2)) : 0;
	(len >= 5 && len <= 9) ? add = (len % 3 == 0) ? 0: (3 - (len % 3)) : 0;
    new = malloc(sizeof(int) * (strlen(str) + add + 1));
    for (int i = 0; str[i] != '\0'; i++)
        new[i] = str[i];
    return (new);
}

void rounded(double *kkey)
{
    char buffer[15];
    for (int i = 0; i != 9; i++) {
        sprintf(buffer, "%.3f\n", kkey[i]);
        kkey[i] = atof(buffer);
    }
}

double *rev_key(char *kkey)
{
    double det;
    double *rev;
    double tab[9];
    int	*key = str_to_int(kkey);
    tab[0] = key[4] * key[8] - key[7] * key[5];
    tab[1] = -1 * (key[3] * key[8] - key[6] * key[5]);
    tab[2] = key[3] * key[7] - key[4] * key[6];
    tab[3] = -1 * (key[1] * key[8] - key[7] * key[2]);
    tab[4] = (key[0] * key[8] - key[6] * key[2]);
    tab[5] = -1 * (key[0] * key[7] - key[6] * key[1]);
    tab[6] = key[1] * key[5] - key[4] * key[2];
    tab[7] = -1 * (key[0] * key[5] - key[3] * key[2]);
    tab[8] = key[0] * key[4] - key[3]*key[2];
    det = key[0] * tab[0] + key[1] * tab[1] + key[2] * tab[2];
    (det == 0) ? exit(84) : 0;
    rev = malloc(sizeof(double) * 9);
    for (int i = 0; i != 9; i++)
        rev[i] = ((tab[i] / det) == 0) ? 0.000 : tab[i] / det;
    free(key);
    return (reverse(rev));
}

void displayrkey(char *kkey)
{
	int col;
	int br;
	int len = strlen(kkey);
	double *key = rev_key(kkey);
	(len >= 2 && len <= 4) ? col = 4, br = 2 : 0;
	(len >= 5 && len <= 9) ? col = 9, br = 3 : 0;
	if (len == 1) {
		printf("%.3f\n", key[0]);
		return ;
	}
	for (int i = 1; i <= col; i++) {
        if (i % br == 0) {
			printf("%.3f\n", key[i]);
			continue;
		}
		printf("%.3f\t", key[i]);
	}
}

void decrypt(char *mmsg, char *kkey)
{
    int j = 0;
    int tmp = 0;
    int length = message_length(mmsg);
    int *msg = get_message(mmsg);
    double *key = rev_key(kkey);
    printf("Key matrix:\n");
    displayrkey(kkey);
    printf("\nDecrypted message:\n");
    for (int i = 0; i != length; i += 3) {
        printf("%c", (char)round(msg[i] * key[0] + msg[i + 1] * key[3] + msg[i + 2] * key[6]));
        printf("%c", (char)round(msg[i] * key[1] + msg[i + 1] * key[4] + msg[i + 2] * key[7]));
        if (i != length - 3 && (msg[i] != 0 || msg[i] != 0 || msg[i + 2] != 0))
            printf("%c", (round(msg[i] * key[2] + msg[i + 1] * key[5] + msg[i + 2] * key[8]) > 0) ?
                   (char)round(msg[i] * key[2] + msg[i + 1] * key[5] + msg[i + 2] * key[8]) : '\0');
        if (i == length - 3 && (msg[i] != 0 || msg[i] != 0 || msg[i + 2] != 0))
            printf("%c\n", (round(msg[i] * key[2] + msg[i + 1] * key[5] + msg[i + 2] * key[8]) > 0) ?
                   (char)round(msg[i] * key[2] + msg[i + 1] * key[5] + msg[i + 2] * key[8]) : '\0');
    }
}

int main(int ac, char **av)
{
    params_check(ac, av);
    (av[3][0] == '0' && av[3][1] == '\0') ? encrypt(av[1], av[2]) : 0;
    (av[3][0] == '1' && av[3][1] == '\0') ? decrypt(av[1], av[2]) : 0;
    return (0);
}
