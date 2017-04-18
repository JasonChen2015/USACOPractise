/*
ID: cyl12341
LANG: C
TASK: heritage
*/
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define MAXNODE 26

char ldr[MAXNODE + 1]; // in-order
char dlr[MAXNODE + 1]; // pre-order
char lrd[MAXNODE + 1]; // post-order

FILE *fin, *fout;

/*
 * sLDR:  the start position in LDR
 * sDLR:  the start position in DLR
 * length: the length of sub-tree
 */
void getRepresentation(int sLDR, int sDLR, int length) {
    char st = dlr[sDLR]; // get root
    if (length <= 0) {
        return;
    } else if (length == 1) {
        fprintf(fout, "%c", st);
    } else {
        int i = sLDR;
        while (ldr[i] != st) i++;
        // left
        getRepresentation(sLDR, sDLR + 1, i - sLDR);
        // right
        getRepresentation(i + 1, sDLR + i - sLDR + 1, length - i + sLDR - 1);
        fprintf(fout, "%c", st);
    }
}

int main() {
    int n;

    fin = fopen("heritage.in", "r");
    fout = fopen("heritage.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%s", ldr);
    fscanf(fin, "%s", dlr);

    n = strlen(ldr);

    getRepresentation(0, 0, n);
    fprintf(fout, "\n");

    fclose(fin);
    fclose(fout);

    return 0;
}

