/*
ID: cyl12341
LANG: C
TASK: palsquare
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
    int n, i;
    FILE *fin = fopen("palsquare.in", "r");
    FILE *fout = fopen("palsquare.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d", &n);

    for (i = 1; i <= 300; i++) {
        char num[MAXLEN], square[MAXLEN];
        getBaseIndex(n, i, num);
        getBaseIndex(n, i * i, square);
        if (checkPalindrome(square) == 1) {
            fprintf(fout, "%s %s\n", num, square);
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}

