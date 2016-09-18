/*
ID: cyl12341
LANG: C
TASK: cowtour
*/
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>

#define INF 1e40

int n;
int point[150][2];
double dis[150][150];
double dis_max[150];

double getDis(int p, int q) {
    int px = point[p][0];
    int py = point[p][1];
    int qx = point[q][0];
    int qy = point[q][1];
    return sqrt((px - qx) * (px - qx) + (py - qy) * (py - qy));
}

int main(void) {
    int i, j, k;

    FILE *fin = fopen("cowtour.in", "r");
    FILE *fout = fopen("cowtour.out", "w");

    fscanf(fin, "%d", &n);
    for (i = 0; i < n; i++) fscanf(fin, "%d%d", &point[i][0], &point[i][1]);
    for (i = 0; i < n; i++) {
        fscanf(fin, "\n");
        for (j = 0; j < n; j++) {
            char ch;
            fscanf(fin, "%c", &ch);
            if (ch == '1') {
                dis[i][j] = dis[j][i] = getDis(i, j);
            } else {
                dis[i][j] = dis[j][i] = INF;
            }
        }
    }

    // get max distance from point x
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i != j)
                for (k = 0; k < n; k++) {
                    if (i != k && j != k)
                        if (dis[i][j] + dis[j][k] < dis[i][k])
                            dis[i][k] = dis[k][i] = dis[i][j] + dis[j][k];
                }
        }
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i != j && dis[i][j] != INF && dis[i][j] > dis_max[i])
                dis_max[i] = dis[i][j];
        }
    }

    // attempt to add line to get the min distance
    double min = INF;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i != j && dis[i][j] == INF) {
                double d = getDis(i, j);
                if (dis_max[i] + d + dis_max[j] < min) min = dis_max[i] + d + dis_max[j];
            }
        }
    }

    // make sure the distance is the longest one in combined field
    for (i = 0; i < n; i++)
        if (min < dis_max[i]) min = dis_max[i];

    fprintf(fout, "%.6f\n", min);

    fclose(fin);
    fclose(fout);
    return 0;
}

