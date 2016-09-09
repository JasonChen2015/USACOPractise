/*
ID: cyl12341
LANG: C
TASK: dualpal
 */
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAXLEN 20

const char indexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                         'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', '0'};

int checkPalindrome(char *str) {
    int flag = 1;
    int i, len;
    len = strlen(str);
    for (i = 0; i < len / 2; i++) {
        if (str[i] != str[len - i - 1]) {
            flag = 0;
            break;
        }
    }
    return flag;
}

// change the number(base 10) into a string of new number(base base)
void getBaseIndex(int base, int number, char *str) {
    int i, l = 0;
    while (number > 0) {
        str[l] = indexmap[number % base];
        number = number / base;
        l++;
    }
    for (i = 0; i < l / 2; i ++) {
        char ch = str[i];
        str[i] = str[l - 1 - i];
        str[l - 1 - i] = ch;
    }
    str[l] = '\0';
}

int main (void)
{
    int n, s, total, i;
    char numstr[MAXLEN];
    int flag = 0;
    FILE *fin = fopen("dualpal.in", "r");
    FILE *fout = fopen("dualpal.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d %d", &n, &s);

    while (flag < n) {
        s++;
        total = 0;
        for (i = 2; i <= 10; i++) {
            getBaseIndex(i, s, numstr);
            if (checkPalindrome(numstr) == 1) {
                total++;
                if (total >= 2) break;
            }
        }
        if (total >= 2) {
            fprintf(fout, "%d\n", s);
            flag++;
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}

