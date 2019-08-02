#include    <stdio.h>
#include    <math.h>
#include    <time.h>

#include    "mario.h"
void printTransformed(double thet, double scale, int w, int h, int c[], int mc[], int mw, int mh, char *m[]);
char getValue(int w, int h, double vec[], char *m[]);

int main(int argc, char **argv)
{
    int n = 32;
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    int i = 0;
    int j = 0;
    double scale_factor = 1.5;
    while (1) {
        long nsec = t.tv_nsec + 16666667L;
        if (nsec > 1000000000L) {
            t = (struct timespec){t.tv_sec + 1, nsec % 1000000000L};
        } else {
            t = (struct timespec){t.tv_sec, nsec};
        }
        printf("time: %lld %ld\n", (long long) t.tv_sec, t.tv_nsec);
        double thet = M_PI * (i / (double) 128);
        double phi = M_PI * (j / (double) 100);
        double scale = cos(phi) * scale_factor;
        scale = (scale < 0 ? -scale : scale) + 0.8;
        i = (i + 1) % 256;
        j = (j + 1) % 100;
        printTransformed(thet, scale, 160, 64, (int []){8, 8}, (int []){80, 30}, 16, 16, mario);
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL);
        clock_gettime(CLOCK_MONOTONIC, &t);
    }
}

void printTransformed(double thet, double scale, int w, int h, int c[], int mc[], int mw, int mh, char *m[])
{
    double sinthet = sin(-thet);
    double costhet = cos(-thet);
    if ((scale < 0 ? -scale : scale) < 0.001) {
        scale = 1000;
    } else {
        scale = 1/scale;
    }
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            double vec[] = {(x - mc[0]) / 2.0L, y - mc[1]};
            double rot[] = {costhet*vec[0] + sinthet*vec[1], -sinthet*vec[0] + costhet*vec[1]};
            rot[0] *= scale;
            rot[1] *= scale;
            char v = getValue(mw, mh, (double[]){rot[0] + c[0], rot[1] + c[1]}, m);
            putchar(v);
        }
        putchar('\n');
    }
}

char getValue(int w, int h, double vec[], char *m[])
{
    long x = (long) (vec[0] + 0.5);
    long y = (long) (vec[1] + 0.5);
    x = (x < 0 ? w + (x % w) - 1 : x % w);
    y = (y < 0 ? h + (y % h) - 1 : y % h);
    return m[y][x];
}
