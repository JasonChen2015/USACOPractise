/*
ID: cyl12341
LANG: C
TASK: fence9
*/
#include <stdio.h>
#include <assert.h>

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

/*
 * Other solution:
 *
 *   Pick's Theorem states that if we have a polygon with lattice points as vertices, then:
 *
 *                                      A = I + B / 2 - 1
 *
 *   where A is the area of the polygon, I is the number of lattice points inside of the polygon,
 *   and B is the number of lattice points on the boundary of the polygon
 *
 */

int gcd(int x, int y) {
    if (y == 0) {
        return x;
    } else {
        return gcd(y, x % y);
    }
}

int main() {
    int n, m, p, c;
    int i, j;

    FILE *fin = fopen("fence9.in", "r");
    FILE *fout = fopen("fence9.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d%d%d", &n, &m, &p);

    c = (n - 1) * (m - 1); // points in rectangle (0, 0, n, m)
    c -= gcd(MAX(n, m), MIN(n, m)) - 1; // points in line (0, 0, n, m)
    c /= 2; // points in triangle (0, 0), (n, m), (n, 0)

    if ((n - p) > 0) {
        i = (n - p - 1) * (m - 1); // points in rectangle (p, 0, n, m)
        j = gcd(MAX(n - p, m), MIN(n - p, m)) - 1; // points in line (p, 0, n, m)
        i = (i - j) / 2; // points in triangle (p, 0), (n, m), (n, 0)

        c -= i + j;
    } else if ((n - p) < 0) {
        i = (p - n - 1) * (m - 1); // points in rectangle (n, 0, p, m)
        j = gcd(MAX(p - n, m), MIN(p - n, m)) - 1; // points in line (n, m, p, 0)
        i = (i - j) / 2; // points in triangle (n, 0), (n, m), (p, 0)

        c += i + m - 1;
    }

    fprintf(fout, "%d\n", c);

    fclose(fin);
    fclose(fout);

    return 0;
}

