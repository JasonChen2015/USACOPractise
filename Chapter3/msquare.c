/*
ID: cyl12341
LANG: C
TASK: msquare
*/
#include <stdio.h>
#include <assert.h>

#define HASHMOD 46189

int status[8];
int e[47000][3];  // record how to get to this status // 0: from which status 1: transformation 2: origin
int queue[40330]; // record the status  //8! = 40320
int matchCode;

void trans1(int tmp[8]) {
    int i, t;
    for (i = 0; i < 4; i++) {
        t = tmp[i]; tmp[i] = tmp[7 - i]; tmp[7 - i] = t;
    }
}

void trans2(int tmp[8]) {
    int i, t;
    t = tmp[3];
    for (i = 2; i >= 0; i--) tmp[i + 1] = tmp[i];
    tmp[0] = t;
    t = tmp[4];
    for (i = 4; i < 7; i++) tmp[i] = tmp[i + 1];
    tmp[7] = t;
}

void trans3(int tmp[8]) {
    int t;
    t = tmp[1]; tmp[1] = tmp[6]; tmp[6] = tmp[5]; tmp[5] = tmp[2]; tmp[2] = t;
}

// get code from a status array, {1, 2, 3, 4, 5, 6, 7, 8} -> 1234567
int getStatusCode(int tmp[8]) {
    int i, s;
    s = 0;
    for (i = 0; i < 7; i++) s = s * 10 + tmp[i];
    return s;
}

// get status array from a code, 1234567 -> {1, 2, 3, 4, 5, 6, 7, 8}
void getStatus(int index) {
    int i, t, s;
    s = 36; // 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8
    t = queue[index];
    for (i = 6; i >=0; i--) {
        status[i] = t % 10;
        t /= 10;
        s -= status[i];
    }
    status[7] = s;
}

// get hash from a code, 1234567 -> 33653
int getHash(int statusCode) {
    int hash;
    hash = statusCode % HASHMOD;
    while (e[hash][2] != 0 && e[hash][2] != statusCode) hash++;
    return hash;
}

int main() {
    int i, p, q, t;
    int newStatusCode, oldStatusCode;
    FILE *fin = fopen("msquare.in", "r");
    FILE *fout = fopen("msquare.out", "w");

    for (i = 0; i < 8; i++) {
        fscanf(fin, "%d", &status[i]);
    }
    matchCode = getStatusCode(status);
    if (matchCode == 1234567) {
        // no move
        fprintf(fout, "0\n\n");
        fclose(fin);
        fclose(fout);
        return 0;
    }

    // BFS
    for (i = 0; i < 8; i++) { status[i] = i + 1; }
    p = -1;
    q = 0;
    queue[q] = getStatusCode(status);
    e[getHash(queue[q])][2] = queue[q];
    while (p <= q) {
        p++;
        // transformation 1
        getStatus(p);
        oldStatusCode = getStatusCode(status);
        trans1(status);
        newStatusCode = getStatusCode(status);
        t = getHash(newStatusCode);
        if (e[t][2] != newStatusCode) {
            // record to hash array
            e[t][0] = oldStatusCode;
            e[t][1] = 1;
            e[t][2] = newStatusCode;
            // insert new status to queue
            q++;
            queue[q] = newStatusCode;
            if (matchCode == queue[q]) break;
        }
        // transformation 2
        getStatus(p);
        trans2(status);
        newStatusCode = getStatusCode(status);
        t = getHash(newStatusCode);
        if (e[t][2] != newStatusCode) {
            // record to hash array
            e[t][0] = oldStatusCode;
            e[t][1] = 2;
            e[t][2] = newStatusCode;
            // insert new status to queue
            q++;
            queue[q] = newStatusCode;
            if (matchCode == queue[q]) break;
        }
       // transformation 3
        getStatus(p);
        trans3(status);
        newStatusCode = getStatusCode(status);
        t = getHash(newStatusCode);
        if (e[t][2] != newStatusCode) {
            // record to hash array
            e[t][0] = oldStatusCode;
            e[t][1] = 3;
            e[t][2] = newStatusCode;
            // insert new status to queue
            q++;
            queue[q] = newStatusCode;
            if (matchCode == queue[q]) break;
        }
    }

    // output
    t = queue[q];
    q = 0;
    while (t != 1234567) {
        p = getHash(t);
        queue[q] = e[p][1];
        t = e[p][0];
        q++;
    }
    fprintf(fout, "%d\n", q);
    p = 0;
    for (i = q- 1; i >= 0; i--) {
        p++;
        if (p == 60) { fprintf(fout, "\n"); p = 1; }
        fprintf(fout, "%c", queue[i] + 64);
    }
    fprintf(fout, "\n");

    fclose(fin);
    fclose(fout);
    return 0;
}

