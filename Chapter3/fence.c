/*
ID: cyl12341
LANG: C
TASK: fence
*/
#include <stdio.h>
#include <assert.h>

#define MAXPOINT 501

int linkcount[MAXPOINT];
int map[MAXPOINT][MAXPOINT];
int queue[1025];
int f;

void eulerian(int s) {
    int i;
    if (!linkcount[s]) {
        queue[++queue[0]] = s;
    } else {
        for (i = 1; i < MAXPOINT; i++) {
            if (map[s][i]) {
                map[s][i]--; map[i][s]--;
                linkcount[s]--; linkcount[i]--;
                eulerian(i);
            }
        }
        queue[++queue[0]] = s;
    }
}

int main() {
    int i, j, k;
    FILE *fin = fopen("fence.in", "r");
    FILE *fout = fopen("fence.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d", &f);
    for (i = 0; i < f; i++) {
        fscanf(fin, "%d%d", &j, &k);
        map[j][k]++; map[k][j]++;
        linkcount[j]++; linkcount[k]++;
    }

    // get the start point and run eulerian path
    for (i = 1; i < MAXPOINT; i++) {
        if (linkcount[i] % 2) {
            eulerian(i);
            break;
        }
        if (i == 500) { eulerian(1); }
    }

    for (i = queue[0]; i > 0; i--) fprintf(fout, "%d\n", queue[i]);

    fclose(fin);
    fclose(fout);
    return 0;
}

