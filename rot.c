#include    <stdio.h>
#include    <math.h>
#include    <time.h>

char *mtx2[] = {
    "                       ",
    "                       ",
    "                       ",
    "                       ",
    "    ###############    ",
    "    #      #      #    ",
    "    #  ##  #      #    ",
    "    # #### #      #    ",
    "    # #### #      #    ",
    "    #  ##  #      #    ",
    "    #      #      #    ",
    "    ###############    ",
    "    #      #      #    ",
    "    #      #      #    ",
    "    #      #      #    ",
    "    #      #      #    ",
    "    #      #      #    ",
    "    #      #      #    ",
    "    ###############    ",
    "                       ",
    "                       ",
    "                       ",
    "                       ",
};
#include    "mario.h"
void printTransformed(double thet, double scale, int w, int h, int c[], int mc[], int mw, int mh, char *m[]);
char getValue(int w, int h, double vec[], char *m[]);

int main(int argc, char **argv)
{
    int n = 32;
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    int i = 0;
    double scale = 2.0;
    while (1) {
        long nsec = t.tv_nsec + 33333333L;
        if (nsec > 1000000000L) {
            t = (struct timespec){t.tv_sec + 1, nsec % 1000000000L};
        } else {
            t = (struct timespec){t.tv_sec, nsec};
        }
        printf("time: %lld %ld\n", (long long) t.tv_sec, t.tv_nsec);
        double thet = M_PI * (i / (double) 128);
        i = (i + 1) % 256;
        printTransformed(thet, scale, 48, 48, (int []){8, 8}, (int []){24, 24}, 16, 16, mario);
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL);
        clock_gettime(CLOCK_MONOTONIC, &t);
    }
}

void printTransformed(double thet, double scale, int w, int h, int c[], int mc[], int mw, int mh, char *m[])
{
    double sinthet = sin(-thet);
    double costhet = cos(-thet);
    scale = 1/scale;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            int vec[] = {x - mc[0], y - mc[1]};
            double rot[] = {costhet*vec[0] + sinthet*vec[1], -sinthet*vec[0] + costhet*vec[1]};
            rot[0] *= scale;
            rot[1] *= scale;
            char v = getValue(mw, mh, (double[]){rot[0] + c[0], rot[1] + c[1]}, m);
            printf("%c%c", v, v);
        }
        putchar('\n');
    }
}

char getValue(int w, int h, double vec[], char *m[])
{
    int x = (int) (vec[0] + 0.5);
    int y = (int) (vec[1] + 0.5);
    if (!m || x >= w || y >= h || x < 0 || y < 0)
        return ' ';
    return m[y][x];
}
