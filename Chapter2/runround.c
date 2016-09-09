/*
ID: cyl12341
LANG: C
TASK: runround
*/
#include <stdio.h>
#include <assert.h>

// e.g. num = 81362 -> i = 5
int getLength(long num)
{
    int i = 0;
    while (num > 0) {
        num /= 10;
        i++;
    }
    return i;
}

// e.g. num = 81362 -> array[] = {0,8,1,3,6,2}
void getArray(long num, int array[])
{
    array[0] = 0;
    int p = getLength(num);
    int i = p;
    long t = num;
    while (t > 0) {
        array[i] = t % 10;
        t /= 10;
        i--;
    }
}

// e.g. array[] = {0,8,1,3,6,2} -> num = 81362
long getNum(int array[], int length)
{
    int i;
    long num = 0;
    for (i = 1; i <= length; i++) {
        num = num * 10 + array[i];
    }
    return num;
}

// e.g. index = 5 -> num = 123,455
long getBigNum(int index)
{
    int i;
    long num = 1;
    for (i = 1; i <= index; i++) num = num * 10 + i + 1;
    return num - 1;
}

// e.g. num = 81362 -> result = 1
int check(long num)
{
    int i, j;
    int result = 0;
    int p = getLength(num);
    int tmp[20];
    getArray(num, tmp);
    int hasRun[10];
    for (i = 0; i <=p; i++) hasRun[i] = 0;
    i = 1;
    hasRun[1] = 1;
    hasRun[0]++;
    while (hasRun[0] <= p) {
        // get the next number
        j = (tmp[i] % p + i) % p;
        if (j == 0) j = p;
        if (hasRun[j] == 1) {
            // has reached
            break;
        } else {
            hasRun[j] = 1;
            hasRun[0]++;
            i = j;
        }
    }
    if (hasRun[0] == p && j == 1) {
        result = 1;
    }
    return result;
}

// e.g. num = 81362 -> 81367
long getNext(long num, int index)
{
    int p = getLength(num);
    if (index == 0) {
       return getNext(getBigNum(p), p + 1); 
    }

    int i, result = 0;
    long newNum = 0;

    // judge if has 0 before index position
    int numDigit[20];
    getArray(num, numDigit);
    for (i = 1; i <= index; i++) {
        if (numDigit[i] == 0) {
            break;
        }
    }
    if (i < index) return getNext(num, i);

    // judge if has repeat digit before index position
    int repeatNum[10];
    for (i = 0; i < 10; i++) repeatNum[i] = 0;
    for (i = 1; i < index; i++) {
        if (repeatNum[numDigit[i]] == 1) {
            break;
        }
        repeatNum[numDigit[i]] = 1;
    }
    if (i < index) return getNext(num, i);

    // reset the places behind index position
    for (i = index + 1; i <= p; i++) numDigit[i] = 0;

    // index position
    for (i = numDigit[index] + 1; i <= 9; i++) {
        if (repeatNum[i] == 0) {
            // set the index position
            repeatNum[i] = 1;
            numDigit[index] = i;
            // get new number
            newNum = getNum(numDigit, p);
            if (index == p) {
                result = check(newNum);
                if (result == 1) {
                    break;
                } else {
                    repeatNum[i] = 0;
                }
            } else {
                // find the next place
                newNum = getNext(newNum, index + 1);
                if (newNum == 0) {
                    // prepare for next digit
                    repeatNum[i] = 0;
                } else {
                    result = 1;
                    break;
                }
            }
        }
    }
    // find the previous place
    if (result == 0) {
        return getNext(num, index - 1);
    }
    return newNum;
}

int main(void)
{
    long m;
    FILE *fin = fopen("runround.in", "r");
    FILE *fout = fopen("runround.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%ld", &m);
    if (m <= 0) {
        fprintf(fout, "1\n");
    } else {
        fprintf(fout, "%ld\n", getNext(m, getLength(m)));
    }

    fclose(fin);
    fclose(fout);

    return 0;
}

