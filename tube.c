#include    <stdio.h>
#include    <math.h>
#include    <time.h>

#include    "mario.h"
void printTube(double thet, double radius, double scale, double offset, int w, int h, int mc[], int mw, int mh, char *m[]);
double norm(double v[]);
char getValue(int w, int h, double vec[], char *m[]);

int main(int argc, char **argv)
{
    int n = 32;
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    int i = 0;
    double radius = 100;
    double offset = 12;
    double scale = 12.5;
    while (1) {
        long nsec = t.tv_nsec + 16666667L;
        if (nsec > 1000000000L) {
            t = (struct timespec){t.tv_sec + 1, nsec % 1000000000L};
        } else {
            t = (struct timespec){t.tv_sec, nsec};
        }
        printf("time: %lld %ld\n", (long long) t.tv_sec, t.tv_nsec);
        double thet = M_PI * i / 256L;
        i = (i + 1) % 512;
        printTube(thet, radius, scale, offset, 64, 160, (int []){32, 80}, 16, 16, mario);
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL);
        clock_gettime(CLOCK_MONOTONIC, &t);
    }
}

void printTube(double thet, double radius, double scale, double offset, int w, int h, int mc[], int mw, int mh, char *m[])
{
    if (!m || !mc)
        return;
    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
            double vec[] = {(x - mc[0]) * 2, y - mc[1]};
            double l = log(norm(vec)) * scale;
            double alph = atan2(vec[0], vec[1]) + thet;
            double pos[] = {-w * alph / (2 * M_PI), h * l / radius + offset};
            char v = getValue(mw, mh, pos, m);
            putchar(v);
        }
        putchar('\n');
    }
}

double norm(double v[])
{
    if (!v)
        return NAN;

    return sqrt(v[0] * v[0] + v[1] * v[1]);
}

char getValue(int w, int h, double vec[], char *m[])
{
    if (!vec || !m)
        return '\0';
    long x = (long) (vec[0] + 0.5);
    long y = (long) (vec[1] + 0.5);
    x = (x < 0 ? w + (x % w) - 1 : x % w);
    y = (y < 0 ? h + (y % h) - 1 : y % h);
    return m[y][x];
}
